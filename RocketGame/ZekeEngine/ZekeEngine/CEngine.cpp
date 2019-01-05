#include "stdafx.h"
#include "CEngine.h"

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

bool CEngine::Init(const EngineParam& engineParam) {
	if (!InitWindow(engineParam)) {
		return false;
	}

	IGameObjectManager().Init(32);
	//TODO :各エンジン初期化
	// : 物理エンジン初期化
	m_physicsWorld.Init();
	// : サウンドエンジン初期化
	// : エフェクトエンジン初期化
	// : 入力デバイスを初期化
	int padNo = 0;
	for (auto& pad : m_pad) {
		pad.Init(padNo);
		padNo++;
	}

	if (!m_graphicsEngine.InitDirectX(m_hWnd)) {
		return false;
	}
}

void CEngine::Final() {
	m_graphicsEngine.Release();
	m_physicsWorld.Release();
}

void CEngine::GameRoop() {
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
		}
	}
}

void CEngine::Update() {
	for (auto& pad : m_pad) {
		pad.Update();
	}
	IGameObjectManager().Execute();
	m_physicsWorld.Update();
}

bool CEngine::InitWindow(const EngineParam& engineParam) {
	assert(engineParam.screenHeight != 0 && "screenHeight is zero");
	assert(engineParam.screenWidth != 0 && "screenWidth is zero");

	m_screenHeight = engineParam.screenHeight;
	m_screenWidth = engineParam.screenWidth;


	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
		TEXT("Game"), nullptr
	};
	RegisterClassEx(&wc);

	RECT rc = { 0, 0, m_screenWidth,m_screenHeight };
	AdjustWindowRect(
		&rc,
		WS_OVERLAPPED,
		FALSE
	);

	m_hWnd = CreateWindow(TEXT("Game"), TEXT("Game"),
		WS_OVERLAPPEDWINDOW, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, wc.hInstance, nullptr);

	ShowWindow(m_hWnd, engineParam.nCmdShow);

	return m_hWnd != nullptr;
}