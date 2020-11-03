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
static HRESULT InitDSBufFmtWave(DWORD samplingRate);

void InitDSound(DWORD a_samplingRate){
	DirectSoundCreate8(NULL, &g_pDSound, NULL);
	if (g_pDSound != NULL) {
		if (SUCCEEDED(g_pDSound->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE))) {
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
	LPDIRECTSOUNDBUFFER ptmpBuf   = NULL;

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
	hr = g_pDSound->CreateSoundBuffer(&tmpDesc, &ptmpBuf, NULL);
	if (FAILED(hr) || NULL == ptmpBuf) {
		Message(_T("�Z�J���_���T�E���h�o�b�t�@�̐����Ɏ��s���܂���(DSB)"), _T("Error"));
		return E_FAIL;
	}
	hr = ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void **)&pDSSecBuf);
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
	if (FAILED(hr = pDSSecBuf->Lock(0, mmdatck.cksize, &lpvPtr1,
		                            &dwBytes1, &lpvPtr2, &dwBytes2, 0)))
	{
		pDSSecBuf->Restore();
		if (FAILED(hr = pDSSecBuf->Lock(0, mmdatck.cksize, &lpvPtr1,
			                            &dwBytes1, &lpvPtr2, &dwBytes2, 0)))
		{
			Message(_T("�T�E���h�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("Error"));
			return E_FAIL;
		}
	}
	return S_OK;
}
HRESULT Sound::dSoundUnlockBuf() {
	if (FAILED(pDSSecBuf->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2))) {
		Message(_T("�T�E���h�o�b�t�@�̃A�����b�N�Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}
	return S_OK;
}


HRESULT Sound::load(LPCTSTR a_pSrcFile, DWORD a_loopStart, DWORD a_loopEnd)
{
	if (E_FAIL == dSoundOpenFile(const_cast<LPTSTR>(a_pSrcFile))) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}
	mmioClose(hMmio, 0);

	//�Ȃ̒���(sec)�����߂�(���o�[�W������ a_lenthSec �ɓ�����)
	float length = (float)(mmrifck.cksize + mmrifck.dwDataOffset) /
		           (float)wavfmtex.nAvgBytesPerSec;

	//�o�b�t�@�����O
	if (FAILED(dSoundCreateSecondaryBuffer(wavfmtex.nSamplesPerSec, length)) ||
		FAILED(dSoundLockBuf()))
	{
		return E_FAIL;
	}

	memcpy(lpvPtr1, pData, mmdatck.cksize);
	dSoundUnlockBuf();
	setCustomLoop(a_loopStart, a_loopEnd);
	canPlay = true;

	return S_OK;
}

HRESULT Sound::loadFromResourceFile(LPCTSTR a_pSrcFile,
		DWORD a_size, DWORD a_offset, DWORD a_loopStart, DWORD a_loopEnd)
{
	hMmio = mmioOpen(const_cast<LPTSTR>(a_pSrcFile), &mmInfo, MMIO_READ);
	//�����t�@�C���J��
	if (NULL == hMmio) {
		Message(_T("�����t�@�C�����J���܂���ł���"), _T("Error"));
		return E_FAIL;
	}

	//�����f�[�^�i�[
	pData = new char[a_size]; // �o�b�t�@�쐬
	mmioSeek(hMmio, a_offset, SEEK_SET); // �I�t�Z�b�g�����炷
	if (mmioRead(hMmio, (HPSTR)pData, a_size) != a_size) { // �ǂݍ���
		Message(_T("�����t�@�C�����i�[�ł��܂���ł���"), _T("Error"));
		delete[] pData;
		return E_FAIL;
	}

	//�Ȃ̒���(sec)�����߂ăo�b�t�@�����O
	DWORD smpRate = SystemParam::getDSPBufSamplingRate();
	wavfmtex.nChannels      = 2;
	wavfmtex.wBitsPerSample = 16;
	wavfmtex.nSamplesPerSec = smpRate;
	mmdatck.cksize          = a_size;
	float length = mmdatck.cksize
		/ ((wavfmtex.nChannels * wavfmtex.wBitsPerSample / 8.0f)
			* wavfmtex.nSamplesPerSec) + 1.0f;
	if (FAILED(dSoundCreateSecondaryBuffer(smpRate, length)) ||
		FAILED(dSoundLockBuf()))
	{
		return E_FAIL;
	}

	memcpy(lpvPtr1, pData, mmdatck.cksize);
	dSoundUnlockBuf();
	setCustomLoop(a_loopStart, a_loopEnd);
	canPlay = true;

	return S_OK;
}

HRESULT Sound::loadFromMemory(const CHAR a_data[],
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
	pData = new char[a_size];
	memcpy(pData, a_data + a_offset, a_size);

	//�Ȃ̒���(sec)�����߂ăo�b�t�@�����O
	DWORD smpRate = SystemParam::getDSPBufSamplingRate();
	wavfmtex.nChannels = 2;
	wavfmtex.wBitsPerSample = 16;
	wavfmtex.nSamplesPerSec = smpRate;
	mmdatck.cksize          = a_size;
	float length = mmdatck.cksize
		/ ((wavfmtex.nChannels * wavfmtex.wBitsPerSample / 8.0f)
			* wavfmtex.nSamplesPerSec) + 1.0f;
	if (FAILED(dSoundCreateSecondaryBuffer(smpRate, length)) ||
		FAILED(dSoundLockBuf()))
	{
		return E_FAIL;
	}

	memcpy(lpvPtr1, pData, mmdatck.cksize);
	dSoundUnlockBuf();
	setCustomLoop(a_loopStart, a_loopEnd);
	canPlay = true;

	return S_OK;
}

void Sound::setCustomLoop(DWORD a_loopStart, DWORD a_loopEnd){
	//loopStart < loopEnd �ŁA loopEnd ��0���߂̏ꍇ�̓J�X�^�����[�v
	if (a_loopStart < a_loopEnd && 0 < a_loopEnd) {
		useCustomLoop     = true;
		float bitrateByte = wavfmtex.nSamplesPerSec *
			                wavfmtex.wBitsPerSample *
			                wavfmtex.nChannels / 8;
		loopStartPos      = bitrateByte * ((float)a_loopStart / 1000.0f); //�~���b�Ȃ̂�
		loopEndPos        = bitrateByte * ((float)a_loopEnd   / 1000.0f); //1000.0f�Ŋ���
	}
}



HRESULT Sound::dSoundOpenFile(LPTSTR pSrcFile) {
	DWORD size;
	hMmio = mmioOpen(pSrcFile, &mmInfo, MMIO_READ);
	//�����t�@�C���J��
	if (NULL == hMmio) {
		Message(_T("�����t�@�C�����J���܂���ł���"), _T("Error"));
		return E_FAIL;
	}

	//RIFF�`�����N����
	mmrifck.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &mmrifck, NULL, MMIO_FINDRIFF)) {
		Message(_T("�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���(RIFF)\n\
�����t�@�C���ł͂Ȃ��\��������܂�"), _T("Error"));
		return E_FAIL;
	}

	//Format�`�����N����
	mmfmtck.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(hMmio, &mmfmtck, &mmrifck, MMIO_FINDCHUNK)) {
		Message(_T("�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���(FMT)\n\
�����t�@�C���ł͂Ȃ��\��������܂�"), _T("Error"));
		return E_FAIL;
	}

	//wave �t�@�C�����擾
	if ((size = mmioRead(hMmio, (HPSTR)&wavfmtex, mmfmtck.cksize)) != mmfmtck.cksize) {
		Message(_T("�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���"), _T("Error"));
		return E_FAIL;
	}

	//�J�[�\����擪�ɖ߂�(data�`�����N�����̈�)
	mmioAscend(hMmio, &mmfmtck, 0);

	//�����f�[�^�i�[
	if (E_FAIL == dSoundLoadToBuf()) {
		Message(_T("�����t�@�C�����������ɏ������߂܂���ł���"), _T("Error"));
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Sound::dSoundLoadToBuf() {
	//�f�[�^�`�����N����
	mmdatck.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (0u != mmioDescend(hMmio, &mmdatck, &mmrifck, MMIO_FINDCHUNK)) {
		return E_FAIL;
	}

	//�����f�[�^�i�[
	pData = new char[mmdatck.cksize];
	if (mmioRead(hMmio, (HPSTR)pData, mmdatck.cksize) != mmdatck.cksize) {
		delete[] pData;
		return E_FAIL;
	}
	return S_OK;
}




void Sound::playBGM() {
	if (canPlay) {
		pDSSecBuf->Play(0, 0, DSBPLAY_LOOPING);
		nowPlaying = true;
	}
}

void Sound::playSE() {
	if (canPlay) {
		if (nowPlaying) {
			stop();
		}
		pDSSecBuf->Play(0, 0, 0);
		nowPlaying = true;
	}
}

void Sound::pause() {
	if (canPlay) {
		pDSSecBuf->Stop();
		nowPlaying = false;
	}
}

void Sound::stop() {
	if (canPlay) {
		pDSSecBuf->Stop();
		pDSSecBuf->SetCurrentPosition(0);
		nowPlaying = false;
	}
}

void Sound::deleteSound() {
	if (canPlay) {
		SafeRelease(pDSSecBuf);
		SafeDeleteArray(pData);
		nowPlaying = false;
		canPlay    = false;
	}
}

void Sound::checkBGMLoop() {
	if (useCustomLoop){
		if (nowPlaying && SUCCEEDED(pDSSecBuf->GetCurrentPosition(&playcur, &writecur))) {
			if (loopEndPos < writecur) {
				pDSSecBuf->SetCurrentPosition(loopStartPos);
			}
		}
	}
}








Sound::Sound() {
	hMmio = NULL;
	ZeroMemory(&mmInfo , sizeof(MMIOINFO));
	ZeroMemory(&mmrifck, sizeof(MMCKINFO));
	ZeroMemory(&mmfmtck, sizeof(MMCKINFO));
	ZeroMemory(&mmdatck, sizeof(MMCKINFO));
	nowPlaying = canPlay      = false;
	loopEndPos = loopStartPos = 0;
	
}

Sound::~Sound() {
	if (pData != NULL) {
		delete[] pData;
	}
}




#undef __PBUF_FLAG
#undef __SBUF_FLAG










