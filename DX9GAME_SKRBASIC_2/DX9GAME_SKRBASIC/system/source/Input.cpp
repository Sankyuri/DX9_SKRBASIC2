#include "..\header\Input.h"
#include "..\header\Basic.h"
#include "..\header\systemExtern.h"


using namespace skrBasic;

BYTE          Input::m_keystate[256];
DIJOYSTATE    Input::m_joystate;
DIMOUSESTATE2 Input::m_mousestate;
bool          Input::m_wasKeyIn[256];
bool          Input::m_wasJoyIn[36];
bool          Input::m_wasClick[8];
POINT         Input::m_mousePt;
POINT         Input::m_preMousePt;
bool          Input::m_useJoypad;
bool          Input::m_useMouse;


static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *a_pdidInstance, VOID *a_pContext);
static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *a_pdidoi, VOID *a_pContext);


HRESULT Input::init() {
	if (initKeyboard() == E_FAIL) {
		Message(_T("�L�[�{�[�h�̏������Ɏ��s���܂���\n����ł̓Q�[�����o���Ȃ��̂ŏI�����܂�"),
			    _T("Error"));
		Release();
		exit(-1);
	}
	else {
		ZeroMemory(m_wasKeyIn, sizeof(m_wasKeyIn));
		g_lpKeyboard->Acquire();
	}
	if (initJoypad() == E_FAIL) {
		m_useJoypad = false;
		_tprintf(_T("�g����Q�[���p�b�h�������悤�ł��B�c�O"));
	}
	else {
		m_useJoypad = true;
		ZeroMemory(m_wasJoyIn, sizeof(m_wasJoyIn));
		g_lpJoypad->Acquire();
	}
	if (initMouse() == E_FAIL) {
		m_useMouse = false;
		_tprintf(_T("�g����}�E�X�������悤�ł��B�c�O"));
	}
	else {
		m_useMouse = true;
		ZeroMemory(m_wasClick, sizeof(m_wasClick));
		g_lpMouse->Acquire();
	}
	return S_OK;
}




HRESULT Input::initKeyboard() {
	if (SUCCEEDED(DirectInput8Create( //DInput8������
		    GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(LPVOID*)&g_pDInput,
			NULL))) {
		if (SUCCEEDED(g_pDInput->CreateDevice( //�f�o�C�X������
				GUID_SysKeyboard,
				&g_lpKeyboard,
				NULL))) {
			if (SUCCEEDED(g_lpKeyboard->SetDataFormat(&c_dfDIKeyboard))) { //���̓f�[�^�`���ݒ�
				if (SUCCEEDED(g_lpKeyboard->SetCooperativeLevel( //�r������̐ݒ�
						g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
					return S_OK;
				}
			}
		} //�Q�l�Fhttp://www.charatsoft.com/develop/otogema/page/07input/dinput.html
	}
	return E_FAIL;
}

HRESULT Input::initJoypad() {
	HRESULT hr;
	if (SUCCEEDED(hr = DirectInput8Create( //DInput8������
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(LPVOID*)&g_pDInputJ,
		NULL))) {
		if (SUCCEEDED(hr = g_pDInputJ->EnumDevices( //�f�o�C�X������
			DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
			NULL, DIEDFL_ALLDEVICES))) {
			if (NULL != g_lpJoypad && SUCCEEDED(hr = g_lpJoypad->SetDataFormat(&c_dfDIJoystick))) { //���̓f�[�^�`���ݒ�
				if (SUCCEEDED(g_lpJoypad->SetCooperativeLevel( //�r������̐ݒ�
					g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
					hr = g_lpJoypad->GetCapabilities(&g_diJoyCaps);
					hr = g_lpJoypad->EnumObjects(EnumAxesCallback, (VOID*)g_hWnd, DIDFT_AXIS);
					return S_OK;
				}
			}
		} //�Q�l�Fhttp://princess-tiara.biz/directx/?chapter=14
	}
	return E_FAIL;
}
static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *a_pdidInstance, VOID *a_pContext)
{
	HRESULT hr;

	hr = g_pDInputJ->CreateDevice(a_pdidInstance->guidInstance, &g_lpJoypad, NULL);

	if (FAILED(hr)) return DIENUM_CONTINUE;

	return DIENUM_STOP;
}
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *a_pdidoi, VOID *a_pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = a_pdidoi->dwType;
	diprg.lMin = -512;
	diprg.lMax =  512;
	hr = g_lpJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr)) return DIENUM_STOP;

	return DIENUM_CONTINUE;
}

HRESULT Input::initMouse() {
	HRESULT hr;
	if (SUCCEEDED(hr = DirectInput8Create( //DInput8������
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(LPVOID*)&g_pDInputM,
		NULL))) {
		if (SUCCEEDED(hr = g_pDInputM->CreateDevice( //�f�o�C�X������
			GUID_SysMouse,
			&g_lpMouse,
			NULL))) {
			if (SUCCEEDED(hr = g_lpMouse->SetDataFormat(&c_dfDIMouse))) { //���̓f�[�^�`���ݒ�
				if (SUCCEEDED(g_lpMouse->SetCooperativeLevel( //�r������̐ݒ�
					g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
					return S_OK;
				}
			}
		}
	}
	return E_FAIL;
}




void Input::getInputDeviceState() {
	getKeyState();
	getJoyState();
	getMouseState();
}

void Input::getKeyState() {
	while (FAILED(g_lpKeyboard->GetDeviceState(sizeof(m_keystate), m_keystate))){
		g_lpKeyboard->Acquire();
	}
//	if (FAILED(g_lpKeyboard->GetDeviceState(sizeof(keystate), keystate))) {
//		g_lpKeyboard->Acquire();
//		if (FAILED(g_lpKeyboard->GetDeviceState(sizeof(keystate), keystate))) {
//			Message(_T("�L�[�{�[�h�̎擾�Ɏ��s���܂���\n����ł̓Q�[�����o���Ȃ��̂ŏI�����܂�"),
//				    _T("Error"));
//			Release();
//			exit(-1);
//		}
//	}
}

void Input::getJoyState() {
	if (m_useJoypad) {
		g_lpJoypad->Poll();
		if (FAILED(g_lpJoypad->GetDeviceState(sizeof(DIJOYSTATE), &m_joystate))) {
			g_lpJoypad->Acquire();
			g_lpJoypad->Poll();
			if (FAILED(g_lpJoypad->GetDeviceState(sizeof(DIJOYSTATE), &m_joystate))) {
				m_useJoypad = false;
			}
		}
	}
}

void Input::getMouseState() {
	if (m_useMouse) {
		m_preMousePt = m_mousePt; //�O��̍��W���X�V
		GetCursorPos(&m_mousePt); //�E�B���h�E���W���擾
		ScreenToClient(g_hWnd, &m_mousePt); //�r���[�|�[�g���W�ɕϊ�
		g_lpMouse->Poll();
		if (FAILED(g_lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mousestate))) {
			g_lpMouse->Acquire();
			g_lpMouse->Poll();
			if (FAILED(g_lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mousestate))) {
				m_useMouse = false;
			}
		}
	}
}




bool Input::isKeyInput(int a_key) {
	return (m_keystate[a_key] & BUTTON_ON_FLUG);
}

bool Input::isKeyInput(KeyboardInput a_key) {
	return isKeyInput(static_cast<int>(a_key));
}

bool Input::isKeyPush(int a_key) {
	if (m_keystate[a_key] & BUTTON_ON_FLUG) {
		if (not m_wasKeyIn[a_key]) {
			return (m_wasKeyIn[a_key] = true);
		}
	}
	else {
		return (m_wasKeyIn[a_key] = false);
	}
	return false;
}

bool Input::isKeyPush(KeyboardInput a_key) {
	return isKeyPush(static_cast<int>(a_key));
}

bool Input::isKeyRelease(int a_key) {
	if (m_keystate[a_key] & BUTTON_ON_FLUG) {
		if (not m_wasKeyIn[a_key]) {
			m_wasKeyIn[a_key] = true;
		}
	}
	else {
		if (m_wasKeyIn[a_key]) {
			m_wasKeyIn[a_key] = false;
			return true;
		}
	}
	return false;
}

bool Input::isKeyRelease(KeyboardInput a_key) {
	return isKeyRelease(static_cast<int>(a_key));
}


bool Input::isJoypadInput(JoypadInput a_button) {
	if (m_useJoypad) {
		switch (a_button) {
		case JoypadInput::UP:
			if (m_joystate.lY <= -PAD_POS_MIN) {
				return true;
			}
			break;
		case JoypadInput::DOWN:
			if (PAD_POS_MIN <= m_joystate.lY) {
				return true;
			}
			break;
		case JoypadInput::LEFT:
			if (m_joystate.lX <= -PAD_POS_MIN) {
				return true;
			}
			break;
		case JoypadInput::RIGHT:
			if (PAD_POS_MIN <= m_joystate.lX) {
				return true;
			}
			break;
		default: //�{�^��
			if (m_joystate.rgbButtons[static_cast<UINT>(a_button)] & BUTTON_ON_FLUG) {
				return true;
			}
			break;
		}
	}
	return false;
}

bool Input::isJoypadPush(JoypadInput a_button) {
	UINT button = static_cast<UINT>(a_button);
	static auto changeJoyIn = [](UINT button) {
		m_wasJoyIn[button] = true;
		return true;
	};

	if (m_useJoypad) {
		//�����L�[
		if (static_cast<int>(JoypadInput::BUTTON32) < button) {
			//���͂��Ă���
			if (m_joystate.rgbButtons[button] & BUTTON_ON_FLUG) {
				if (not m_wasJoyIn[button]) {
					return changeJoyIn(button);
				}
			}
			//���͂��Ă��Ȃ�
			else {
				m_wasJoyIn[button] = false;
			}
		}
		//�{�^��
		else {
			if (abs(m_joystate.lX) > PAD_POS_MIN ||
				abs(m_joystate.lY) > PAD_POS_MIN)
			{
				if (not m_wasJoyIn[button]) {
					//���͂��Ă���
					switch (a_button) {
					case JoypadInput::UP:
						if (m_joystate.lY < 0L) { return changeJoyIn(button); }
						break;
					case JoypadInput::DOWN:
						if (0L < m_joystate.lY) { return changeJoyIn(button); }
						break;
					case JoypadInput::LEFT:
						if (m_joystate.lX < 0L) { return changeJoyIn(button); }
						break;
					case JoypadInput::RIGHT:
						if (0L < m_joystate.lX) { return changeJoyIn(button); }
						break;
					}
				} // if (not wasJoyIn[button])
			} // if (abs(joystate.lX) > PAD_POS_MIN || ... )
			else { //���͂��Ă��Ȃ�
				m_wasJoyIn[button] = false;
			}
		} // if (button < static_cast<int>(JoypadInput::UP)) { ... } else
	}
	return false;
}

bool Input::isJoypadRelease(JoypadInput a_button) {
	UINT button = static_cast<UINT>(a_button);
	static auto changeJoyIn = [](UINT button) {
		if (m_wasJoyIn[button]) {
			// ���O�܂œ��͂��Ă���
			m_wasJoyIn[button] = false;
			return true;
		}
		return false;
	};
	if (m_useJoypad) {
		switch (a_button) {
		case JoypadInput::UP:
			//���͂��Ă���
			if (m_joystate.lY < 0L) { m_wasJoyIn[button] = true; }
			//���͂��Ă��Ȃ�
			else { return changeJoyIn(button); }
			break;
		case JoypadInput::DOWN:
			if (0L < m_joystate.lY) { m_wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		case JoypadInput::LEFT:
			if (m_joystate.lX < 0L) { m_wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		case JoypadInput::RIGHT:
			if (0L < m_joystate.lX) { m_wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		default: //�{�^��
			if (m_joystate.rgbButtons[button] & BUTTON_ON_FLUG) { m_wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		}
	}
	return false;
}


bool Input::isMouseInput(MouseInput a_mousebutton) {
	return (m_mousestate.rgbButtons[static_cast<UINT>(a_mousebutton)] & BUTTON_ON_FLUG);
}

bool Input::isMouseClick(MouseInput a_mousebutton) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (m_mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG) {
		if (not m_wasClick[mousebutton]) {
			m_wasClick[mousebutton] = true;
			return true;
		}
	}
	else { // ���͂��Ă��Ȃ�
		m_wasClick[mousebutton] = false;
		return false;
	}
	return false;
}

bool Input::isMouseRelease(MouseInput a_mousebutton) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (m_mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG) {
		if (not m_wasClick[mousebutton]) {
			m_wasClick[mousebutton] = true;
		}
	}
	else { // ���͂��Ă��Ȃ�
		if (m_wasClick[mousebutton]) { // ���O�܂œ��͂��Ă���
			m_wasClick[mousebutton] = false;
			return true;
		}
	}
	return false;
}

bool Input::isMouseInputInRange(MouseInput a_mousebutton, const RECT &a_area) {
	return ((m_mousestate.rgbButtons[static_cast<UINT>(a_mousebutton)] & BUTTON_ON_FLUG) &&
			a_area.left <= m_mousePt.x && a_area.right  > m_mousePt.x                    &&
			a_area.top  <= m_mousePt.y && a_area.bottom > m_mousePt.y);
}

bool Input::isMouseClickInRange(MouseInput a_mousebutton, const RECT &a_area) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (m_mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG     &&
		a_area.left <= m_mousePt.x && a_area.right  > m_mousePt.x &&
		a_area.top  <= m_mousePt.y && a_area.bottom > m_mousePt.y)
	{
		if (not m_wasClick[mousebutton]) {
			m_wasClick[mousebutton] = true;
			return true;
		}
	}
	else { // ���͂��Ă��Ȃ����͈͊O
		m_wasClick[mousebutton] = false;
	}
	return false;
}

bool Input::isMouseReleaseInRange(MouseInput a_mousebutton, const RECT &a_area) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (m_mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG     &&
		a_area.left <= m_mousePt.x && a_area.right  > m_mousePt.x &&
		a_area.top  <= m_mousePt.y && a_area.bottom > m_mousePt.y)
	{
		if (not m_wasClick[mousebutton]) {
			m_wasClick[mousebutton] = true;
		}
	}
	else { // ���͂��Ă��Ȃ����͈͊O
		m_wasClick[mousebutton] = false;
		return true;
	}
	return false;
}


bool Input::isMouseInRange(const RECT &a_area) {
	return (a_area.left <= m_mousePt.x && a_area.right  > m_mousePt.x &&
			a_area.top  <= m_mousePt.y && a_area.bottom > m_mousePt.y);
}


bool Input::isCursorMove() {
	return (m_mousePt.x != m_preMousePt.x ||
			m_mousePt.y != m_preMousePt.y);
}


POINT Input::getCursorPos() {
	return m_mousePt;
}

POINT Input::getCursorPosPt() {
	return getCursorPos();
}

D3DXVECTOR2 Input::getCursorPosVec() {
	return D3DXVECTOR2(m_mousePt.x, m_mousePt.y);
}


POINT Input::getCursorMoveLength() {
	POINT res;
	res.x = m_preMousePt.x - m_mousePt.x;
	res.y = m_preMousePt.y - m_mousePt.y;
	return res;
}

POINT Input::getCursorMoveLengthPt() {
	return getCursorMoveLength();
}

D3DXVECTOR2 Input::getCursorMoveLengthVec() {
	return D3DXVECTOR2(m_preMousePt.x - m_mousePt.x, m_preMousePt.y - m_mousePt.y);
}


LONG Input::getJoypadAxisTiltX() {
	return m_joystate.lX;
}

LONG Input::getJoypadAxisTiltY() {
	return m_joystate.lY;
}

LONG Input::getJoypadAxisTiltZ() {
	return m_joystate.lZ;
}


LONG Input::getMouseAxisTiltX() {
	return m_mousestate.lX;
}

LONG Input::getMouseAxisTiltY() {
	return m_mousestate.lY;
}

LONG Input::getMouseAxisTiltZ() {
	return m_mousestate.lZ;
}

LONG Input::getMouseWheelTilt() {
	return m_mousestate.lZ;
}


bool Input::isSomeKey() {
	for (int i = 0; i < KEY_ARY_MAX; ++i) {
		if (m_keystate[i] & BUTTON_ON_FLUG) {
			return true;
		}
	}
	return false;
}

bool Input::isSomeJoypad() {
	for (int i = 0; i < PAD_BTN_MAX; ++i) {
		if (m_joystate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return true;
		}
	}
	if (abs(m_joystate.lX) >= PAD_POS_MIN ||
		abs(m_joystate.lY) >= PAD_POS_MIN)
	{
		return true;
	}
	return false;
}

bool Input::isSomeMouse() {
	for (int i = 0; i < MOUSE_ARY_MAX; ++i) {
		if (m_mousestate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return true;
		}
	}
	return false;
}

bool Input::isSomeInput() {
	return (isSomeKey() || isSomeJoypad() || isSomeMouse());
}


int Input::getSomeKey() {
	for (int i = 0; i < KEY_ARY_MAX; ++i) {
		if (m_keystate[i] & BUTTON_ON_FLUG) {
			return i;
		}
	}
	return -1;
}

int Input::getSomeJoypad() {
	for (int i = 0; i < PAD_BTN_MAX; ++i) {
		if (m_joystate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return i;
		}
	}
	if (m_joystate.lY <= -PAD_POS_MIN) {
		return static_cast<int>(JoypadInput::UP);
	}
	if (PAD_POS_MIN <= m_joystate.lY) {
		return static_cast<int>(JoypadInput::DOWN);
	}
	if (m_joystate.lX <= -PAD_POS_MIN) {
		return static_cast<int>(JoypadInput::LEFT);
	}
	if (PAD_POS_MIN <= m_joystate.lX) {
		return static_cast<int>(JoypadInput::RIGHT);
	}
	return -1;
}

int Input::getSomeMouse() {
	for (int i = 0; i < MOUSE_ARY_MAX; ++i) {
		if (m_mousestate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return i;
		}
	}
	return -1;
}



