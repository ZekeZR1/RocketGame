#pragma once
namespace ZekeEngine {
	class SkinModel : Noncopyable
	{
	public:

		enum EnFbxUpAxis {
			enFbxUpAxisY,		
			enFbxUpAxisZ,	
		};

		SkinModel();
		~SkinModel();
		//TODO : �C���X�^���V���O�`��ł���悤�ɂ���
		//TODO : ���f���f�[�^�������Ɏ��悤�ɂ���
		void Init();
		void Draw();
	private:
	};
}
