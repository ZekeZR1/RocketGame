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
	//とりあえずゲームカメラのdataロードをするテスト関数
	ptree pt;
	read_json("Assets/saveData/PlayerOptionData.json", pt);
	//視野角
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.viewAngle")) {
		m_cameraData.viewAngle = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
	//距離
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.distanceToTarget")) {
		m_cameraData.distanceToTarget = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
	//高度
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.cameraHeight")) {
		m_cameraData.cameraHeight = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
	//回転速度
	if (boost::optional<int> value = pt.get_optional<int>("GameCameraData.cameraRotationSpeed")) {
		m_cameraData.cameraRotationSpeed = value.get();
	}
	else {
		OutputDebugStringA("value is nothing\n");
	}
}

void CSaveSystem::Save() {
	ptree pt;
	//視野角
	pt.put("GameCameraData.viewAngle", 0);
	//距離
	pt.put("GameCameraData.distanceToTarget", 300);
	//高度
	pt.put("GameCameraData.cameraHeight", 50);
	//回転速度
	pt.put("GameCameraData.cameraRotationSpeed", 5);

	write_json("Assets/saveData/PlayerOptionData.json", pt);
}