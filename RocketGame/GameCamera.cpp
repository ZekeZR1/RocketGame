#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start() {
	SaveSystem().Load();
	CSaveSystem::SCameraData data = SaveSystem().GetGameCameraData();
	m_distanceToTarget = data.distanceToTarget;
	m_toCameraPos.z = m_distanceToTarget;
	m_cameraRotationSpeed = data.cameraRotationSpeed;
	return true;
}

void GameCamera::Update() {
	MainCamera2D().Update();

	Player* tar = FindGO<Player>("Player");
	m_target = tar->GetPosition();
	m_target.y += m_raiseViewPoint;

	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//TODO : ターゲットとのカメラ距離 (オプションで設定するようにする)
	CVector3 toCamera = m_toCameraPos;
	toCamera.Normalize();
	if (Pad(0).IsTrigger(enButtonRight)) {
		if (m_distanceToTarget >= m_maxDistance)
			return;
		m_toCameraPos +=  m_distanceMoveParam * toCamera;
		m_distanceToTarget += m_distanceMoveParam;
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		if (m_distanceToTarget <= m_minDistance)
			return;
		m_toCameraPos -= m_distanceMoveParam * toCamera;
		m_distanceToTarget -= m_distanceMoveParam;
	}
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), m_cameraRotationSpeed * x);
	qRot.Multiply(m_toCameraPos);

	CVector3 toCameraPosOld = m_toCameraPos;

	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, m_cameraRotationSpeed * y);
	qRot.Multiply(m_toCameraPos);
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	CVector3 pos = m_target + m_toCameraPos;

	MainCamera().SetTarget(m_target);
	MainCamera().SetPosition(pos);
	MainCamera().Update();
}
