//#include "..\header\SKRGameCommon.h"
#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#include "..\header\ImagePolygon.h"

using namespace skrBasic;

#define FVF_SETTING (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)


HRESULT ImagePolygon::load(LPCTSTR a_srcFile,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//頂点データコピー
	if (E_FAIL == loadCommon(a_width, a_height)) {
		return E_FAIL;
	}

	//テクスチャ読み込み
	if (FAILED(loadLoadTex(a_srcFile, a_keyColor))) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}
	
	m_isDrawable = true;
	return S_OK;
}

HRESULT ImagePolygon::loadFromMemory(const BYTE a_data[], DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//頂点データコピー
	if (E_FAIL == loadCommon(a_width, a_height)) {
		return E_FAIL;
	}

	//テクスチャ読み込み
	if (FAILED(loadLoadTexMem(a_data, a_size, a_keyColor))) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}
	
	m_isDrawable = true;
	return S_OK;
}

HRESULT ImagePolygon::loadFromResourceFile(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//頂点データコピー
	if (E_FAIL == loadCommon(a_width, a_height)) {
		return E_FAIL;
	}

	//テクスチャ読み込み
	if (FAILED(loadLoadTexRscFil(a_pSrcFile, a_size, a_offset, a_keyColor))) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}
	
	m_isDrawable = true;
	return S_OK;
}

HRESULT ImagePolygon::loadFromResource(int a_id,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//頂点データコピー
	if (E_FAIL == loadCommon(a_width, a_height)) {
		return E_FAIL;
	}

	//テクスチャ読み込み
	if (FAILED(loadLoadTexRsc(a_id, a_keyColor))) {
		Message(_T("画像の読み込みに失敗しました"), _T("Error"));
		m_isDrawable = false; //失敗した時は描画処理をしなくする
		return E_FAIL;
	}
	
	m_isDrawable = true;
	return S_OK;
}


HRESULT ImagePolygon::loadCommon(DWORD a_width, DWORD a_height)
{
	m_width  = a_width;  //幅設定
	m_height = a_height; //高さ設定
	m_cpos   = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	//頂点/頂点バッファ生成
	if (FAILED(loadCreateVtx())) {
		return E_FAIL;
	}
	//頂点データコピー
	if (FAILED(copyVtx())) {
		Message(_T("頂点バッファに書き込めませんでした"), _T("Error"));
		return E_FAIL;
	}
	return S_OK;
}

HRESULT ImagePolygon::loadCreateVtx() {
	HRESULT hr;
	//
	//  0 __ 1
	//   : /:  アルファベットの Z と
	//   :/ :  同じ順番でストリップで定義
	//  2 ￣ 3
	//
	float nw = (float)m_width / 2.0f - 0.25f;
	float nh = (float)m_height / 2.0f - 0.25f;
	//vtx[n] = { x, y, z, rhw, color, u, v};
	m_vtx[0] = { -nw - 0.5f, -nh - 0.5f, 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f };
	m_vtx[1] = {  nw       , -nh - 0.5f, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f };
	m_vtx[2] = { -nw - 0.5f,  nh       , 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f };
	m_vtx[3] = {  nw       ,  nh       , 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f };

	//頂点バッファ生成
	if (FAILED(hr = loadCreateVtxBuf())) {
		switch (hr) {
		case D3DERR_OUTOFVIDEOMEMORY:
			Message(_T("頂点バッファの生成に失敗しました。\nビデオメモリ不足です"),
					_T("Error"));
			break;
		case E_OUTOFMEMORY:
			Message(_T("頂点バッファの生成に失敗しました。\nメモリ不足です"),
					_T("Error"));
			break;
		default:
			Message(_T("頂点バッファの生成に失敗しました"),
					_T("Error"));
			break;
		}
		m_isDrawable = false;
		return E_FAIL; //メモリ不足等なので抜ける
	}
	return S_OK;
}

HRESULT ImagePolygon::loadCreateVtxBuf() {
	return g_pd3dDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_SETTING,
		D3DPOOL_MANAGED,
		&m_ppVtxBuf,
		NULL
	);
}

HRESULT ImagePolygon::loadLoadTex(LPCTSTR a_srcFile, D3DCOLOR a_keyColor) {
	return D3DXCreateTextureFromFileEx( //テクスチャの読み込み
		g_pd3dDevice, a_srcFile, m_width, m_height, D3DX_DEFAULT,
		0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture
	);
}

HRESULT ImagePolygon::loadLoadTexMem(const BYTE a_data[], DWORD a_size, D3DCOLOR a_keyColor)
{	//テクスチャの読み込み
	return D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, a_data, a_size, m_width, m_height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture);
}

HRESULT ImagePolygon::loadLoadTexRscFil(LPCTSTR a_pSrcFile,
		DWORD a_size, DWORD a_offset, D3DCOLOR a_keyColor)
{
	// データ読み込み
	FILE *fp = _tfopen(a_pSrcFile, _T("rb"));
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
	HRESULT
	hr = D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, data, a_size, m_width, m_height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture);
	SafeDeleteArray(data); // 一時バッファを解放
	return hr;
}

HRESULT ImagePolygon::loadLoadTexRsc(int a_id, D3DCOLOR a_keyColor)
{	//テクスチャの読み込み
	return D3DXCreateTextureFromResourceEx(
			g_pd3dDevice, NULL, MAKEINTRESOURCE(a_id), m_width, m_height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &m_ppTexture);
}

HRESULT ImagePolygon::copyVtx() {
	HRESULT hr;
	if (NULL == m_ppVtxBuf) {
		return E_FAIL;
	}
	if (FAILED(hr = m_ppVtxBuf->Lock(
		0,
		sizeof(VERTEX_2D) * 4,
		(void **)&m_pVtx, 0)))
	{
		m_ppVtxBuf->Unlock();
		return hr;
	}
	memcpy(m_pVtx, m_vtx, sizeof(VERTEX_2D) * 4);
	m_ppVtxBuf->Unlock();
	return S_OK;
}


HRESULT ImagePolygon::refer(ImageBase &a_obj) {
	m_isDrawable = false;
	if (NULL == a_obj.getTexture()) {
		Message(_T("空の画像を使用しようとしました"), _T("ImagePolygon::referTexture()"));
		return E_FAIL;
	}
	a_obj.getTexture()->AddRef();
	this->m_pReferTexture = &a_obj; //同じものを指すようにする
	if (NULL == this->m_pReferTexture) {
		Message(_T("画像の参照に失敗しました"), _T("Error"));
		return E_FAIL;
	}
	HRESULT hr;
	m_width  = a_obj.getImgWidth();
	m_height = a_obj.getImgHeight();
	m_cpos   = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化
	//頂点/頂点バッファ生成
	if (FAILED(hr = loadCreateVtx())) {
		return hr;
	}
	//頂点データコピー
	if (FAILED(hr = copyVtx())) {
		Message(_T("頂点バッファに書き込めませんでした"), _T("Error"));
		return hr;
	}
	m_isDrawable = true;
	return S_OK;
}

HRESULT ImagePolygon::draw() {
	if (not m_isDrawable) {
		return E_FAIL;
	}

	D3DXVECTOR3 DrPos = D3DXVECTOR3(0, 0, 0);
	if (m_blendMode != D3DBLEND_INVSRCALPHA) {
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, m_blendMode);
	}
	if (m_sampleModeU != D3DTADDRESS_WRAP) {
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, m_sampleModeU);
	}
	if (m_sampleModeV != D3DTADDRESS_WRAP) {
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, m_sampleModeU);
	}
	if (FAILED(drawSetTex()) ||
		FAILED(g_pd3dDevice->SetFVF(FVF_SETTING)) ||
		FAILED(g_pd3dDevice->SetStreamSource(0, m_ppVtxBuf, 0, sizeof(VERTEX_2D))) ||
		FAILED(g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2)))
	{
		Message(_T("画像の表示に失敗しました"), _T("Error"));
		m_isDrawable = false;
	}
	if (m_blendMode != D3DBLEND_INVSRCALPHA) {
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	if (m_sampleModeU != D3DTADDRESS_WRAP) {
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	}
	if (m_sampleModeV != D3DTADDRESS_WRAP) {
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	}
	if (m_isDrawable) {
		return S_OK;
	}
	return E_FAIL;
}
HRESULT ImagePolygon::drawSetTex() {
	if (NULL == m_pReferTexture) {
		if (FAILED(g_pd3dDevice->SetTexture(0, m_ppTexture))) {
			return E_FAIL;
		}
	}
	else {
		if (FAILED(g_pd3dDevice->SetTexture(0, m_pReferTexture->getTexture()))) {
			return E_FAIL;
		}
	}
	return S_OK;
}


HRESULT ImagePolygon::createEmptyTexture(DWORD a_width, DWORD a_height) {
	HRESULT hr;

	m_width  = a_width;  //幅設定
	m_height = a_height; //高さ設定
	m_cpos   = D3DXVECTOR3(m_width / 2.0f, m_height / 2.0f, 0.0f); //画像の中心を初期化

	//頂点/頂点バッファ生成
	if (FAILED(hr = loadCreateVtx())) {
		return E_FAIL;
	}

	//頂点データコピー
	if (FAILED(hr = copyVtx())) {
		Message(_T("頂点バッファに書き込めませんでした"), _T("Error"));
		return hr;
	}

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
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		case 2:
			Message(_T("空テクスチャの深度バッファ生成に失敗しました"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		case 3:
			Message(_T("空テクスチャのインターフェース取得に失敗しました"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		default:
			Message(_T("無効なパラメータ"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
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

HRESULT ImagePolygon::setRenderTarget(D3DCOLOR a_clearColor) {
	g_pd3dDevice->SetViewport(&m_vpSurf);
	g_pd3dDevice->SetRenderTarget(0, m_rtSurf);
	g_pd3dDevice->SetDepthStencilSurface(m_zbSurf);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		                a_clearColor, 1.0f, 0);
	return S_OK;
}




void ImagePolygon::trim(float a_left , float a_top,
	                    float a_right, float a_bottom,
                        float a_width, float a_height)
{
	m_vtx[0].m_u = a_left;
	m_vtx[0].m_v = a_top;
	m_vtx[1].m_x = m_vtx[0].m_x + a_width;
	m_vtx[1].m_u = a_right;
	m_vtx[1].m_v = a_top;
	m_vtx[2].m_y = m_vtx[0].m_y + a_height;
	m_vtx[2].m_u = a_left;
	m_vtx[2].m_v = a_bottom;
	m_vtx[3].m_x = m_vtx[0].m_x + a_width;
	m_vtx[3].m_y = m_vtx[0].m_y + a_height;
	m_vtx[3].m_u = a_right;
	m_vtx[3].m_v = a_bottom;
	copyVtx();
}

void ImagePolygon::trim(float a_left , float a_top,
	                    float a_right, float a_bottom)
{
	m_vtx[0].m_u = a_left;
	m_vtx[0].m_v = a_top;
	m_vtx[1].m_u = a_right;
	m_vtx[1].m_v = a_top;
	m_vtx[2].m_u = a_left;
	m_vtx[2].m_v = a_bottom;
	m_vtx[3].m_u = a_right;
	m_vtx[3].m_v = a_bottom;
	copyVtx();
}

void ImagePolygon::resize(float a_width, float a_height)
{
	auto hw = a_width  / 2.0f;
	auto hh = a_height / 2.0f;
	// 0(--)  1(+-)
	// 2(-+)  3(++)
//	m_vtx[0].m_x = m_cpos.x - hw;
//	m_vtx[0].m_y = m_cpos.y - hh;
//	m_vtx[1].m_x = m_cpos.x + hw;
//	m_vtx[1].m_y = m_vtx[0].m_y;
//	m_vtx[2].m_x = m_vtx[0].m_x;
//	m_vtx[2].m_y = m_cpos.y + hh;
//	m_vtx[3].m_x = m_vtx[1].m_x;
//	m_vtx[3].m_y = m_vtx[2].m_y;
//	copyVtx();
//	trim(m_pos.x - hw, m_pos.y - hh,
//		 m_pos.x + hw, m_pos.y + hh,
//		 a_width, a_height);
	trim(0.0f, 0.0f, 1.0f, 1.0f,
		 a_width, a_height);
}

void ImagePolygon::setDrawColor(D3DCOLOR a_color) {
	m_vtx[0].m_color = a_color;
	m_vtx[1].m_color = a_color;
	m_vtx[2].m_color = a_color;
	m_vtx[3].m_color = a_color;
	copyVtx();
}


void ImagePolygon::setAlphaBlendMode(D3DBLEND a_mode) {
	m_blendMode = a_mode;
}

void ImagePolygon::setWrappingMode(D3DTEXTUREADDRESS a_modeU, D3DTEXTUREADDRESS a_modeV) {
	m_sampleModeU = a_modeU;
	m_sampleModeV = a_modeV;
}

void ImagePolygon::setWrappingModeU(D3DTEXTUREADDRESS a_mode) {
	m_sampleModeU = a_mode;
}

void ImagePolygon::setWrappingModeV(D3DTEXTUREADDRESS a_mode) {
	m_sampleModeV = a_mode;
}




float ImagePolygon::getPolygonCX() {
	return m_rcpos.x;
}

float ImagePolygon::getPolygonCY() {
	return m_rcpos.y;
}

float ImagePolygon::getPolygonCZ() {
	return m_rcpos.z;
}




void ImagePolygon::setPos(float a_x, float a_y) {
	setPos(a_x, a_y, 0.0f);
}
void ImagePolygon::setPos(float a_x, float a_y, float a_z) {
	move(-(m_pos.x - a_x), -(m_pos.y - a_y), -(m_pos.z - a_z));
}

void ImagePolygon::setCenterPos(float a_cx, float a_cy) {
	setCenterPos(a_cx, a_cy, m_pos.z);
}
void ImagePolygon::setCenterPos(float a_cx, float a_cy, float a_cz) {
	m_rcpos = D3DXVECTOR3(a_cx, a_cy, a_cz);
}
void ImagePolygon::setCenterPosX(float a_cx) {
	m_rcpos.x = a_cx;
}
void ImagePolygon::setCenterPosY(float a_cy) {
	m_rcpos.y = a_cy;
}
void ImagePolygon::setCenterPosZ(float a_cz) {
	m_rcpos.z = a_cz;
}



//座標変換ここから
void ImagePolygon::move(float a_x, float a_y) {
	move(a_x, a_y, 0.0f);
}
void ImagePolygon::move(float a_x, float a_y, float a_z) {
	m_pos   += D3DXVECTOR3(a_x, a_y, a_z); //オブジェクトの座標を更新
	m_rcpos += D3DXVECTOR3(a_x, a_y, a_z); //    ↓
	D3DXMatrixIdentity(&m_mtrxMove); //行列の初期化
	D3DXMatrixTranslation(&m_mtrxMove, a_x, a_y, a_z); //変換行列を設定
	matrixFinallyA(m_mtrxMove); //座標変換
	copyVtx(); //全て変換し終わったら頂点バッファに書き込み
} //以下同じパターン

void ImagePolygon::scaling(float a_size) {
	scaling(a_size, a_size, 0.0f);
}
void ImagePolygon::scaling(float a_x, float a_y) {
	scaling(a_x, a_y, 0.0f);
}
void ImagePolygon::scaling(float a_x, float a_y, float a_z) {
	m_scale += D3DXVECTOR3(a_x, a_y, a_z);
	D3DXMatrixIdentity(&m_mtrxScale);
	D3DXMatrixScaling(&m_mtrxScale, 1.0f + a_x, 1.0f + a_y, 1.0f + a_z);
	matrixFinallyB(m_mtrxScale);
	copyVtx();
}

void ImagePolygon::rotate(float a_angleRad) {
	rotateZ(a_angleRad);
}
void ImagePolygon::rotate(Axis a_axis, float a_angleRad) {
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
		Message(_T("無効なパラメータ"), _T("GAME_SPRITE_2D::Rotate()"));
	}
}
void ImagePolygon::rotateX(float a_angleRad) {
	m_angle.x += a_angleRad;
	D3DXMatrixIdentity(&m_mtrxRotate);
	D3DXMatrixRotationX(&m_mtrxRotate, a_angleRad);
	matrixFinallyB(m_mtrxRotate);
	copyVtx();
}
void ImagePolygon::rotateY(float a_angleRad) {
	m_angle.y += a_angleRad;
	D3DXMatrixIdentity(&m_mtrxRotate);
	D3DXMatrixRotationY(&m_mtrxRotate, a_angleRad);
	matrixFinallyB(m_mtrxRotate);
	copyVtx();
}
void ImagePolygon::rotateZ(float a_angleRad) {
	m_angle.z += a_angleRad;
	D3DXMatrixIdentity(&m_mtrxRotate);
	D3DXMatrixRotationZ(&m_mtrxRotate, a_angleRad);
	matrixFinallyB(m_mtrxRotate);
	copyVtx();
}

void ImagePolygon::matrixFinallyA(D3DXMATRIX &a_matrix) {
	for (int vtxId = 0; vtxId < 4; ++vtxId) { //頂点毎に変換する必要がある(決め打ちの 4 は頂点数)
		D3DXMatrixTranslation(&m_mtrxPos, m_vtx[vtxId].m_x, m_vtx[vtxId].m_y, m_vtx[vtxId].m_z); //変換行列を設定
		m_mtrxPos *= a_matrix; //行列を乗算
		m_vtx[vtxId].m_x = m_mtrxPos._41; //変換後の座標を代入
		m_vtx[vtxId].m_y = m_mtrxPos._42; //    ｜
		m_vtx[vtxId].m_z = m_mtrxPos._43; //    ↓
	}
}
void ImagePolygon::matrixFinallyB(D3DXMATRIX &a_matrix) {
	moveForMFB(-m_rcpos.x, -m_rcpos.y, -m_rcpos.z); //原点へ移動
	for (int vtxId = 0; vtxId < 4; ++vtxId) { //for{}内はMFA()と同じ
		D3DXMatrixTranslation(&m_mtrxPos, m_vtx[vtxId].m_x, m_vtx[vtxId].m_y, m_vtx[vtxId].m_z);
		m_mtrxPos *= a_matrix;
		m_vtx[vtxId].m_x = m_mtrxPos._41;
		m_vtx[vtxId].m_y = m_mtrxPos._42;
		m_vtx[vtxId].m_z = m_mtrxPos._43;
	}
	moveForMFB(m_rcpos.x, m_rcpos.y, m_rcpos.z); //元の位置へ移動
}
void ImagePolygon::moveForMFB(float a_x, float a_y, float a_z) {
	D3DXMatrixIdentity(&m_mtrxMove);
	D3DXMatrixTranslation(&m_mtrxMove, a_x, a_y, a_z);
	matrixFinallyA(m_mtrxMove);
}

void ImagePolygon::reset() {
	m_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rcpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float nx = (float)m_width  / 2.0f;
	float ny = (float)m_height / 2.0f;
	m_vtx[0].m_x = -nx  ;
	m_vtx[0].m_y = -ny  ;
	m_vtx[0].m_z =  0.0f;
	m_vtx[1].m_x =  nx  ;
	m_vtx[1].m_y = -ny  ;
	m_vtx[1].m_z =  0.0f;
	m_vtx[2].m_x = -nx  ;
	m_vtx[2].m_y =  ny  ;
	m_vtx[2].m_z =  0.0f;
	m_vtx[3].m_x =  nx  ;
	m_vtx[3].m_y =  ny  ;
	m_vtx[3].m_z =  0.0f;
	copyVtx();
}

void ImagePolygon::resetScale() {
	float nx = (float)m_width  / 2.0f    ;
	float ny = (float)m_height / 2.0f    ;
	m_vtx[0].m_x = m_rcpos.x - (nx   - m_scale.x);
	m_vtx[0].m_y = m_rcpos.y - (ny   - m_scale.y);
	m_vtx[0].m_z = m_rcpos.z + (1.0f - m_scale.z);
	m_vtx[1].m_x = m_rcpos.x + (nx   - m_scale.x);
	m_vtx[1].m_y = m_rcpos.y - (ny   - m_scale.y);
	m_vtx[1].m_z = m_rcpos.z + (1.0f - m_scale.z);
	m_vtx[2].m_x = m_rcpos.x - (nx   - m_scale.x);
	m_vtx[2].m_y = m_rcpos.y + (ny   - m_scale.y);
	m_vtx[2].m_z = m_rcpos.z + (1.0f - m_scale.z);
	m_vtx[3].m_x = m_rcpos.x + (nx   - m_scale.x);
	m_vtx[3].m_y = m_rcpos.y + (ny   - m_scale.y);
	m_vtx[3].m_z = m_rcpos.z + (1.0f - m_scale.z);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	copyVtx();
}

void ImagePolygon::resetAngle() {
	rotate(Axis::X, -m_angle.x);
	rotate(Axis::Y, -m_angle.y);
	rotate(Axis::Z, -m_angle.z);
	m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void ImagePolygon::resetAngleX() {
	rotateX(-m_angle.x);
	m_angle.x = 0.0f;
}
void ImagePolygon::resetAngleY() {
	rotateY(-m_angle.y);
	m_angle.y = 0.0f;
}
void ImagePolygon::resetAngleZ() {
	rotateZ(-m_angle.z);
	m_angle.z = 0.0f;
}

void ImagePolygon::moveUV(float a_u, float a_v) {
	m_vtx[0].m_u += a_u;
	m_vtx[0].m_v += a_v;
	m_vtx[1].m_u += a_u;
	m_vtx[1].m_v += a_v;
	m_vtx[2].m_u += a_u;
	m_vtx[2].m_v += a_v;
	m_vtx[3].m_u += a_u;
	m_vtx[3].m_v += a_v;
	copyVtx();
}
void ImagePolygon::moveU(float a_u) {
	m_vtx[0].m_u += a_u;
	m_vtx[1].m_u += a_u;
	m_vtx[2].m_u += a_u;
	m_vtx[3].m_u += a_u;
	copyVtx();
}
void ImagePolygon::moveV(float a_v) {
	m_vtx[0].m_v += a_v;
	m_vtx[1].m_v += a_v;
	m_vtx[2].m_v += a_v;
	m_vtx[3].m_v += a_v;
	copyVtx();
}







ImagePolygon::ImagePolygon() :
	m_ppVtxBuf(nullptr),
	m_rcpos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_sampleModeU(D3DTADDRESS_WRAP),
	m_sampleModeV(D3DTADDRESS_WRAP),
	m_pVtx(nullptr)
{
	D3DXMatrixIdentity(&m_mtrxPos);
}

ImagePolygon::~ImagePolygon() {
	SafeRelease(m_ppVtxBuf);
}