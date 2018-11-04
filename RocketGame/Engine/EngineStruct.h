#pragma once

namespace ZekeEngine {
	struct EngineParam {
		HINSTANCE  hInstance;
		HINSTANCE hPrevInstance;
		LPWSTR lpCmdLine;
		int screenWidth;
		int screenHeight;
		int nCmdShow;
	};
}
