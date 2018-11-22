#pragma once
#include "GameCamera.h"
class Game : public GameObject
{
public:
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render() override;
private:
	SkinModelRender* m_octane;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	SkinModelRender* m_stage;
	CVector3 m_stagePos = CVector3::Zero();
	CQuaternion m_stageRot = CQuaternion::Identity();
	CVector3 m_cameraPos = CVector3::Zero();
	GameCamera* m_gameCamera;
};

