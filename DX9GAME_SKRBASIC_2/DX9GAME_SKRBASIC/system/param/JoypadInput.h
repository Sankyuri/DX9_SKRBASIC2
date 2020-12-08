#pragma once

namespace skrBasic {

	//
	//  ゲームパッドのボタン
	//  JOY_BUTTONX があるが、2^nでいまいち使い辛いので独自定義
	//
	enum class JoypadInput {
		BUTTON1,
		BUTTON2,
		BUTTON3,
		BUTTON4,
		BUTTON5,
		BUTTON6,
		BUTTON7,
		BUTTON8,
		BUTTON9,
		BUTTON10,
		BUTTON11,
		BUTTON12,
		BUTTON13,
		BUTTON14,
		BUTTON15,
		BUTTON16,
		BUTTON17,
		BUTTON18,
		BUTTON19,
		BUTTON20,
		BUTTON21,
		BUTTON22,
		BUTTON23,
		BUTTON24,
		BUTTON25,
		BUTTON26,
		BUTTON27,
		BUTTON28,
		BUTTON29,
		BUTTON30,
		BUTTON31,
		BUTTON32,
		LEFT,  //軸の傾きを考慮しない左入力
		UP,    //軸の傾きを考慮しない上入力
		RIGHT, //軸の傾きを考慮しない右入力
		DOWN,  //軸の傾きを考慮しない下入力

		MAX
	};

}; // namespace skrBasic



