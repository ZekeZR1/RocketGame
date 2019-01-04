#include "stdafx.h"
#include "SaveSystem.h"
#include <boost/version.hpp>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include "../debug/OutputConsole.h"

using namespace boost::property_tree;


CSaveSystem::CSaveSystem()
{
}


CSaveSystem::~CSaveSystem()
{
}

void CSaveSystem::Load() {
	//�Ƃ肠�����Q�[���J������data���[�h������e�X�g�֐�
	ptree pt;
	read_json("Assets/saveData/PlayerOptionData.json", pt);
	//����p
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.viewAngle")) {
		m_cameraData.viewAngle = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
	//����
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.distanceToTarget")) {
		m_cameraData.distanceToTarget = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
	//���x
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.cameraHeight")) {
		m_cameraData.cameraHeight = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
	//��]���x
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.cameraRotationSpeed")) {
		m_cameraData.cameraRotationSpeed = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
}

void CSaveSystem::Save() {
	ptree pt;
	//����p
	pt.put("GameCameraData.viewAngle", 0);
	//����
	pt.put("GameCameraData.distanceToTarget", 300);
	//���x
	pt.put("GameCameraData.cameraHeight", 50);
	//��]���x
	pt.put("GameCameraData.cameraRotationSpeed", 5);

	write_json("Assets/saveData/PlayerOptionData.json", pt);
}