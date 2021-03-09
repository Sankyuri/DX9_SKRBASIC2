#pragma once
#include "SystemInclude.h"
#include "..\param\KeyboardInput.h"
#include "..\param\JoypadInput.h"
#include "..\param\MouseInput.h"


namespace skrBasic {
	
	//
	//  入力系統
	//  キーボード、ゲームパッド、マウスが利用可能
	//
	class Input {
	public:
		//キーを押しているか
		//@param a_key キーID(DIK_*)
		//@return 押している間は true を返す
		static bool isKeyInput(int a_key);

		//キーを押しているか
		//@param a_key キーID
		//@return 押している間は true を返す
		static bool isKeyInput(KeyboardInput a_key);

		//キーを押した瞬間か
		//@param a_key キーID(DIK_*)
		//@return 押した瞬間は true を返す
		static bool isKeyPush(int a_key);

		//キーを押した瞬間か
		//@param a_key キーID
		//@return 押した瞬間は true を返す
		static bool isKeyPush(KeyboardInput a_key);

		//キーを押した瞬間か
		//@param a_key キーID(DIK_*)
		//@return 離した瞬間は true を返す
		static bool isKeyRelease(int a_key);

		//キーを押した瞬間か
		//@param a_key キーID
		//@return 離した瞬間は true を返す
		static bool isKeyRelease(KeyboardInput a_key);




		//ゲームパッドのボタンを押しているか
		//@param a_button ボタンID
		//@return 押している間は true を返す
		static bool isJoypadInput(JoypadInput a_button);

		//ゲームパッドのボタンを押した瞬間か
		//@param a_button ボタンID
		//@return 押した瞬間は true を返す
		static bool isJoypadPush(JoypadInput a_button);

		//ゲームパッドのボタンを離した瞬間か
		//@param a_button ボタンID
		//@return 離した瞬間は true を返す
		static bool isJoypadRelease(JoypadInput a_button);




		//マウスボタンを押しているか
		//@param a_mousebutton マウスボタンID
		//@return 押している間は true を返す
		static bool isMouseInput(MouseInput a_mousebutton);

		//マウスボタンを押した瞬間か
		//@param a_mousebutton マウスボタンID
		//@return 押した瞬間は true を返す
		static bool isMouseClick(MouseInput a_mousebutton);

		//マウスボタンを離した瞬間か
		//@param a_mousebutton マウスボタンID
		//@return 離した瞬間は true を返す
		static bool isMouseRelease(MouseInput a_mousebutton);


		//特定範囲内でマウスボタンを押しているか
		//@param a_mousebutton マウスボタンID
		//@param a_area 判定する範囲
		//@return 押している間は true を返す
		static bool isMouseInputInRange(MouseInput a_mousebutton, const RECT *a_area);

		//特定範囲内でマウスボタンを押した瞬間か
		//@param a_mousebutton マウスボタンID
		//@param a_area 判定する範囲
		//@return 押した瞬間は true を返す
		static bool isMouseClickInRange(MouseInput a_mousebutton, const RECT *a_area);

		//特定範囲内でのマウスボタンを離した瞬間か
		//@param a_mousebutton マウスボタンID
		//@param a_area 判定する範囲
		//@return 離した瞬間は true を返す
		static bool isMouseReleaseInRange(MouseInput a_mousebutton, const RECT *a_area);


		//マウス(カーソル)が特定範囲内にあるか
		//@param a_area 判定する範囲
		static bool isMouseInRange(const RECT *a_area);




		//マウスカーソルを移動させたか
		//@return 移動していたら true を返す
		static bool isCursorMove();

		//マウスカーソルの座標を取得
		//@return ビューポート座標を POINT で返す
		static POINT getCursorPos();

		//マウスカーソルの座標を取得
		//@return ビューポート座標を POINT で返す
		static POINT getCursorPosPt();

		//マウスカーソルの座標を取得
		//@return ビューポート座標を D3DXVECTOR2 で返す
		static D3DXVECTOR2 getCursorPosVec();


		//マウスカーソルの移動距離を取得
		//@return 移動距離を POINT で返す
		static POINT getCursorMoveLength();

		//マウスカーソルの移動距離を取得
		//@return 移動距離を POINT で返す
		static POINT getCursorMoveLengthPt();

		//マウスカーソルの移動距離を取得
		//@return 移動距離を D3DXVECTOR2 で返す
		static D3DXVECTOR2 getCursorMoveLengthVec();




		//ゲームパッドの軸のx方向の傾きを取得
		//@return 右が正、左が負
		static LONG getJoypadAxisTiltX();

		//ゲームパッドの軸のy方向の傾きを取得
		//@return 下が正、上が負
		static LONG getJoypadAxisTiltY();

		//ゲームパッドの軸のz方向の傾きを取得
		static LONG getJoypadAxisTiltZ();


		//マウスの軸のx方向の傾きを取得
		static LONG getMouseAxisTiltX();

		//マウスの軸のy方向の傾きを取得
		static LONG getMouseAxisTiltY();

		//マウスの軸のz方向の傾きを取得
		//@return 奥が正、手前が負
		static LONG getMouseAxisTiltZ();

		//マウスホイールの回転量を取得
		//@return 奥が正、手前が負
		static LONG getMouseWheelTilt();




		//何らかのキーボードキーを押しているか
		//@return 何らかのキーを押している間は true を返す
		static bool isSomeKey();

		//何らかのゲームパッドボタンを押しているか
		//@return 何らかのボタンを押している間は true を返す
		static bool isSomeJoypad();

		//何らかのマウスボタンを押しているか
		//@return 何らかのマウスボタンを押している間は true を返す
		static bool isSomeMouse();

		//何らかの入力をしているか
		//@return 何らかの入力をしている間は true を返す
		static bool isSomeInput();


		//押されている最も番号の若いキーボードキーを取得
		//@return 何も押していない場合は-1、何かを押している場合は KeyboardInput に対応する整数を返す
		static int getSomeKey();

		//押されている最も番号の若いゲームパッドボタンを取得
		//@return 何も押していない場合は-1、何かを押している場合は JoypadInput に対応する整数を返す
		static int getSomeJoypad();

		//押されている最も番号の若いマウスボタンを取得
		//@return 何も押していない場合は-1、何かを押している場合は MouseInput に対応する整数を返す
		static int getSomeMouse();




		Input() = delete;

		//入力系処理の初期化<システム用>
		//@deprecated
		static HRESULT init();

		//入力状態の取得<システム用>
		//@deprecated
		static void    getInputDeviceState();


	private:
		static const int BUTTON_ON_FLUG = 0x80; //キーやボタンの入力しているかフラグ

		static const int KEY_ARY_MAX   = 256; //キー入力配列の最大数
		static const int PAD_ARY_MAX   =  36; //パッド入力配列の上下左右も含めた最大数
		static const int MOUSE_ARY_MAX =   8; //マウス入力配列の最大数
		static const int PAD_BTN_MAX   =  32; //パッドボタンの最大数
		static const int PAD_POS_MIN   =  32; //パッド軸の傾き最小


		static BYTE          m_keystate[KEY_ARY_MAX];   //キーボード入力代入先
		static DIJOYSTATE    m_joystate;                //ゲームパッド入力代入先
		static DIMOUSESTATE2 m_mousestate;              //マウス入力代入先
		static bool          m_wasKeyIn[KEY_ARY_MAX];   //現在のキーボード入力
		static bool          m_wasJoyIn[PAD_ARY_MAX];   //現在のゲームパッド入力
		static bool          m_wasClick[MOUSE_ARY_MAX]; //現在のマウス入力
		static POINT         m_mousePt;                 //現在のマウスのビューポート座標
		static POINT         m_preMousePt;              //前回のマウスのビューポート座標

		static bool    m_useJoypad;       //ジョイパッドを使用できるか
		static bool    m_useMouse;        //マウスを使用できるか

		static HRESULT initKeyboard();  //キーボード初期化
		static HRESULT initJoypad();    //ゲームパッド初期化
		static HRESULT initMouse();     //マウス初期化

		static void    getKeyState();   //キーボード状態取得
		static void    getJoyState();   //ゲームパッド状態取得
		static void    getMouseState(); //キーボード状態取得


	};
	//参考: http://mkubara.com/wp/%E3%83%9E%E3%83%AB%E3%83%81%E3%83%AC%E3%83%B3%E3%83%80%E3%83%AA%E3%83%B3%E3%82%B0%E3%82%BF%E3%83%BC%E3%82%B2%E3%83%83%E3%83%88/

}; // namespace skrBasic



