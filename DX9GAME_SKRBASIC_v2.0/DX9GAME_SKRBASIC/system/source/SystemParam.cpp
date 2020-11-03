#pragma once
#include "..\header\SystemParam.h"
#include "..\..\SystemParams.h"

using namespace skrBasic;


int SystemParam::getWindowWidth() {
	return WINDOW_WIDTH;
}

int SystemParam::getWindowHeight() {
	return WINDOW_HEIGHT;
}

std::_tstring SystemParam::getWindowTitle() {
	return GAME_TITLE;
}

DWORD SystemParam::getDSPBufSamplingRate() {
	return DSOUND_SAMPLINGRATE;
}

void SystemParam::setClearColor(D3DCOLOR a_color) {
	clearColor = a_color;
}

D3DCOLOR SystemParam::getClearColor() {
	return clearColor;
}



