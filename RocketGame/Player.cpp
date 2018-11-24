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
	m_rot.SetRotationDeg(CVector3::AxisY(), 90.f);
	m_model->SetRotation(m_rot);
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

	CVector3 accVec = MainCamera().GetForward();
	accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	accVec.y = 0.f;

	CVector3 friction = m_moveSpeed;
	friction *= -1.0f;
	m_moveSpeed.x += friction.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += friction.z * GameTime().GetFrameDeltaTime();
	//‰Á‘¬“x‚ð‰Á‚¦‚éB
	m_moveSpeed += accVec;
	m_pos += m_moveSpeed;
	m_model->SetPosition(m_pos);
}

void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rot.SetRotation(CVector3::AxisY(), angle);
	m_model->SetRotation(m_rot);
}