#pragma once
#include "system/IncludeSystemHeader.h"


//
//  GameMain �c �Q�[�����C�������̏�����Z�߂邽�߂̃N���X
//
//              ���̃N���X�Ɋ֐���ǉ������肵�č쐬���ĉ�����
//

//�Q�[�����C�����������n��
class GameMain : public skrBasic::D3DBasicProcess {
public:
	// �Q�[��������
	// @return ����������ɐ��������ꍇ�� ((HRESULT)(S_OK)) ��Ԃ��Ă��������B
	HRESULT init();
	
	//���C�����[�v
	// @return ����������ɐ��������ꍇ�� ((HRESULT)(S_OK)) ��Ԃ��Ă��������B
	HRESULT main();

	//BGM �̃��[�v�`�F�b�N
	// @return ����������ɐ��������ꍇ�� ((HRESULT)(S_OK)) ��Ԃ��Ă��������B
	HRESULT bgmLoop();


private:


};