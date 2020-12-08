#include "..\header\ImageBase.h"
#include "..\header\Input.h"

using namespace skrBasic;

int ImageBase::getImgWidth() {
	return width;
}

int ImageBase::getImgHeight() {
	return height;
}

float ImageBase::getPosX() {
	return pos.x;
}

float ImageBase::getPosY() {
	return pos.y;
}

float ImageBase::getPosZ() {
	return pos.z;
}

float ImageBase::getCenterX() {
	return cpos.x;
}

float ImageBase::getCenterY() {
	return cpos.y;
}

float ImageBase::getCenterZ() {
	return cpos.z;
}

float ImageBase::getAngleX() {
	return angle.x;
}

float ImageBase::getAngleY() {
	return angle.y;
}

float ImageBase::getAngleZ() {
	return angle.z;
}

float ImageBase::getScaleX() {
	return scale.x;
}

float ImageBase::getScaleY() {
	return scale.y;
}

float ImageBase::getScaleZ() {
	return scale.z;
}


LPDIRECT3DTEXTURE9 ImageBase::getTexture() {
	return ppTexture;
}




bool ImageBase::isScaled() {
	if (abs(scale.x) > 0.0001f ||
		abs(scale.y) > 0.0001f ||
		abs(scale.z) > 0.0001f )
	{
		return true;
	}
	return false;
}


bool ImageBase::isRotated() {
	if (abs(angle.z) > 0.0001f ||
		abs(angle.x) > 0.0001f ||
		abs(angle.y) > 0.0001f )
	{
		return true;
	}
	return false;
}




bool ImageBase::isMouseHoverOn() {
	if (isCanDraw) {
		POINT curPos = Input::getCursorPos();
		RECT  imgRct;
		float hw = width / 2.0f * scale.x, hh = height / 2.0f * scale.y;
		// 矩形を求める
		if (isRotated()) { // 回転した矩形
			SetRect(&imgRct, -hw, -hh, hw, hh);
			curPos = getRelativePoint(&curPos);
		}
		else { // 回転していない矩形
			SetRect(&imgRct, pos.x - hw, pos.y - hh, pos.x + hw, pos.y + hh);
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


POINT ImageBase::getRelativePoint(const POINT *a_curPos) {
	D3DXVECTOR3 tmpVec = D3DXVECTOR3(a_curPos->x, a_curPos->y, 0.0f) - pos;
	float cf  = cosf(angle.z);
	float sf  = sinf(angle.z);
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
	if (isMouseHoverOn() && Input::isMouseInput(a_mousebutton)) {
		return true;
	}
	return false;
}


bool ImageBase::isMouseClickOn(MouseInput a_mousebutton) {
	if (isMouseHoverOn() && Input::isMouseClick(a_mousebutton)) {
		return true;
	}
	return false;
}


bool ImageBase::isMouseReleaseOn(MouseInput a_mousebutton) {
	if (isMouseHoverOn() && Input::isMouseRelease(a_mousebutton)) {
		return true;
	}
	return false;
}


bool ImageBase::isSomeMouseOn() {
	if (isMouseHoverOn() && Input::isSomeMouse()) {
		return true;
	}
	return false;
}



