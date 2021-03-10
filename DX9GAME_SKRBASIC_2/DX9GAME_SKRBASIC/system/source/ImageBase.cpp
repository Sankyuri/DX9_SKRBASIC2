#include "..\header\Basic.h"
#include "..\header\ImageBase.h"
#include "..\header\Input.h"

using namespace skrBasic;

int ImageBase::getImgWidth() {
	return m_width;
}

int ImageBase::getImgHeight() {
	return m_height;
}

float ImageBase::getPosX() {
	return m_pos.x;
}

float ImageBase::getPosY() {
	return m_pos.y;
}

float ImageBase::getPosZ() {
	return m_pos.z;
}

float ImageBase::getCenterX() {
	return m_cpos.x;
}

float ImageBase::getCenterY() {
	return m_cpos.y;
}

float ImageBase::getCenterZ() {
	return m_cpos.z;
}

float ImageBase::getAngleX() {
	return m_angle.x;
}

float ImageBase::getAngleY() {
	return m_angle.y;
}

float ImageBase::getAngleZ() {
	return m_angle.z;
}

float ImageBase::getScaleX() {
	return m_scale.x;
}

float ImageBase::getScaleY() {
	return m_scale.y;
}

float ImageBase::getScaleZ() {
	return m_scale.z;
}


LPDIRECT3DTEXTURE9 ImageBase::getTexture() {
	return m_ppTexture;
}




bool ImageBase::isScaled() {
	return (abs(m_scale.x) > 0.0001f ||
		    abs(m_scale.y) > 0.0001f ||
		    abs(m_scale.z) > 0.0001f );
}


bool ImageBase::isRotated() {
	return (abs(m_angle.z) > 0.0001f ||
		    abs(m_angle.x) > 0.0001f ||
		    abs(m_angle.y) > 0.0001f );
}




bool ImageBase::isMouseHoverOn() {
	if (m_isDrawable) {
		POINT curPos = Input::getCursorPos();
		RECT  imgRct;
		float hw = m_width / 2.0f * m_scale.x, hh = m_height / 2.0f * m_scale.y;
		// 矩形を求める
		if (isRotated()) { // 回転した矩形
			SetRect(&imgRct, -hw, -hh, hw, hh);
			curPos = getRelativePoint(curPos);
		}
		else { // 回転していない矩形
			SetRect(&imgRct, m_pos.x - hw, m_pos.y - hh, m_pos.x + hw, m_pos.y + hh);
		} // if (isCanDraw)
		// カーソルが矩形内(=画像上)にあるか
		if (curPos.x < imgRct.left || imgRct.right  <= curPos.x ||
			curPos.y < imgRct.top  || imgRct.bottom <= curPos.y )
		{
			// 矩形外
			return false;
		}
		//矩形内
		return true;
	}
	//描画されない
	return false;
}


POINT ImageBase::getRelativePoint(const POINT &a_curPos) {
	D3DXVECTOR3 tmpVec = D3DXVECTOR3(a_curPos.x, a_curPos.y, 0.0f) - m_pos;
	float cf  = cosf(m_angle.z);
	float sf  = sinf(m_angle.z);
	POINT res = {
		(LONG)( cf * tmpVec.x + sf * tmpVec.y),
		(LONG)(-sf * tmpVec.x + cf * tmpVec.y)
	};
	return res;
//	//行列使う版
//	D3DXVECTOR4 resVec;
//	D3DXMATRIX  mtx;
//	D3DXMatrixIdentity(&mtx);
//	D3DXMatrixRotationZ(&mtx, -angle.z);
//	D3DXVec3Transform(&resVec, &tmpVec, &mtx);
//	return POINT{ (LONG)resVec.x, (LONG)resVec.y };
}


bool ImageBase::isMouseInputOn(MouseInput a_mousebutton) {
	return (isMouseHoverOn() && Input::isMouseInput(a_mousebutton));
}


bool ImageBase::isMouseClickOn(MouseInput a_mousebutton) {
	return (isMouseHoverOn() && Input::isMouseClick(a_mousebutton));
}


bool ImageBase::isMouseReleaseOn(MouseInput a_mousebutton) {
	return (isMouseHoverOn() && Input::isMouseRelease(a_mousebutton));
}


bool ImageBase::isSomeMouseOn() {
	return (isMouseHoverOn() && Input::isSomeMouse());
}




ImageBase::ImageBase() :
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_cpos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
	m_angle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pReferTexture(nullptr),
	m_ppTexture(nullptr)
{
	D3DXMatrixIdentity(&m_mtrxMove);
	D3DXMatrixIdentity(&m_mtrxScale);
	D3DXMatrixIdentity(&m_mtrxRotate);
}

ImageBase::~ImageBase() {
	SafeRelease(m_ppTexture);
}



