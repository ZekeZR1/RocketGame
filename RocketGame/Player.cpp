#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start() {
	m_model = NewGO<SkinModelRender>(0, "octane");
	m_model->Init(L"Assets/modelData/Octane.cmo", nullptr, 0, enFbxUpAxisY);
	return true;
}

void Player::OnDestroy() {
	DeleteGO(m_model);
}

void Player::Update() {
	Move();
	Rotation();
}

void Player::Move() {
	float MOVE_SPEED = 50.0f;
	static float MOVE_SPEED_JUMP = 30.0f;
	float x = Pad(0).GetLStickXF();
	float y = Pad(0).GetLStickYF();
	float r = Pad(0).GetRTrigger();
	float l = Pad(0).GetLTrigger();
	//‰ñ‚·‚æ
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
	m_rot.Multiply(qRot);
	//m_model->SetRotation(m_rot);
	//Šµ«
	accVec = CVector3::One();
	accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	accVec.y = 0.f;
	m_rot.Multiply(accVec);
	CVector3 friction = m_moveSpeed;
	friction *= -1.5f;
	m_moveSpeed.x += friction.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += friction.z * GameTime().GetFrameDeltaTime();

	//‰Á‘¬“x‚ð‰Á‚¦‚éB
	m_moveSpeed += accVec;
	m_pos += m_moveSpeed;
	m_model->SetPosition(m_pos);

	char message[256];
	sprintf_s(message, "x...%f z...%f\n", fabsf(m_moveSpeed.x), fabsf(m_moveSpeed.z));
	OutputDebugStringA(message);
}

void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion nRot;
	nRot.SetRotation(CVector3::AxisY(), angle);
	CQuaternion aRot;
	aRot.SetRotationDeg(CVector3::AxisY(),180.f);
	nRot.Multiply(aRot);
	m_model->SetRotation(nRot);
}