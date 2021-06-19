#pragma once
#include <Windows.h>
#include <d3d9types.h>
#include <tchar.h>
#include "system/header/tstring.h"

namespace skrBasic {

	//
	//  �V�X�e���ɕK�{�̒萔
	//  �ݒ肷��ɂ͂��ꂼ��̒l��ύX���ĉ�����
	//
	class SystemParamSetting {
	protected:
		//�E�B���h�E(vp)�̉���
		static inline constexpr const int WINDOW_WIDTH  = 1280;

		//�E�B���h�E(vp)�̏c��
		static inline constexpr const int WINDOW_HEIGHT =  720;

		//�E�B���h�E�̃^�C�g��
		static inline const           stdex::_tstring GAME_TITLE
						= _T("�y�����y�����m�x���Q�[��");

		//DSound ��P�o�b�t�@�̃T���v�����O���[�g
		static inline constexpr const DWORD DSOUND_SAMPLINGRATE = 44100;

		//�E�B���h�E�̃N���A�F
		static inline                 D3DCOLOR clearColor
						= D3DCOLOR_XRGB(0x00, 0x63, 0x58);




	};

}

