#pragma once
namespace ZekeEngine{
	class Engine
	{
	private:
		Engine();
		~Engine();
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