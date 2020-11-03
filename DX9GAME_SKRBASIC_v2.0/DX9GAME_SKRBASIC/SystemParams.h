#pragma once
#include "system/header/SystemParam.h"

namespace skrBasic {

	//
	//  �V�X�e���ɕK�{�̒萔
	//  �ݒ肷��ɂ͂��ꂼ��̒l��ύX���ĉ�����
	//

	//�E�B���h�E(vp)�̉���
	const int SystemParam::WINDOW_WIDTH  = 1280;

	//�E�B���h�E(vp)�̏c��
	const int SystemParam::WINDOW_HEIGHT =  720;

	//�E�B���h�E�̃^�C�g��
	const std::_tstring SystemParam::GAME_TITLE = _T("�y�����y�����m�x���Q�[��");

	//DSound ��P�o�b�t�@�̃T���v�����O���[�g
	const DWORD SystemParam::DSOUND_SAMPLINGRATE = 44100;

	//�E�B���h�E�̃N���A�F
	D3DCOLOR SystemParam::clearColor = D3DCOLOR_XRGB(0x00, 0x63, 0x58);

}

