#include "stdafx.h"
#include "SkinModelData.h"
#include "SkinModelEffect.h"
#include "Skelton.h"

SkinModelDataManager g_skinModelDataManager;

DirectX::Model* SkinModelDataManager::Load(const wchar_t* filePath, const ZekeEngine::Skeleton& skeleton)
{
	DirectX::Model* retModel = NULL;
	auto onFindBone = [&](
		const wchar_t* boneName,
		const VSD3DStarter::Bone* bone,
		std::vector<int>& localBoneIDtoGlobalBoneIDTbl
		)
	{
		int globalBoneID = skeleton.FindBoneID(boneName);
		if (globalBoneID == -1) {
			return;
		}
		localBoneIDtoGlobalBoneIDTbl.push_back(globalBoneID);
	};
	auto it = m_directXModelMap.find(filePath);
	if (it == m_directXModelMap.end()) {
		SkinModelEffectFactory effectFactory(GraphicsEngine().GetD3DDevice());
		//テクスチャがあるフォルダを設定する
		effectFactory.SetDirectory(L"Assets/modelData");
		//CMOファイルのロード
		auto model = DirectX::Model::CreateFromCMO(
			GraphicsEngine().GetD3DDevice(),
			filePath,
			effectFactory,
			false,
			false,
			onFindBone
		);
		retModel = model.get();
		//新規なのでマップに登録
		m_directXModelMap.insert({ filePath, std::move(model) });
	}
	else {
		//読み込み済みのデータを取得
		retModel = it->second.get();
	}
	return retModel;
}

void SkinModelDataManager::Release()
{
	m_directXModelMap.clear();
}