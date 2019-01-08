#pragma once
#include "GameCamera.h"
class Player;
class Stage;
class SoccerBall;

class Game : public GameObject
{
public:
	Game();
	~Game();
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
	void Render() override;
private:
	CVector3 m_stagePos = CVector3::Zero();
	CQuaternion m_stageRot = CQuaternion::Identity();
	CVector3 m_cameraPos = CVector3::Zero();
	GameCamera* m_gameCamera;
	Player* m_player = nullptr;
	Stage* m_stage = nullptr;
	SoccerBall* m_ball = nullptr;
};

