#include "stdafx.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {

	EngineParam  eParam;
	eParam.hInstance = hInstance;
	eParam.hPrevInstance = hPrevInstance;
	eParam.lpCmdLine = lpCmdLine;
	eParam.nCmdShow = nCmdShow;
	eParam.screenWidth = 1280;
	//eParam.screenWidth = 1920;
	eParam.screenHeight = 720;
	//eParam.screenHeight = 1080;

	if (CEngine::Engine().Init(eParam)) {
		CEngine::Engine().GameRoop();
	}

	CEngine::Engine().Final();

	return 0;
}
