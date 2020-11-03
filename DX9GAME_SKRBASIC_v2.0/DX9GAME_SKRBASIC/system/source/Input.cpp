#include "..\header\Input.h"
#include "..\header\Basic.h"
#include "..\header\systemExtern.h"

static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);

using namespace skrBasic;

BYTE          Input::keystate[256];
DIJOYSTATE    Input::joystate;
DIMOUSESTATE2 Input::mousestate;
bool          Input::wasKeyIn[256];
bool          Input::wasJoyIn[36];
bool          Input::wasClick[8];
POINT         Input::mousePt;
POINT         Input::preMousePt;
bool          Input::useJoypad;
bool          Input::useMouse;


HRESULT Input::init() {
	if (initKeyboard() == E_FAIL) {
		Message(_T("�L�[�{�[�h�̏������Ɏ��s���܂���\n����ł̓Q�[�����o���Ȃ��̂ŏI�����܂�"),
			    _T("Error"));
		Release();
		exit(-1);
	}
	else {
		ZeroMemory(wasKeyIn, sizeof(wasKeyIn));
		g_lpKeyboard->Acquire();
	}
	if (initJoypad() == E_FAIL) {
		useJoypad = false;
		_tprintf(_T("�g����Q�[���p�b�h�������悤�ł��B�c�O"));
	}
	else {
		useJoypad = true;
		ZeroMemory(wasJoyIn, sizeof(wasJoyIn));
		g_lpJoypad->Acquire();
	}
	if (initMouse() == E_FAIL) {
		useMouse = false;
		_tprintf(_T("�g����}�E�X�������悤�ł��B�c�O"));
	}
	else {
		useMouse = true;
		ZeroMemory(wasClick, sizeof(wasClick));
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
						hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
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
					hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
					hr = g_lpJoypad->GetCapabilities(&g_diJoyCaps);
					hr = g_lpJoypad->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
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
					hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
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
	while (FAILED(g_lpKeyboard->GetDeviceState(sizeof(keystate), keystate))){
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
	if (useJoypad == true) {
		g_lpJoypad->Poll();
		if (FAILED(g_lpJoypad->GetDeviceState(sizeof(DIJOYSTATE), &joystate))) {
			g_lpJoypad->Acquire();
			g_lpJoypad->Poll();
			if (FAILED(g_lpJoypad->GetDeviceState(sizeof(DIJOYSTATE), &joystate))) {
				useJoypad = false;
			}
		}
	}
}

void Input::getMouseState() {
	if (useMouse == true) {
		preMousePt = mousePt; //�O��̍��W���X�V
		GetCursorPos(&mousePt); //�E�B���h�E���W���擾
		ScreenToClient(hWnd, &mousePt); //�r���[�|�[�g���W�ɕϊ�
		g_lpMouse->Poll();
		if (FAILED(g_lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mousestate))) {
			g_lpMouse->Acquire();
			g_lpMouse->Poll();
			if (FAILED(g_lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mousestate))) {
				useMouse = false;
			}
		}
	}
}




bool Input::isKeyInput(int a_key) {
	return (keystate[a_key] & BUTTON_ON_FLUG);
}

bool Input::isKeyInput(KeyboardInput a_key) {
	return isKeyInput(static_cast<int>(a_key));
}

bool Input::isKeyPush(int a_key) {
	if (keystate[a_key] & BUTTON_ON_FLUG) {
		if (false == wasKeyIn[a_key]) {
			return (wasKeyIn[a_key] = true);
		}
	}
	else {
		return (wasKeyIn[a_key] = false);
	}
	return false;
}

bool Input::isKeyPush(KeyboardInput a_key) {
	return isKeyPush(static_cast<int>(a_key));
}

bool Input::isKeyRelease(int a_key) {
	if (keystate[a_key] & BUTTON_ON_FLUG) {
		if (false == wasKeyIn[a_key]) {
			wasKeyIn[a_key] = true;
		}
	}
	else {
		if (wasKeyIn[a_key]) {
			wasKeyIn[a_key] = false;
			return true;
		}
	}
	return false;
}

bool Input::isKeyRelease(KeyboardInput a_key) {
	return isKeyRelease(static_cast<int>(a_key));
}


bool Input::isJoypadInput(JoypadInput a_button) {
	if (true == useJoypad) {
		switch (a_button) {
		case JoypadInput::UP:
			if (joystate.lY <= -PAD_POS_MIN) {
				return true;
			}
			break;
		case JoypadInput::DOWN:
			if (PAD_POS_MIN <= joystate.lY) {
				return true;
			}
			break;
		case JoypadInput::LEFT:
			if (joystate.lX <= -PAD_POS_MIN) {
				return true;
			}
			break;
		case JoypadInput::RIGHT:
			if (PAD_POS_MIN <= joystate.lX) {
				return true;
			}
			break;
		default: //�{�^��
			if (joystate.rgbButtons[static_cast<UINT>(a_button)] & BUTTON_ON_FLUG) {
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
		wasJoyIn[button] = true;
		return true;
	};

	if (true == useJoypad) {
		//�����L�[
		if (static_cast<int>(JoypadInput::BUTTON32) < button) {
			//���͂��Ă���
			if (joystate.rgbButtons[button] & BUTTON_ON_FLUG) {
				if (false == wasJoyIn[button]) {
					return changeJoyIn(button);
				}
			}
			//���͂��Ă��Ȃ�
			else {
				wasJoyIn[button] = false;
			}
		}
		//�{�^��
		else {
			if (abs(joystate.lX) > PAD_POS_MIN ||
				abs(joystate.lY) > PAD_POS_MIN)
			{
				if (false == wasJoyIn[button]) {
					//���͂��Ă���
					switch (a_button) {
					case JoypadInput::UP:
						if (joystate.lY < 0L) { return changeJoyIn(button); }
						break;
					case JoypadInput::DOWN:
						if (0L < joystate.lY) { return changeJoyIn(button); }
						break;
					case JoypadInput::LEFT:
						if (joystate.lX < 0L) { return changeJoyIn(button); }
						break;
					case JoypadInput::RIGHT:
						if (0L < joystate.lX) { return changeJoyIn(button); }
						break;
					}
				} // if (false == wasJoyIn[button])
			} // if (abs(joystate.lX) > PAD_POS_MIN || ... )
			else { //���͂��Ă��Ȃ�
				wasJoyIn[button] = false;
			}
		} // if (button < static_cast<int>(JoypadInput::UP)) { ... } else
	}
	return false;
}

bool Input::isJoypadRelease(JoypadInput a_button) {
	UINT button = static_cast<UINT>(a_button);
	static auto changeJoyIn = [](UINT button) {
		if (true == wasJoyIn[button]) {
			// ���O�܂œ��͂��Ă���
			wasJoyIn[button] = false;
			return true;
		}
		return false;
	};
	if (true == useJoypad) {
		switch (a_button) {
		case JoypadInput::UP:
			//���͂��Ă���
			if (joystate.lY < 0L) { wasJoyIn[button] = true; }
			//���͂��Ă��Ȃ�
			else { return changeJoyIn(button); }
			break;
		case JoypadInput::DOWN:
			if (0L < joystate.lY) { wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		case JoypadInput::LEFT:
			if (joystate.lX < 0L) { wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		case JoypadInput::RIGHT:
			if (0L < joystate.lX) { wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		default: //�{�^��
			if (joystate.rgbButtons[button] & BUTTON_ON_FLUG) { wasJoyIn[button] = true; }
			else { return changeJoyIn(button); }
			break;
		}
	}
	return false;
}


bool Input::isMouseInput(MouseInput a_mousebutton) {
	if (mousestate.rgbButtons[static_cast<UINT>(a_mousebutton)] & BUTTON_ON_FLUG) {
		return true;
	}
	return false;
}

bool Input::isMouseClick(MouseInput a_mousebutton) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG) {
		if (false == wasClick[mousebutton]) {
			wasClick[mousebutton] = true;
			return true;
		}
	}
	else { // ���͂��Ă��Ȃ�
		wasClick[mousebutton] = false;
		return false;
	}
	return false;
}

bool Input::isMouseRelease(MouseInput a_mousebutton) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG) {
		if (false == wasClick[mousebutton]) {
			wasClick[mousebutton] = true;
		}
	}
	else { // ���͂��Ă��Ȃ�
		if (true == wasClick[mousebutton]) { // ���O�܂œ��͂��Ă���
			wasClick[mousebutton] = false;
			return true;
		}
	}
	return false;
}

bool Input::isMouseInputInRange(MouseInput a_mousebutton, const RECT *a_area) {
	if ((mousestate.rgbButtons[static_cast<UINT>(a_mousebutton)] & BUTTON_ON_FLUG) &&
		a_area->left <= mousePt.x && a_area->right  > mousePt.x &&
		a_area->top  <= mousePt.y && a_area->bottom > mousePt.y)
	{
		return true;
	}
	return false;
}

bool Input::isMouseClickInRange(MouseInput a_mousebutton, const RECT *a_area) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG &&
		a_area->left <= mousePt.x && a_area->right  > mousePt.x &&
		a_area->top  <= mousePt.y && a_area->bottom > mousePt.y)
	{
		if (false == wasClick[mousebutton]) {
			wasClick[mousebutton] = true;
			return true;
		}
	}
	else { // ���͂��Ă��Ȃ����͈͊O
		wasClick[mousebutton] = false;
	}
	return false;
}

bool Input::isMouseReleaseInRange(MouseInput a_mousebutton, const RECT *a_area) {
	UINT mousebutton = static_cast<UINT>(a_mousebutton);
	if (mousestate.rgbButtons[mousebutton] & BUTTON_ON_FLUG &&
		a_area->left <= mousePt.x && a_area->right  > mousePt.x &&
		a_area->top  <= mousePt.y && a_area->bottom > mousePt.y)
	{
		if (false == wasClick[mousebutton]) {
			wasClick[mousebutton] = true;
		}
	}
	else { // ���͂��Ă��Ȃ����͈͊O
		wasClick[mousebutton] = false;
		return true;
	}
	return false;
}


bool Input::isMouseInRange(const RECT *a_area) {
	if (a_area->left <= mousePt.x && a_area->right  > mousePt.x &&
		a_area->top  <= mousePt.y && a_area->bottom > mousePt.y)
	{
		return true;
	}
	return false;
}


bool Input::isCursorMove() {
	if (mousePt.x != preMousePt.x ||
		mousePt.y != preMousePt.y)
	{
		return true;
	}
	return false;
}


POINT Input::getCursorPos() {
	return mousePt;
}

POINT Input::getCursorPosPt() {
	return getCursorPos();
}

D3DXVECTOR2 Input::getCursorPosVec() {
	return D3DXVECTOR2(mousePt.x, mousePt.y);
}


POINT Input::getCursorMoveLength() {
	POINT res;
	res.x = preMousePt.x - mousePt.x;
	res.y = preMousePt.y - mousePt.y;
	return res;
}

POINT Input::getCursorMoveLengthPt() {
	return getCursorMoveLength();
}

D3DXVECTOR2 Input::getCursorMoveLengthVec() {
	return D3DXVECTOR2(preMousePt.x - mousePt.x, preMousePt.y - mousePt.y);
}


LONG Input::getJoypadAxisTiltX() {
	return joystate.lX;
}

LONG Input::getJoypadAxisTiltY() {
	return joystate.lY;
}

LONG Input::getJoypadAxisTiltZ() {
	return joystate.lZ;
}


LONG Input::getMouseAxisTiltX() {
	return mousestate.lX;
}

LONG Input::getMouseAxisTiltY() {
	return mousestate.lY;
}

LONG Input::getMouseAxisTiltZ() {
	return mousestate.lZ;
}

LONG Input::getMouseWheelTilt() {
	return mousestate.lZ;
}


bool Input::isSomeKey() {
	for (int i = 0; i < KEY_ARY_MAX; ++i) {
		if (keystate[i] & BUTTON_ON_FLUG) {
			return true;
		}
	}
	return false;
}

bool Input::isSomeJoypad() {
	for (int i = 0; i < PAD_BTN_MAX; ++i) {
		if (joystate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return true;
		}
	}
	if (abs(joystate.lX) >= PAD_POS_MIN ||
		abs(joystate.lY) >= PAD_POS_MIN)
	{
		return true;
	}
	return false;
}

bool Input::isSomeMouse() {
	for (int i = 0; i < MOUSE_ARY_MAX; ++i) {
		if (mousestate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return true;
		}
	}
	return false;
}

bool Input::isSomeInput() {
	if (isSomeKey() || isSomeJoypad() || isSomeMouse()) {
		return true;
	}
	return false;
}


int Input::getSomeKey() {
	for (int i = 0; i < KEY_ARY_MAX; ++i) {
		if (keystate[i] & BUTTON_ON_FLUG) {
			return i;
		}
	}
	return -1;
}

int Input::getSomeJoypad() {
	for (int i = 0; i < PAD_BTN_MAX; ++i) {
		if (joystate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return i;
		}
	}
	if (joystate.lY <= -PAD_POS_MIN) {
		return static_cast<int>(JoypadInput::UP);
	}
	if (PAD_POS_MIN <= joystate.lY) {
		return static_cast<int>(JoypadInput::DOWN);
	}
	if (joystate.lX <= -PAD_POS_MIN) {
		return static_cast<int>(JoypadInput::LEFT);
	}
	if (PAD_POS_MIN <= joystate.lX) {
		return static_cast<int>(JoypadInput::RIGHT);
	}
	return -1;
}

int Input::getSomeMouse() {
	for (int i = 0; i < MOUSE_ARY_MAX; ++i) {
		if (mousestate.rgbButtons[i] & BUTTON_ON_FLUG) {
			return i;
		}
	}
	return -1;
}



