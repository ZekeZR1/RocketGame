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
		/*initialize 3dCamera*/
		CEngine::MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
		CEngine::MainCamera().SetNear(10.0f);
		CEngine::MainCamera().SetFar(1000.0f);
		CEngine::MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
		CEngine::MainCamera().SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		CEngine::MainCamera().Update();
		//start main roop
		CEngine::Engine().GameRoop();
	}
	CEngine::Engine().Final();

	return 0;
}
