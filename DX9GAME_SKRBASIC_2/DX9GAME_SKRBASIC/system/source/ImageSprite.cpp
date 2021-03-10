//#include "..\header\SKRGameCommon.h"
#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#include "..\header\ImageSprite.h"

using namespace skrBasic;

static D3DXMATRIX g_Sprite2DMatrix;

HRESULT ImageSprite::load(LPCTSTR a_srcFile, DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor) {
	m_width  = a_width;  //幅設定
	m_height = a_height; //高さ設定
	m_blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	m_cpos = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &m_ppSprite); //スプライトのセットアップ
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, a_srcFile, m_width, m_height, D3DX_DEFAULT,
		                                   0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		/*テクスチャの読み込み*/           D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture))) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}

	m_isDrawable = true;
	return S_OK;

}

HRESULT ImageSprite::loadFromMemory(const BYTE a_data[], DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	m_width  = a_width;  //幅設定
	m_height = a_height; //高さ設定
	m_blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	m_cpos = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &m_ppSprite); //スプライトのセットアップ
	if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, a_data, a_size, m_width, m_height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture)))
	{
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}
	m_isDrawable = true;
	return S_OK;
}

HRESULT ImageSprite::loadFromResourceFile(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	m_width  = a_width;  //幅設定
	m_height = a_height; //高さ設定
	m_blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	m_cpos = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &m_ppSprite); //スプライトのセットアップ

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
			g_pd3dDevice, data, a_size, m_width, m_height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture)))
	{
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		SafeDeleteArray(data); // 一時バッファを解放
		return E_FAIL;
	}
	SafeDeleteArray(data); // 一時バッファを解放
	m_isDrawable = true;
	return S_OK;
}

HRESULT ImageSprite::loadFromResource(int a_id,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	m_width  = a_width;  //幅設定
	m_height = a_height; //高さ設定
	m_blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	m_cpos = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &m_ppSprite); //スプライトのセットアップ

	if (FAILED(D3DXCreateTextureFromResourceEx(
			g_pd3dDevice, NULL, MAKEINTRESOURCE(a_id), m_width, m_height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture)))
	{
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}

	m_isDrawable = true;
	return S_OK;
}

HRESULT ImageSprite::refer(ImageBase &a_obj) {
	m_isDrawable = false;
	if (NULL == a_obj.getTexture()) {
		Message(_T("空の画像を使用しようとしました"), _T("ImageSprite::referTexture()"));
		return E_FAIL;
	}
	a_obj.getTexture()->AddRef();
	this->m_pReferTexture = &a_obj; //同じものを指すようにする
	if (NULL == this->m_pReferTexture) {
		Message(_T("画像の参照に失敗しました"), _T("Error"));
		return E_FAIL;
	}
	this->m_width  = a_obj.getImgWidth();
	this->m_height = a_obj.getImgHeight();
	m_cpos = D3DXVECTOR3((float)this->m_width / 2.0f,
		                 (float)this->m_height / 2.0f, 0.0f); //画像の中心を初期化
	m_isDrawable = true;
	return S_OK;
}


HRESULT ImageSprite::draw(const RECT *a_trimSize, D3DCOLOR a_color) {
	if (m_isDrawable) {
		RECT rc = { 0, 0, m_width, m_height }; //画像の表示部分の設定
		if (a_trimSize) {
			//トリミング範囲が渡された場合はそれで設定
			rc = *a_trimSize;
		} //渡されていない場合はフルサイズとする
		if (not a_color) {
			a_color = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
		}
		D3DXVECTOR3 drPos = D3DXVECTOR3(0, 0, 0);
		m_ppSprite->Begin(0);
		if (m_blendMode == D3DBLEND_INVSRCALPHA) {
			if (FAILED(m_ppSprite->Draw(m_ppTexture, &rc, &m_cpos, &drPos, a_color))) {
				Message(_T("画像の表示に失敗しました"), _T("Error"));
				m_isDrawable = false;
			}
		}
		else {
			// アルファブレンドモードを変更
			g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, m_blendMode);
			// 描画
			if (FAILED(m_ppSprite->Draw(m_ppTexture, &rc, &m_pos, &drPos, a_color))) {
				Message(_T("画像の表示に失敗しました"), _T("Error"));
				// アルファブレンドモードを元に戻す
				g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				m_isDrawable = false;
				m_ppSprite->End();
				return E_FAIL;
			}
			// アルファブレンドモードを元に戻す
			g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		m_ppSprite->End();
		return S_OK;
	}
	return E_FAIL;
}
HRESULT ImageSprite::draw(const RECT *a_trimSize) {
	return draw(a_trimSize, D3DCOLOR(0));
}
HRESULT ImageSprite::draw() {
	return draw(nullptr, D3DCOLOR(0));
}




HRESULT ImageSprite::createEmptyTexture(DWORD a_width, DWORD a_height) {
	m_width  = a_width;   //幅設定
	m_height = a_height; //高さ設定
	m_blendMode = D3DBLEND_INVSRCALPHA; //アルファブレンドの方法の設定
	m_cpos = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	D3DXCreateSprite(g_pd3dDevice, &m_ppSprite); //スプライトのセットアップ

	//空テクスチャ生成
	try {
		//テクスチャ本体生成
		if (FAILED(g_pd3dDevice->CreateTexture(
			m_width, m_height, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_ppTexture, NULL))) throw(1);
		//深度バッファ作成
		if (FAILED(g_pd3dDevice->CreateDepthStencilSurface(
			m_width, m_height, D3DFMT_D16,
			D3DMULTISAMPLE_NONE, 0, 1, &m_zbSurf, NULL))) throw(2);
		//テクスチャのインターフェース取得
		if (FAILED(m_ppTexture->GetSurfaceLevel(0, &m_rtSurf))) throw(3);
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
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}

	//ビューポート設定
	m_vpSurf.X      = 0;
	m_vpSurf.Y      = 0;
	m_vpSurf.Width  = m_width;
	m_vpSurf.Height = m_height;
	m_vpSurf.MinZ   = 0.0f;
	m_vpSurf.MaxZ   = 1.0f;

	m_isDrawable = true;
	return S_OK;
}

HRESULT ImageSprite::setRenderTarget(D3DCOLOR a_clearColor) {
	g_pd3dDevice->SetViewport(&m_vpSurf);
	g_pd3dDevice->SetRenderTarget(0, m_rtSurf);
	g_pd3dDevice->SetDepthStencilSurface(m_zbSurf);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		                a_clearColor, 1.0f, 0);
	return S_OK;
}




void ImageSprite::alphaBlendMode(D3DBLEND a_mode) {
	m_blendMode = a_mode;
}




float ImageSprite::getAngleX() {
	return m_angle.x;
}

float ImageSprite::getAngleY() {
	return m_angle.y;
}

float ImageSprite::getAngleZ() {
	return m_angle.z;
}

float ImageSprite::getAngle() {
	return m_angle.z;
}




void ImageSprite::setPos(float a_posX, float a_posY) {
	move(-(m_pos.x - a_posX), -(m_pos.y - a_posY));
}

void ImageSprite::setCenterPos(float a_centerX, float a_centerY) {
	m_cpos.x = a_centerX;
	m_cpos.y = a_centerY;
}




void ImageSprite::move(float a_x, float a_y) {
	m_pos.x += a_x;
	m_pos.y += a_y;
	D3DXMatrixTranslation(&m_mtrxMove, m_pos.x, m_pos.y, 0.0f);
	matrixFinally();
}

void ImageSprite::scaling(float a_size) {
	scaling(a_size, a_size);
}
void ImageSprite::scaling(float a_x, float a_y) {
	m_scale.x += a_x;
	m_scale.y += a_y;
	D3DXMatrixScaling(&m_mtrxScale, m_scale.x, m_scale.y, 0.0f);
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
	m_angle.x += a_angleRad;
	D3DXMatrixRotationX(&m_mtrxRotate, m_angle.x);
	matrixFinally();
}
void ImageSprite::rotateY(float a_angleRad) {
	m_angle.y += a_angleRad;
	D3DXMatrixRotationY(&m_mtrxRotate, m_angle.y);
	matrixFinally();
}
void ImageSprite::rotateZ(float a_angleRad) {
	m_angle.z += a_angleRad;
	D3DXMatrixRotationZ(&m_mtrxRotate, m_angle.z);
	matrixFinally();
}

void ImageSprite::matrixFinally() {
	D3DXMatrixMultiply(&m_mtrxTemp, &m_mtrxScale, &m_mtrxRotate);
	D3DXMatrixMultiply(&m_mtrx, &m_mtrxTemp, &m_mtrxMove);
	m_ppSprite->SetTransform(&m_mtrx);
}




ImageSprite::ImageSprite() :
	m_ppSprite(nullptr)
{
	// none
}

ImageSprite::~ImageSprite() {
	SafeRelease(m_ppSprite);
}



