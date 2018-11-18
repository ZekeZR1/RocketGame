#include "stdafx.h"
#include "Game.h"



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

	if (Engine().Init(eParam)) {
		/*initialize 3dCamera*/
		MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
		MainCamera().SetNear(10.0f);
		MainCamera().SetFar(1000.0f);
		MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
		MainCamera().SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		MainCamera().Update();
		//start main roop
		//NewGO<Game>(0,"Game");
		Engine().GameRoop();
	}
	Engine().Final();

	return 0;
}
