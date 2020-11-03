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
	void gameEnd();  //ゲーム終了

	void init(); //ゲーム初期化
	void main();     //メインループ


private:


};



