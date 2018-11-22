#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start() {
	return true;
}

void GameCamera::Update() {
	MainCamera2D().Update();
	SkinModelRender* tar = FindGO<SkinModelRender>("octane");
	m_target = tar->GetPosition();

	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
	qRot.Multiply(m_toCameraPos);

	CVector3 toCameraPosOld = m_toCameraPos;

	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
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
