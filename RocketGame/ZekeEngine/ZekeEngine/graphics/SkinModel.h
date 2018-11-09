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
		//TODO : インスタンシング描画できるようにする
		//TODO : モデルデータを引数に取るようにする
		void Init();
		void Draw();
	private:
	};
}
