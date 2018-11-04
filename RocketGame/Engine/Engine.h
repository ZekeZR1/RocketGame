#pragma once
namespace ZekeEngine{
	class Engine
	{
	private:
		Engine();
		~Engine();
	public:
		/*
			エンジンの初期化
		*/
		bool Init(const EngineParam& engineParam);
		/*
			終了処理
		*/
		void Final();
		/*
			メインループ
		*/
		void GameRoop();
		/*
			エンジンの更新
		*/
		void Update();
		/*
			エンジンのインスタンスを取得
		*/
		static Engine& GetInstance() {
			static Engine* instance = nullptr;
			if (instance == nullptr) {
				instance = new Engine;
			}
			return *instance;
		}
		static inline Engine& IEngine()
		{
			return Engine::GetInstance();
		}
	private:
		/*
			ウィンドウ初期化
		*/
		bool InitWindow(const EngineParam& engineParam);
	private:
		HINSTANCE		m_hinst = nullptr;					//アプリのインスタンス
		HWND				m_hWnd = nullptr;					//ウィンドウのハンドル
		int					m_screenWidth = 0;				//スクリーンの幅
		int					m_screenHeight = 0;				//スクリーンの高さ
	};
}