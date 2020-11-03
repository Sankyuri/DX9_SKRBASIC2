//#include "..\header\SKRGameCommon.h"
#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#include "..\header\ImagePolygon.h"

using namespace skrBasic;

#define FVF_SETTING (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)


HRESULT ImagePolygon::load(LPCTSTR a_srcFile,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//���_�f�[�^�R�s�[
	if (E_FAIL == load_Common(a_width, a_height)) {
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	if (FAILED(load_LoadTex(a_srcFile, a_keyColor))) {
		Message(_T("�摜�̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		isCanDraw = false; //���s�������͕`�揈�������Ȃ�����
		return E_FAIL;
	}
	
	isCanDraw = true;
	return S_OK;
}

HRESULT ImagePolygon::loadFromMemory(const CHAR a_data[], DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//���_�f�[�^�R�s�[
	if (E_FAIL == load_Common(a_width, a_height)) {
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	if (FAILED(load_LoadTexMem(a_data, a_size, a_keyColor))) {
		Message(_T("�摜�̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		isCanDraw = false; //���s�������͕`�揈�������Ȃ�����
		return E_FAIL;
	}
	
	isCanDraw = true;
	return S_OK;
}

HRESULT ImagePolygon::loadFromResourceFile(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//���_�f�[�^�R�s�[
	if (E_FAIL == load_Common(a_width, a_height)) {
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	if (FAILED(load_LoadTexRscFil(a_pSrcFile, a_size, a_offset, a_keyColor))) {
		Message(_T("�摜�̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		isCanDraw = false; //���s�������͕`�揈�������Ȃ�����
		return E_FAIL;
	}
	
	isCanDraw = true;
	return S_OK;
}

HRESULT ImagePolygon::loadFromResource(int a_id,
		DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor)
{
	//���_�f�[�^�R�s�[
	if (E_FAIL == load_Common(a_width, a_height)) {
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	if (FAILED(load_LoadTexRsc(a_id, a_keyColor))) {
		Message(_T("�摜�̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		isCanDraw = false; //���s�������͕`�揈�������Ȃ�����
		return E_FAIL;
	}
	
	isCanDraw = true;
	return S_OK;
}


HRESULT ImagePolygon::load_Common(DWORD a_width, DWORD a_height)
{
	width  = a_width;  //���ݒ�
	height = a_height; //�����ݒ�
	cpos   = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //�摜�̒��S��������
	//���_/���_�o�b�t�@����
	if (FAILED(load_CreateVtx())) {
		return E_FAIL;
	}
	//���_�f�[�^�R�s�[
	if (FAILED(copyVtx())) {
		Message(_T("���_�o�b�t�@�ɏ������߂܂���ł���"), _T("Error"));
		return E_FAIL;
	}
	return S_OK;
}

HRESULT ImagePolygon::load_CreateVtx() {
	HRESULT hr;
	//
	//  0 __ 1
	//   : /:  �A���t�@�x�b�g�� Z ��
	//   :/ :  �������ԂŃX�g���b�v�Œ�`
	//  2 �P 3
	//
	float nw = (float)width / 2.0f - 0.25f;
	float nh = (float)height / 2.0f - 0.25f;
	//vtx[n] = { x, y, z, rhw, color, u, v};
	vtx[0] = { -nw - 0.5f, -nh - 0.5f, 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f };
	vtx[1] = {  nw       , -nh - 0.5f, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f };
	vtx[2] = { -nw - 0.5f,  nh       , 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f };
	vtx[3] = {  nw       ,  nh       , 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f };

	//���_�o�b�t�@����
	if (FAILED(hr = load_CreateVtxBuf())) {
		switch (hr) {
		case D3DERR_OUTOFVIDEOMEMORY:
			Message(_T("���_�o�b�t�@�̐����Ɏ��s���܂����B\n�r�f�I�������s���ł�"),
					_T("Error"));
			break;
		case E_OUTOFMEMORY:
			Message(_T("���_�o�b�t�@�̐����Ɏ��s���܂����B\n�������s���ł�"),
					_T("Error"));
			break;
		default:
			Message(_T("���_�o�b�t�@�̐����Ɏ��s���܂���"),
					_T("Error"));
			break;
		}
		isCanDraw = false;
		return E_FAIL; //�������s�����Ȃ̂Ŕ�����
	}
	return S_OK;
}

HRESULT ImagePolygon::load_CreateVtxBuf() {
	return g_pd3dDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_SETTING,
		D3DPOOL_MANAGED,
		&ppVtxBuf,
		NULL
	);
}

HRESULT ImagePolygon::load_LoadTex(LPCTSTR a_srcFile, D3DCOLOR a_keyColor) {
	return D3DXCreateTextureFromFileEx( //�e�N�X�`���̓ǂݍ���
		g_pd3dDevice, a_srcFile, width, height, D3DX_DEFAULT,
		0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture
	);
}

HRESULT ImagePolygon::load_LoadTexMem(const CHAR a_data[], DWORD a_size, D3DCOLOR a_keyColor)
{	//�e�N�X�`���̓ǂݍ���
	return D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, a_data, a_size, width, height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture);
}

HRESULT ImagePolygon::load_LoadTexRscFil(LPCTSTR a_pSrcFile,
		DWORD a_size, DWORD a_offset, D3DCOLOR a_keyColor)
{
	// �f�[�^�ǂݍ���
	FILE *fp = _tfopen(a_pSrcFile, _T("rb"));
	if (NULL == fp) {
		Message(_T("�摜�̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}
	char *data = new char[a_size]; // �ꎞ�o�b�t�@���쐬
	fseek(fp, a_offset, SEEK_SET); // �I�t�Z�b�g�������i�߂�
	if (a_size != fread(data, sizeof(char), a_size, fp)) { // �f�[�^�ǂݍ���
		Message(_T("�摜�f�[�^�̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		SafeDeleteArray(data); // �ꎞ�o�b�t�@�����
		return E_FAIL;
	}
	HRESULT
	hr = D3DXCreateTextureFromFileInMemoryEx(
			g_pd3dDevice, data, a_size, width, height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture);
	SafeDeleteArray(data); // �ꎞ�o�b�t�@�����
	return hr;
}

HRESULT ImagePolygon::load_LoadTexRsc(int a_id, D3DCOLOR a_keyColor)
{	//�e�N�X�`���̓ǂݍ���
	return D3DXCreateTextureFromResourceEx(
			g_pd3dDevice, NULL, MAKEINTRESOURCE(a_id), width, height, D3DX_DEFAULT,
			0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
			D3DX_FILTER_NONE, a_keyColor, NULL, NULL, &ppTexture);
}

HRESULT ImagePolygon::copyVtx() {
	HRESULT hr;
	if (NULL == ppVtxBuf) {
		return E_FAIL;
	}
	if (FAILED(hr = ppVtxBuf->Lock(
		0,
		sizeof(VERTEX_2D) * 4,
		(void **)&pVtx, 0)))
	{
		ppVtxBuf->Unlock();
		return hr;
	}
	memcpy(pVtx, vtx, sizeof(VERTEX_2D) * 4);
	ppVtxBuf->Unlock();
	return S_OK;
}


HRESULT ImagePolygon::refer(ImageBase *a_obj) {
	isCanDraw = false;
	if (NULL == a_obj->getTexture()) {
		Message(_T("��̉摜���g�p���悤�Ƃ��܂���"), _T("ImagePolygon::referTexture()"));
		return E_FAIL;
	}
	a_obj->getTexture()->AddRef();
	this->pReferTexture = a_obj; //�������̂��w���悤�ɂ���
	if (NULL == this->pReferTexture) {
		Message(_T("�摜�̎Q�ƂɎ��s���܂���"), _T("Error"));
		return E_FAIL;
	}
	HRESULT hr;
	width  = a_obj->getImgWidth();
	height = a_obj->getImgHeight();
	cpos   = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //�摜�̒��S��������
	//���_/���_�o�b�t�@����
	if (FAILED(hr = load_CreateVtx())) {
		return hr;
	}
	//���_�f�[�^�R�s�[
	if (FAILED(hr = copyVtx())) {
		Message(_T("���_�o�b�t�@�ɏ������߂܂���ł���"), _T("Error"));
		return hr;
	}
	isCanDraw = true;
	return S_OK;
}

HRESULT ImagePolygon::draw() {
	if (false == isCanDraw) {
		return E_FAIL;
	}

	D3DXVECTOR3 DrPos = D3DXVECTOR3(0, 0, 0);
	if (blendMode != D3DBLEND_INVSRCALPHA) {
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, blendMode);
	}
	if (sampleModeU != D3DTADDRESS_WRAP) {
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, sampleModeU);
	}
	if (sampleModeV != D3DTADDRESS_WRAP) {
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, sampleModeU);
	}
	if (FAILED(draw_SetTex()) ||
		FAILED(g_pd3dDevice->SetFVF(FVF_SETTING)) ||
		FAILED(g_pd3dDevice->SetStreamSource(0, ppVtxBuf, 0, sizeof(VERTEX_2D))) ||
		FAILED(g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2)))
	{
		Message(_T("�摜�̕\���Ɏ��s���܂���"), _T("Error"));
		isCanDraw = false;
	}
	if (blendMode != D3DBLEND_INVSRCALPHA) {
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	if (isCanDraw) {
		return S_OK;
	}
	else {
		return E_FAIL;
	}
}
HRESULT ImagePolygon::draw_SetTex() {
	if (NULL == pReferTexture) {
		if (FAILED(g_pd3dDevice->SetTexture(0, ppTexture))) {
			return E_FAIL;
		}
	}
	else {
		if (FAILED(g_pd3dDevice->SetTexture(0, pReferTexture->getTexture()))) {
			return E_FAIL;
		}
	}
	return S_OK;
}


HRESULT ImagePolygon::createEmptyTexture(DWORD a_width, DWORD a_height) {
	HRESULT hr;

	width  = a_width;  //���ݒ�
	height = a_height; //�����ݒ�
	cpos   = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0.0f); //�摜�̒��S��������

	//���_/���_�o�b�t�@����
	if (FAILED(hr = load_CreateVtx())) {
		return E_FAIL;
	}

	//���_�f�[�^�R�s�[
	if (FAILED(hr = copyVtx())) {
		Message(_T("���_�o�b�t�@�ɏ������߂܂���ł���"), _T("Error"));
		return hr;
	}

	//��e�N�X�`������
	try {
		//�e�N�X�`���{�̐���
		if (FAILED(g_pd3dDevice->CreateTexture(
			width, height, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &ppTexture, NULL))) throw(1);
		//�[�x�o�b�t�@�쐬
		if (FAILED(g_pd3dDevice->CreateDepthStencilSurface(
			width, height, D3DFMT_D16,
			D3DMULTISAMPLE_NONE, 0, 1, &zbSurf, NULL))) throw(2);
		//�e�N�X�`���̃C���^�[�t�F�[�X�擾
		if (FAILED(ppTexture->GetSurfaceLevel(0, &rtSurf))) throw(3);
	}
	catch (int res) {
		switch (res) {
		case 1:
			Message(_T("��e�N�X�`���̃e�N�X�`�������Ɏ��s���܂���"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		case 2:
			Message(_T("��e�N�X�`���̐[�x�o�b�t�@�����Ɏ��s���܂���"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		case 3:
			Message(_T("��e�N�X�`���̃C���^�[�t�F�[�X�擾�Ɏ��s���܂���"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		default:
			Message(_T("�����ȃp�����[�^"),
				    _T("Error:ImagePolygon::createEmptyTexture()"));
			break;
		}
		isCanDraw = false; //���s�������͕`�揈�������Ȃ�����
		return E_FAIL;
	}

	//�r���[�|�[�g�ݒ�
	vpSurf.X      = 0;
	vpSurf.Y      = 0;
	vpSurf.Width  = width;
	vpSurf.Height = height;
	vpSurf.MinZ   = 0.0f;
	vpSurf.MaxZ   = 1.0f;

	isCanDraw = true;
	return S_OK;
}

HRESULT ImagePolygon::setRenderTarget(D3DCOLOR a_clearColor) {
	g_pd3dDevice->SetViewport(&vpSurf);
	g_pd3dDevice->SetRenderTarget(0, rtSurf);
	g_pd3dDevice->SetDepthStencilSurface(zbSurf);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		                a_clearColor, 1.0f, 0);
	return S_OK;
}




/*void IMAGE_POLYGON::TrimTexture(const RECT *rc) {
	vtx[0].u = rc->left;
	vtx[0].v = rc->top;
	vtx[1].u = rc->right;
	vtx[1].v = rc->top;
	vtx[2].u = rc->left;
	vtx[2].v = rc->bottom;
	vtx[3].u = rc->right;
	vtx[3].v = rc->bottom;
	CopyVtx();
}*/
void ImagePolygon::trim(float a_left , float a_top,
	                    float a_right, float a_bottom,
                        float a_width, float a_height)
{
	vtx[0].u = a_left;
	vtx[0].v = a_top;
	vtx[1].x = vtx[0].x + a_width;
	vtx[1].u = a_right;
	vtx[1].v = a_top;
	vtx[2].y = vtx[0].y + a_height;
	vtx[2].u = a_left;
	vtx[2].v = a_bottom;
	vtx[3].x = vtx[0].x + a_width;
	vtx[3].y = vtx[0].y + a_height;
	vtx[3].u = a_right;
	vtx[3].v = a_bottom;
	copyVtx();
}

void ImagePolygon::setDrawColor(D3DCOLOR a_color) {
	vtx[0].color = a_color;
	vtx[1].color = a_color;
	vtx[2].color = a_color;
	vtx[3].color = a_color;
	copyVtx();
}


void ImagePolygon::setAlphaBlendMode(D3DBLEND a_mode) {
	blendMode = a_mode;
}

void ImagePolygon::setWrappingMode(D3DTEXTUREADDRESS a_modeU, D3DTEXTUREADDRESS a_modeV) {
	sampleModeU = a_modeU;
	sampleModeV = a_modeV;
}

void ImagePolygon::setWrappingModeU(D3DTEXTUREADDRESS a_mode) {
	sampleModeU = a_mode;
}

void ImagePolygon::setWrappingModeV(D3DTEXTUREADDRESS a_mode) {
	sampleModeV = a_mode;
}




float ImagePolygon::getPolygonCX() {
	return rcpos.x;
}

float ImagePolygon::getPolygonCY() {
	return rcpos.y;
}

float ImagePolygon::getPolygonCZ() {
	return rcpos.z;
}




void ImagePolygon::setPos(float a_x, float a_y) {
	setPos(a_x, a_y, 0.0f);
}
void ImagePolygon::setPos(float a_x, float a_y, float a_z) {
	move(-(pos.x - a_x), -(pos.y - a_y), -(pos.z - a_z));
}

void ImagePolygon::setCenterPos(float a_cx, float a_cy) {
	setCenterPos(a_cx, a_cy, pos.z);
}
void ImagePolygon::setCenterPos(float a_cx, float a_cy, float a_cz) {
	rcpos = D3DXVECTOR3(a_cx, a_cy, a_cz);
}
void ImagePolygon::setCenterPosX(float a_cx) {
	rcpos.x = a_cx;
}
void ImagePolygon::setCenterPosY(float a_cy) {
	rcpos.y = a_cy;
}
void ImagePolygon::setCenterPosZ(float a_cz) {
	rcpos.z = a_cz;
}



//���W�ϊ���������
void ImagePolygon::move(float a_x, float a_y) {
	move(a_x, a_y, 0.0f);
}
void ImagePolygon::move(float a_x, float a_y, float a_z) {
	pos   += D3DXVECTOR3(a_x, a_y, a_z); //�I�u�W�F�N�g�̍��W���X�V
	rcpos += D3DXVECTOR3(a_x, a_y, a_z); //    ��
	D3DXMatrixIdentity(&mtrx_move); //�s��̏�����
	D3DXMatrixTranslation(&mtrx_move, a_x, a_y, a_z); //�ϊ��s���ݒ�
	matrixFinallyA(&mtrx_move); //���W�ϊ�
	copyVtx(); //�S�ĕϊ����I������璸�_�o�b�t�@�ɏ�������
} //�ȉ������p�^�[��

void ImagePolygon::scaling(float a_size) {
	scaling(a_size, a_size, 0.0f);
}
void ImagePolygon::scaling(float a_x, float a_y) {
	scaling(a_x, a_y, 0.0f);
}
void ImagePolygon::scaling(float a_x, float a_y, float a_z) {
	scale += D3DXVECTOR3(a_x, a_y, a_z);
	D3DXMatrixIdentity(&mtrx_scale);
	D3DXMatrixScaling(&mtrx_scale, 1.0f + a_x, 1.0f + a_y, 1.0f + a_z);
	matrixFinallyB(&mtrx_scale);
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
		Message(_T("�����ȃp�����[�^"), _T("GAME_SPRITE_2D::Rotate()"));
	}
}
void ImagePolygon::rotateX(float a_angleRad) {
	angle.x += a_angleRad;
	D3DXMatrixIdentity(&mtrx_rotate);
	D3DXMatrixRotationX(&mtrx_rotate, a_angleRad);
	matrixFinallyB(&mtrx_rotate);
	copyVtx();
}
void ImagePolygon::rotateY(float a_angleRad) {
	angle.y += a_angleRad;
	D3DXMatrixIdentity(&mtrx_rotate);
	D3DXMatrixRotationY(&mtrx_rotate, a_angleRad);
	matrixFinallyB(&mtrx_rotate);
	copyVtx();
}
void ImagePolygon::rotateZ(float a_angleRad) {
	angle.z += a_angleRad;
	D3DXMatrixIdentity(&mtrx_rotate);
	D3DXMatrixRotationZ(&mtrx_rotate, a_angleRad);
	matrixFinallyB(&mtrx_rotate);
	copyVtx();
}

void ImagePolygon::matrixFinallyA(D3DXMATRIX *a_matrix) {
	for (int vtxId = 0; vtxId < 4; ++vtxId) { //���_���ɕϊ�����K�v������(���ߑł��� 4 �͒��_��)
		D3DXMatrixTranslation(&mtrx_pos, vtx[vtxId].x, vtx[vtxId].y, vtx[vtxId].z); //�ϊ��s���ݒ�
		mtrx_pos *= *a_matrix; //�s�����Z
		vtx[vtxId].x = mtrx_pos._41; //�ϊ���̍��W����
		vtx[vtxId].y = mtrx_pos._42; //    �b
		vtx[vtxId].z = mtrx_pos._43; //    ��
	}
}
void ImagePolygon::matrixFinallyB(D3DXMATRIX *a_matrix) {
	moveForMFB(-rcpos.x, -rcpos.y, -rcpos.z); //���_�ֈړ�
	for (int vtxId = 0; vtxId < 4; ++vtxId) { //for{}����MFA()�Ɠ���
		D3DXMatrixTranslation(&mtrx_pos, vtx[vtxId].x, vtx[vtxId].y, vtx[vtxId].z);
		mtrx_pos *= *a_matrix;
		vtx[vtxId].x = mtrx_pos._41;
		vtx[vtxId].y = mtrx_pos._42;
		vtx[vtxId].z = mtrx_pos._43;
	}
	moveForMFB(rcpos.x, rcpos.y, rcpos.z); //���̈ʒu�ֈړ�
}
void ImagePolygon::moveForMFB(float a_x, float a_y, float a_z) {
	D3DXMatrixIdentity(&mtrx_move);
	D3DXMatrixTranslation(&mtrx_move, a_x, a_y, a_z);
	matrixFinallyA(&mtrx_move);
}

void ImagePolygon::reset() {
	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rcpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float nx = (float)width  / 2.0f;
	float ny = (float)height / 2.0f;
	vtx[0].x = -nx  ;
	vtx[0].y = -ny  ;
	vtx[0].z =  0.0f;
	vtx[1].x =  nx  ;
	vtx[1].y = -ny  ;
	vtx[1].z =  0.0f;
	vtx[2].x = -nx  ;
	vtx[2].y =  ny  ;
	vtx[2].z =  0.0f;
	vtx[3].x =  nx  ;
	vtx[3].y =  ny  ;
	vtx[3].z =  0.0f;
	copyVtx();
}

void ImagePolygon::resetScale() {
	float nx = (float)width  / 2.0f    ;
	float ny = (float)height / 2.0f    ;
	vtx[0].x = rcpos.x - (nx   - scale.x);
	vtx[0].y = rcpos.y - (ny   - scale.y);
	vtx[0].z = rcpos.z + (1.0f - scale.z);
	vtx[1].x = rcpos.x + (nx   - scale.x);
	vtx[1].y = rcpos.y - (ny   - scale.y);
	vtx[1].z = rcpos.z + (1.0f - scale.z);
	vtx[2].x = rcpos.x - (nx   - scale.x);
	vtx[2].y = rcpos.y + (ny   - scale.y);
	vtx[2].z = rcpos.z + (1.0f - scale.z);
	vtx[3].x = rcpos.x + (nx   - scale.x);
	vtx[3].y = rcpos.y + (ny   - scale.y);
	vtx[3].z = rcpos.z + (1.0f - scale.z);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	copyVtx();
}

void ImagePolygon::resetAngle() {
	rotate(Axis::X, -angle.x);
	rotate(Axis::Y, -angle.y);
	rotate(Axis::Z, -angle.z);
	angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void ImagePolygon::resetAngleX() {
	rotateX(-angle.x);
	angle.x = 0.0f;
}
void ImagePolygon::resetAngleY() {
	rotateY(-angle.y);
	angle.y = 0.0f;
}
void ImagePolygon::resetAngleZ() {
	rotateZ(-angle.z);
	angle.z = 0.0f;
}

void ImagePolygon::moveUV(float a_u, float a_v) {
	vtx[0].u += a_u;
	vtx[0].v += a_v;
	vtx[1].u += a_u;
	vtx[1].v += a_v;
	vtx[2].u += a_u;
	vtx[2].v += a_v;
	vtx[3].u += a_u;
	vtx[3].v += a_v;
	copyVtx();
}
void ImagePolygon::moveU(float a_u) {
	vtx[0].u += a_u;
	vtx[1].u += a_u;
	vtx[2].u += a_u;
	vtx[3].u += a_u;
	copyVtx();
}
void ImagePolygon::moveV(float a_v) {
	vtx[0].v += a_v;
	vtx[1].v += a_v;
	vtx[2].v += a_v;
	vtx[3].v += a_v;
	copyVtx();
}







ImagePolygon::ImagePolygon() {
	pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���݂̍��W�� (0, 0) �ɏ�����
	cpos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rcpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mtrx_move);
	D3DXMatrixIdentity(&mtrx_scale);
	D3DXMatrixIdentity(&mtrx_rotate);
	D3DXMatrixIdentity(&mtrx_pos);
	blendMode     = D3DBLEND_INVSRCALPHA; //�A���t�@�u�����h�̕��@�̐ݒ�
	sampleModeU   = sampleModeV = D3DTADDRESS_WRAP;
	pReferTexture = NULL;
	ppVtxBuf      = NULL;
	ppTexture     = NULL;
}

ImagePolygon::~ImagePolygon() {
	SafeRelease(ppVtxBuf);
	SafeRelease(ppTexture);
}