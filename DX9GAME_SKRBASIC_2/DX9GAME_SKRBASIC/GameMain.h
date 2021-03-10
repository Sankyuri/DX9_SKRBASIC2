#pragma once
#include "system/IncludeSystemHeader.h"


//
//  GameMain … ゲームメイン部分の処理を纏めるためのクラス
//
//              このクラスに関数を追加したりして作成して下さい
//

//ゲームメイン部分処理系統
class GameMain : public skrBasic::D3DBasicProcess {
public:
	// ゲーム初期化
	// @return 処理が正常に成功した場合は ((HRESULT)(S_OK)) を返してください。
	HRESULT init();
	
	//メインループ
	// @return 処理が正常に成功した場合は ((HRESULT)(S_OK)) を返してください。
	HRESULT main();

	//BGM のループチェック
	// @return 処理が正常に成功した場合は ((HRESULT)(S_OK)) を返してください。
	HRESULT bgmLoop();


private:


};