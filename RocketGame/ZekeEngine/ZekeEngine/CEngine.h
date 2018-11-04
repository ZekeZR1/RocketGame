#pragma once
namespace ZekeEngine {
	class CEngine
	{
	private:
		CEngine();
		~CEngine();
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
		static CEngine& GetInstance() {
			static CEngine* instance = nullptr;
			if (instance == nullptr) {
				instance = new CEngine;
			}
			return *instance;
		}
		static inline CEngine& Engine()
		{
			return CEngine::GetInstance();
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