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
		//�e�N�X�`��������t�H���_��ݒ肷��
		effectFactory.SetDirectory(L"Assets/modelData");
		//CMO�t�@�C���̃��[�h
		auto model = DirectX::Model::CreateFromCMO(
			GraphicsEngine().GetD3DDevice(),
			filePath,
			effectFactory,
			false,
			false,
			onFindBone
		);
		retModel = model.get();
		//�V�K�Ȃ̂Ń}�b�v�ɓo�^
		m_directXModelMap.insert({ filePath, std::move(model) });
	}
	else {
		//�ǂݍ��ݍς݂̃f�[�^���擾
		retModel = it->second.get();
	}
	return retModel;
}

void SkinModelDataManager::Release()
{
	m_directXModelMap.clear();
}