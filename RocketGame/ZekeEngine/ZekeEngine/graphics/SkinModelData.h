#pragma once
#include <map>
#include "Skelton.h"

class Skeleton;
namespace ZekeEngine {
	class SkinModelDataManager
	{
	public:
		DirectX::Model* Load(const wchar_t* filePath, const Skeleton& sketon);
		void Release();
	private:
		std::map<
			std::wstring,
			std::unique_ptr<DirectX::Model>
		> m_directXModelMap;
	};
	extern SkinModelDataManager g_skinModelDataManager;
}