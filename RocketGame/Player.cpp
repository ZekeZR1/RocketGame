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

//TODO : 前進などを仮想ボタンのようにして、キーコンフィグから動作変更できるようにする
void Player::Update() {
	Move();
	Rotation();
}

void Player::Move() {
	if (Pad(0).IsPress(enGoForward)) {
		m_moveSpeed.x += 10.f;
	}
	else {
		if (m_moveSpeed.x <= 0.f)
			return;
		m_moveSpeed.x -= 10.f;
	}
	if (Pad(0).IsPress(enGOBack)) {
		m_moveSpeed.z += 10.f;
	}
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