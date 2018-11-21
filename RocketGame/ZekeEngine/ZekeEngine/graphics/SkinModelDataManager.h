#pragma once
#include <map>
#include "Skelton.h"
class Skeleton;
namespace ZekeEngine {
	/*!
	*@brief	スキンモデルデータマネージャー。。
	*@FlyweightパターンのFlyweightFactoryクラス、。
	*/
	class SkinModelDataManager
	{
	public:
		/*!
		*@brief	モデルをロード。
		*@param[in]	filePath	ファイルパス。
		*@param[in]	skeleton	スケルトン。
		*/
		DirectX::Model* Load(const wchar_t* filePath, const Skeleton& sketon);
		/*!
		*@brief	モデルデータを全開放。
		*/
		void Release();
	private:
		std::map<
			std::wstring,
			std::unique_ptr<DirectX::Model>
		> m_directXModelMap;
	};
}