#pragma once
namespace ZekeEngine {
	class CEngine
	{
	private:
		CEngine();
		~CEngine();
	public:
		/*
		�G���W���̏�����
		*/
		bool Init(const EngineParam& engineParam);
		/*
		�I������
		*/
		void Final();
		/*
		���C�����[�v
		*/
		void GameRoop();
		/*
		�G���W���̍X�V
		*/
		void Update();
		/*
		�G���W���̃C���X�^���X���擾
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
		�E�B���h�E������
		*/
		bool InitWindow(const EngineParam& engineParam);
	private:
		HINSTANCE		m_hinst = nullptr;					//�A�v���̃C���X�^���X
		HWND				m_hWnd = nullptr;					//�E�B���h�E�̃n���h��
		int					m_screenWidth = 0;				//�X�N���[���̕�
		int					m_screenHeight = 0;				//�X�N���[���̍���
	};
}