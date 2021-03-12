//#include "..\header\SKRGameCommon.h"
#include "..\header\systemExtern.h"
#include "..\header\Sound.h"
#include "..\header\Basic.h"
#include "..\header\SystemParam.h"

using namespace skrBasic;

#define __PBUF_FLAG ( DSBCAPS_CTRLVOLUME    | \
					  DSBCAPS_STICKYFOCUS   | \
					  DSBCAPS_PRIMARYBUFFER)
#define __SBUF_FLAG ( DSBCAPS_GETCURRENTPOSITION2 | \
					  DSBCAPS_STATIC              | \
					  DSBCAPS_STICKYFOCUS         | \
					  DSBCAPS_CTRLVOLUME)

static HRESULT InitDSBufBuffer();
static HRESULT InitDSBufFmtWave(DWORD a_samplingRate);

void InitDSound(DWORD a_samplingRate){
	DirectSoundCreate8(nullptr, &g_pDSound, nullptr);
	if (g_pDSound != nullptr) {
		if (SUCCEEDED(g_pDSound->SetCooperativeLevel(g_hWnd, DSSCL_EXCLUSIVE))) {
			if (SUCCEEDED(InitDSBufBuffer())) {
				if (SUCCEEDED(InitDSBufFmtWave(a_samplingRate))) {
					return;
				}
			}
		}
		return; //http://marupeke296.com/DS_No1_PlaySound.html
	} //�Q�l�F http://www.charatsoft.com/develop/otogema/page/06sound/ds.html
	Message(_T("�����f�o�C�X�̍쐬�Ɏ��s���܂���"), _T("Error"));
}
//�v���C�}���o�b�t�@�̐ݒ�
static HRESULT InitDSBufBuffer() {
	HRESULT hr;
	DSBUFFERDESC pDSDesc = { 0 };
	pDSDesc.dwSize = sizeof(DSBUFFERDESC);
	pDSDesc.dwFlags = __PBUF_FLAG;
	pDSDesc.dwBufferBytes = 0;
	pDSDesc.lpwfxFormat = NULL;
	if (FAILED(hr = g_pDSound->CreateSoundBuffer(&pDSDesc, &g_pDSBuf, NULL))) {
		Message(_T("�v���C�}���T�E���h�o�b�t�@�̐����Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}
	return S_OK;
}
//�v���C�}���o�b�t�@��Wave Format�̐ݒ�
static HRESULT InitDSBufFmtWave(DWORD a_samplingRate) {
	HRESULT hr;
	WAVEFORMATEX pcmWavFmt;
	ZeroMemory(&pcmWavFmt, sizeof(WAVEFORMATEX));
	pcmWavFmt.cbSize          = sizeof(WAVEFORMATEX);
	pcmWavFmt.wFormatTag      = WAVE_FORMAT_PCM;
	pcmWavFmt.nChannels       = 2;    //�`�����l����
	pcmWavFmt.nSamplesPerSec  = a_samplingRate; //�T���v�����O���[�g
	pcmWavFmt.wBitsPerSample  = 16;
	pcmWavFmt.nBlockAlign     = pcmWavFmt.nChannels * pcmWavFmt.wBitsPerSample / 8;
	pcmWavFmt.nAvgBytesPerSec = pcmWavFmt.nSamplesPerSec * pcmWavFmt.nBlockAlign;
	if (FAILED(hr = g_pDSBuf->SetFormat(&pcmWavFmt))) {
		Message(_T("�������̐ݒ�Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}
	return S_OK;
}




HRESULT Sound::dSoundCreateSecondaryBuffer(DWORD a_rate, float a_lengthSec) {
	HRESULT hr;
	WAVEFORMATEX        tmpWavFmt = { 0 };
	DSBUFFERDESC        tmpDesc   = { 0 };
	LPDIRECTSOUNDBUFFER ptmpBuf   = nullptr;

	tmpWavFmt.cbSize          = sizeof(WAVEFORMATEX);
	tmpWavFmt.wFormatTag      = WAVE_FORMAT_PCM;
	tmpWavFmt.nChannels       = 2;    //�`�����l����
	tmpWavFmt.nSamplesPerSec  = a_rate; //�T���v�����O���[�g
	tmpWavFmt.wBitsPerSample  = 16;
	tmpWavFmt.nBlockAlign     = tmpWavFmt.nChannels * tmpWavFmt.wBitsPerSample / 8;
	tmpWavFmt.nAvgBytesPerSec = tmpWavFmt.nSamplesPerSec * tmpWavFmt.nBlockAlign;

	tmpDesc.dwSize          = sizeof(DSBUFFERDESC);
	tmpDesc.dwFlags         = __SBUF_FLAG;
	tmpDesc.dwBufferBytes   = (float)tmpWavFmt.nAvgBytesPerSec * a_lengthSec;
	tmpDesc.lpwfxFormat     = &tmpWavFmt;
	tmpDesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	hr = g_pDSound->CreateSoundBuffer(&tmpDesc, &ptmpBuf, nullptr);
	if (FAILED(hr) || nullptr == ptmpBuf) {
		Message(_T("�Z�J���_���T�E���h�o�b�t�@�̐����Ɏ��s���܂���(DSB)"), _T("Error"));
		return E_FAIL;
	}
	hr = ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void **)&m_pDSSecBuf);
	if (FAILED(hr)) {
		Message(_T("�Z�J���_���T�E���h�o�b�t�@�̐����Ɏ��s���܂���(DSB8)"), _T("Error"));
		ptmpBuf->Release();
		return E_FAIL;
	}
	ptmpBuf->Release();
	return S_OK;
}

HRESULT Sound::dSoundLockBuf() {
	HRESULT hr;
	if (FAILED(hr = m_pDSSecBuf->Lock(0, m_mmdatck.cksize, &m_lpvPtr1,
		                            &m_dwBytes1, &m_lpvPtr2, &m_dwBytes2, 0)))
	{
		m_pDSSecBuf->Restore();
		if (FAILED(hr = m_pDSSecBuf->Lock(0, m_mmdatck.cksize, &m_lpvPtr1,
			                            &m_dwBytes1, &m_lpvPtr2, &m_dwBytes2, 0)))
		{
			Message(_T("�T�E���h�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("Error"));
			return E_FAIL;
		}
	}
	return S_OK;
}
HRESULT Sound::dSoundUnlockBuf() {
	if (FAILED(m_pDSSecBuf->Unlock(m_lpvPtr1, m_dwBytes1, m_lpvPtr2, m_dwBytes2))) {
		Message(_T("�T�E���h�o�b�t�@�̃A�����b�N�Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}
	return S_OK;
}


HRESULT Sound::load(LPCTSTR a_pSrcFile, DWORD a_loopStart, DWORD a_loopEnd)
{
	if (E_FAIL == dSoundOpenFile(const_cast<LPTSTR>(a_pSrcFile))) {
		mmioClose(m_hMmio, 0);
		return E_FAIL;
	}
	mmioClose(m_hMmio, 0);

	//�Ȃ̒���(sec)�����߂�(���o�[�W������ a_lenthSec �ɓ�����)
	float length = (float)(m_mmrifck.cksize + m_mmrifck.dwDataOffset) /
		           (float)m_wavfmtex.nAvgBytesPerSec;

	//�o�b�t�@�����O
	if (FAILED(dSoundCreateSecondaryBuffer(m_wavfmtex.nSamplesPerSec, length)) ||
		FAILED(dSoundLockBuf()))
	{
		return E_FAIL;
	}

	memcpy(m_lpvPtr1, m_pData, m_mmdatck.cksize);
	dSoundUnlockBuf();
	setCustomLoop(a_loopStart, a_loopEnd);
	m_isPlayable = true;

	return S_OK;
}

HRESULT Sound::loadFromResourceFile(LPCTSTR a_pSrcFile,
		DWORD a_size, DWORD a_offset, DWORD a_loopStart, DWORD a_loopEnd)
{
	m_hMmio = mmioOpen(const_cast<LPTSTR>(a_pSrcFile), &m_mmInfo, MMIO_READ);
	//�����t�@�C���J��
	if (nullptr == m_hMmio) {
		Message(_T("�����t�@�C�����J���܂���ł���"), _T("Error"));
		return E_FAIL;
	}

	//�����f�[�^�i�[
	m_pData = new BYTE[a_size]; // �o�b�t�@�쐬
	mmioSeek(m_hMmio, a_offset, SEEK_SET); // �I�t�Z�b�g�����炷
	if (mmioRead(m_hMmio, (HPSTR)m_pData, a_size) != a_size) { // �ǂݍ���
		Message(_T("�����t�@�C�����i�[�ł��܂���ł���"), _T("Error"));
		delete[] m_pData;
		mmioClose(m_hMmio, 0);
		return E_FAIL;
	}
	mmioClose(m_hMmio, 0);

	//�Ȃ̒���(sec)�����߂ăo�b�t�@�����O
	DWORD smpRate = SystemParam::getDSPBufSamplingRate();
	m_wavfmtex.nChannels      = 2;
	m_wavfmtex.wBitsPerSample = 16;
	m_wavfmtex.nSamplesPerSec = smpRate;
	m_mmdatck.cksize          = a_size;
	float length = m_mmdatck.cksize
			/ ((m_wavfmtex.nChannels * m_wavfmtex.wBitsPerSample / 8.0f)
				* m_wavfmtex.nSamplesPerSec) + 1.0f;
	if (FAILED(dSoundCreateSecondaryBuffer(smpRate, length)) ||
		FAILED(dSoundLockBuf()))
	{
		return E_FAIL;
	}

	memcpy(m_lpvPtr1, m_pData, m_mmdatck.cksize);
	dSoundUnlockBuf();
	setCustomLoop(a_loopStart, a_loopEnd);
	m_isPlayable = true;

	return S_OK;
}

HRESULT Sound::loadFromMemory(const BYTE a_data[],
		DWORD a_size, DWORD a_offset, DWORD a_loopStart, DWORD a_loopEnd)
{
	if (nullptr == a_data) {
		Message(_T("��̉����f�[�^��n����܂���"), _T("Error"));
		return E_FAIL;
	}

	//�����f�[�^�i�[
	DWORD dataSize = (sizeof(a_data) + a_offset);
	if (dataSize < a_size) { //�\���ȃT�C�Y������
		Message(_T("�����f�[�^�̃T�C�Y������܂���"), _T("Error"));
		return E_FAIL;
	}
	m_pData = new BYTE[a_size];
	memcpy(m_pData, a_data + a_offset, a_size);

	//�Ȃ̒���(sec)�����߂ăo�b�t�@�����O
	DWORD smpRate = SystemParam::getDSPBufSamplingRate();
	m_wavfmtex.nChannels = 2;
	m_wavfmtex.wBitsPerSample = 16;
	m_wavfmtex.nSamplesPerSec = smpRate;
	m_mmdatck.cksize          = a_size;
	float length = m_mmdatck.cksize
			/ ((m_wavfmtex.nChannels * m_wavfmtex.wBitsPerSample / 8.0f)
				* m_wavfmtex.nSamplesPerSec) + 1.0f;
	if (FAILED(dSoundCreateSecondaryBuffer(smpRate, length)) ||
		FAILED(dSoundLockBuf()))
	{
		return E_FAIL;
	}

	memcpy(m_lpvPtr1, m_pData, m_mmdatck.cksize);
	dSoundUnlockBuf();
	setCustomLoop(a_loopStart, a_loopEnd);
	m_isPlayable = true;

	return S_OK;
}

void Sound::setCustomLoop(DWORD a_loopStart, DWORD a_loopEnd){
	//loopStart < loopEnd �ŁA loopEnd ��0���߂̏ꍇ�̓J�X�^�����[�v
	if (a_loopStart < a_loopEnd && 0 < a_loopEnd) {
		m_useCustomLoop     = true;
		float bitrateByte = m_wavfmtex.nSamplesPerSec *
			                m_wavfmtex.wBitsPerSample *
			                m_wavfmtex.nChannels / 8;
		m_loopStartPos      = bitrateByte * ((float)a_loopStart / 1000.0f); //�~���b�Ȃ̂�
		m_loopEndPos        = bitrateByte * ((float)a_loopEnd   / 1000.0f); //1000.0f�Ŋ���
	}
}



HRESULT Sound::dSoundOpenFile(LPTSTR pSrcFile) {
	DWORD size;
	m_hMmio = mmioOpen(pSrcFile, &m_mmInfo, MMIO_READ);
	//�����t�@�C���J��
	if (NULL == m_hMmio) {
		Message(_T("�����t�@�C�����J���܂���ł���"), _T("Error"));
		return E_FAIL;
	}

	//RIFF�`�����N����
	m_mmrifck.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (MMSYSERR_NOERROR != mmioDescend(m_hMmio, &m_mmrifck, NULL, MMIO_FINDRIFF)) {
		Message(_T("�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���(RIFF)\n\
�����t�@�C���ł͂Ȃ��\��������܂�"), _T("Error"));
		return E_FAIL;
	}

	//Format�`�����N����
	m_mmfmtck.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(m_hMmio, &m_mmfmtck, &m_mmrifck, MMIO_FINDCHUNK)) {
		Message(_T("�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���(FMT)\n\
�����t�@�C���ł͂Ȃ��\��������܂�"), _T("Error"));
		return E_FAIL;
	}

	//wave �t�@�C�����擾
	if ((size = mmioRead(m_hMmio, (HPSTR)&m_wavfmtex, m_mmfmtck.cksize)) != m_mmfmtck.cksize) {
		Message(_T("�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}

	//�J�[�\����擪�ɖ߂�(data�`�����N�����̈�)
	mmioAscend(m_hMmio, &m_mmfmtck, 0);

	//�����f�[�^�i�[
	if (E_FAIL == dSoundLoadToBuf()) {
		Message(_T("�����t�@�C�����������ɏ������߂܂���ł���"), _T("Error"));
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Sound::dSoundLoadToBuf() {
	//�f�[�^�`�����N����
	m_mmdatck.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (0u != mmioDescend(m_hMmio, &m_mmdatck, &m_mmrifck, MMIO_FINDCHUNK)) {
		return E_FAIL;
	}

	//�����f�[�^�i�[
	m_pData = new BYTE[m_mmdatck.cksize];
	if (mmioRead(m_hMmio, (HPSTR)m_pData, m_mmdatck.cksize) != m_mmdatck.cksize) {
		delete[] m_pData;
		return E_FAIL;
	}
	return S_OK;
}




void Sound::playBGM() {
	if (m_isPlayable) {
		m_pDSSecBuf->Play(0, 0, DSBPLAY_LOOPING);
		m_isPlaying = true;
	}
}

void Sound::playSE() {
	if (m_isPlayable) {
		if (m_isPlaying) {
			stop();
		}
		m_pDSSecBuf->Play(0, 0, 0);
		m_isPlaying = true;
	}
}

void Sound::pause() {
	if (m_isPlayable) {
		m_pDSSecBuf->Stop();
		m_isPlaying = false;
	}
}

void Sound::stop() {
	if (m_isPlayable) {
		m_pDSSecBuf->Stop();
		m_pDSSecBuf->SetCurrentPosition(0);
		m_isPlaying = false;
	}
}

void Sound::release() {
	m_pDSSecBuf->Stop();
	SafeRelease(m_pDSSecBuf);
	SafeDeleteArray(m_pData);
	m_isPlaying  = false;
	m_isPlayable = false;
}


void Sound::checkBGMLoop() {
	if (m_useCustomLoop){
		if (m_isPlaying && SUCCEEDED(m_pDSSecBuf->GetCurrentPosition(&m_playcur, &m_writecur))) {
			if (m_loopEndPos < m_writecur) {
				m_pDSSecBuf->SetCurrentPosition(m_loopStartPos);
			}
		}
	}
}








Sound::Sound() :
	m_mmInfo{0},
	m_mmrifck{0},
	m_mmfmtck{0},
	m_mmdatck{0},
	m_wavfmtex{0},
	m_hMmio(nullptr),
	m_pData(nullptr),
	m_pDSSecBuf(nullptr),
	m_isPlaying(false),
	m_isPlayable(false),
	m_loopEndPos(0),
	m_loopStartPos(0)
{
	// none
}

Sound::~Sound() {
	SafeDeleteArray(m_pData);
}




#undef __PBUF_FLAG
#undef __SBUF_FLAG










