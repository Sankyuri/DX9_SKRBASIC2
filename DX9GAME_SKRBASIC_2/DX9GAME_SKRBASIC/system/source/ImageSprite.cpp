//#include "..\header\SKRGameCommon.h"
#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#include "..\header\ImageSprite.h"

using namespace skrBasic;

static D3DXMATRIX g_Sprite2DMatrix;

HRESULT ImageSprite::load(LPCTSTR a_srcFile, DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor) {
	width  = a_width;  //幅設定
	height = a_height; //高さ設定
	blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	cpos = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &ppSprite); //スプライトのセットアップ
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, a_srcFile, width, height, D3DX_DEFAULT,
		                                   0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		/*テクスチャの読み込み*/           D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture))) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		isCanDraw = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}

	isCanDraw = true;
	return S_OK;

}

HRESULT ImageSprite::loadFromMemory(const BYTE a_data[], DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	width  = a_width;  //幅設定
	height = a_height; //高さ設定
	blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	cpos = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &ppSprite); //スプライトのセットアップ
	if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, a_data, a_size, width, height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture)))
	{
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		isCanDraw = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}
	isCanDraw = true;
	return S_OK;
}

HRESULT ImageSprite::loadFromResourceFile(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	width  = a_width;  //幅設定
	height = a_height; //高さ設定
	blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	cpos = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &ppSprite); //スプライトのセットアップ

	// データ読み込み
	FILE *fp   = _tfopen(a_pSrcFile, _T("rb"));
	if (NULL == fp) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		return E_FAIL;
	}
	BYTE *data = new BYTE[a_size]; // 一時バッファを作成
	fseek(fp, a_offset, SEEK_SET); // オフセット分だけ進める
	if (a_size != fread(data, sizeof(BYTE), a_size, fp)) { // データ読み込み
		Message(_T("画像データの読み込みに失敗しました"), _T("Error"));
		SafeDeleteArray(data); // 一時バッファを解放
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, data, a_size, width, height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture)))
	{
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		isCanDraw = false; //失敗した時は描画処理をしなくする
		SafeDeleteArray(data); // 一時バッファを解放
		return E_FAIL;
	}
	SafeDeleteArray(data); // 一時バッファを解放
	isCanDraw = true;
	return S_OK;
}

HRESULT ImageSprite::loadFromResource(int a_id,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	width  = a_width;  //幅設定
	height = a_height; //高さ設定
	blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	cpos = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &ppSprite); //スプライトのセットアップ

	if (FAILED(D3DXCreateTextureFromResourceEx(
			g_pd3dDevice, NULL, MAKEINTRESOURCE(a_id), width, height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture)))
	{
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		isCanDraw = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}

	isCanDraw = true;
	return S_OK;
}

HRESULT ImageSprite::refer(ImageBase *a_obj) {
	isCanDraw = false;
	if (NULL == a_obj->getTexture()) {
		Message(_T("空の画像を使用しようとしました"), _T("ImageSprite::referTexture()"));
		return E_FAIL;
	}
	a_obj->getTexture()->AddRef();
	this->pReferTexture = a_obj; //同じものを指すようにする
	if (NULL == this->pReferTexture) {
		Message(_T("画像の参照に失敗しました"), _T("Error"));
		return E_FAIL;
	}
	this->width  = a_obj->getImgWidth();
	this->height = a_obj->getImgHeight();
	cpos = D3DXVECTOR3((float)this->width / 2.0f,
		               (float)this->height / 2.0f, 0.0f); //画像の中心を初期化
	isCanDraw = true;
	return S_OK;
}


HRESULT ImageSprite::draw(const RECT *a_trimSize, D3DCOLOR a_color) {
	if (true == isCanDraw) {
		RECT rc = { 0, 0, width, height }; //画像の表示部分の設定
		if (a_trimSize) {
			//トリミング範囲が渡された場合はそれで設定
			rc = *a_trimSize;
		} //渡されていない場合はフルサイズとする
		if (not a_color) {
			a_color = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
		}
		D3DXVECTOR3 drPos = D3DXVECTOR3(0, 0, 0);
		ppSprite->Begin(0);
		if (blendMode == D3DBLEND_INVSRCALPHA) {
			if (FAILED(ppSprite->Draw(ppTexture, &rc, &cpos, &drPos, a_color))) {
				Message(_T("画像の表示に失敗しました"), _T("Error"));
				isCanDraw = false;
			}
		}
		else {
			// アルファブレンドモードを変更
			g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, blendMode);
			// 描画
			if (FAILED(ppSprite->Draw(ppTexture, &rc, &cpos, &drPos, a_color))) {
				Message(_T("画像の表示に失敗しました"), _T("Error"));
				// アルファブレンドモードを元に戻す
				g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				isCanDraw = false;
				ppSprite->End();
				return E_FAIL;
			}
			// アルファブレンドモードを元に戻す
			g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		ppSprite->End();
		return S_OK;
	}
	return E_FAIL;
}
HRESULT ImageSprite::draw(const RECT *a_trimSize) {
	return draw(a_trimSize, NULL);
}
HRESULT ImageSprite::draw() {
	return draw(nullptr, NULL);
}




HRESULT ImageSprite::createEmptyTexture(DWORD a_width, DWORD a_height) {
	width  = a_width;   //幅設定
	height = a_height; //高さ設定
	blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	cpos = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &ppSprite); //スプライトのセットアップ

	//空テクスチャ生成
	try {
		//テクスチャ本体生成
		if (FAILED(g_pd3dDevice->CreateTexture(
			width, height, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &ppTexture, NULL))) throw(1);
		//深度バッファ作成
		if (FAILED(g_pd3dDevice->CreateDepthStencilSurface(
			width, height, D3DFMT_D16,
			D3DMULTISAMPLE_NONE, 0, 1, &zbSurf, NULL))) throw(2);
		//テクスチャのインターフェース取得
		if (FAILED(ppTexture->GetSurfaceLevel(0, &rtSurf))) throw(3);
	}
	catch (int res) {
		switch (res) {
		case 1:
			Message(_T("空テクスチャのテクスチャ生成に失敗しました"),
				    _T("Error:ImageSprite::createEmptyTexture()"));
			break;
		case 2:
			Message(_T("空テクスチャの深度バッファ生成に失敗しました"),
				    _T("Error:ImageSprite::createEmptyTexture()"));
			break;
		case 3:
			Message(_T("空テクスチャのインターフェース取得に失敗しました"),
				    _T("Error:ImageSprite::createEmptyTexture()"));
			break;
		default:
			Message(_T("無効なパラメータ"),
				    _T("Error:ImageSprite::createEmptyTexture()"));
			break;
		}
		isCanDraw = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}

	//ビューポート設定
	vpSurf.X      = 0;
	vpSurf.Y      = 0;
	vpSurf.Width  = width;
	vpSurf.Height = height;
	vpSurf.MinZ   = 0.0f;
	vpSurf.MaxZ   = 1.0f;

	isCanDraw = true;
	return S_OK;
}

HRESULT ImageSprite::setRenderTarget(D3DCOLOR a_clearColor) {
	g_pd3dDevice->SetViewport(&vpSurf);
	g_pd3dDevice->SetRenderTarget(0, rtSurf);
	g_pd3dDevice->SetDepthStencilSurface(zbSurf);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		                a_clearColor, 1.0f, 0);
	return S_OK;
}




void ImageSprite::alphaBlendMode(D3DBLEND a_mode) {
	blendMode = a_mode;
}




float ImageSprite::getAngleX() {
	return angle.x;
}

float ImageSprite::getAngleY() {
	return angle.y;
}

float ImageSprite::getAngleZ() {
	return angle.z;
}

float ImageSprite::getAngle() {
	return angle.z;
}




void ImageSprite::setPos(float a_posX, float a_posY) {
	move(-(pos.x - a_posX), -(pos.y - a_posY));
}

void ImageSprite::setCenterPos(float a_centerX, float a_centerY) {
	cpos.x = a_centerX;
	cpos.y = a_centerY;
}




void ImageSprite::move(float a_x, float a_y) {
	pos.x += a_x;
	pos.y += a_y;
	D3DXMatrixTranslation(&mtrx_move, pos.x, pos.y, 0.0f);
	matrixFinally();
}

void ImageSprite::scaling(float a_size) {
	scaling(a_size, a_size);
}
void ImageSprite::scaling(float a_x, float a_y) {
	scale.x += a_x;
	scale.y += a_y;
	D3DXMatrixScaling(&mtrx_scale, scale.x, scale.y, 0.0f);
	matrixFinally();
}

void ImageSprite::rotate(float a_angleRad) {
	rotateZ(a_angleRad);
}
void ImageSprite::rotate(Axis a_axis, float a_angleRad) {
	if (Axis::X == a_axis) {
		rotateX(a_angleRad);
	}
	else if (Axis::Y == a_axis) {
		rotateY(a_angleRad);
	}
	else if (Axis::Z == a_axis) {
		rotateZ(a_angleRad);
	}
	else {
		Message(_T("無効なパラメータ"), _T("ImageSprite::rotate()"));
	}
}
void ImageSprite::rotateX(float a_angleRad) {
	angle.x += a_angleRad;
	D3DXMatrixRotationX(&mtrx_rotate, angle.x);
	matrixFinally();
}
void ImageSprite::rotateY(float a_angleRad) {
	angle.y += a_angleRad;
	D3DXMatrixRotationY(&mtrx_rotate, angle.y);
	matrixFinally();
}
void ImageSprite::rotateZ(float a_angleRad) {
	angle.z += a_angleRad;
	D3DXMatrixRotationZ(&mtrx_rotate, angle.z);
	matrixFinally();
}

void ImageSprite::matrixFinally() {
	D3DXMatrixMultiply(&mtrx_temp, &mtrx_scale, &mtrx_rotate);
	D3DXMatrixMultiply(&mtrx, &mtrx_temp, &mtrx_move);
	ppSprite->SetTransform(&mtrx);
}




ImageSprite::ImageSprite() {
	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //現在の座標を (0, 0) に初期化
	cpos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mtrx_move);
	D3DXMatrixIdentity(&mtrx_scale);
	D3DXMatrixIdentity(&mtrx_rotate);
	pReferTexture = NULL;
	ppSprite      = NULL;
	ppTexture     = NULL;
}

ImageSprite::~ImageSprite() {
	SafeRelease(ppSprite);
	SafeRelease(ppTexture);
}