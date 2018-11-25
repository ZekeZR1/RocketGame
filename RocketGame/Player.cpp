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
	CQuaternion sRot = m_rot;
	sRot.SetRotationDeg(CVector3::AxisY(), 45.f + 180.f);
	m_model->SetRotation(sRot);
	m_forward = MainCamera().GetForward();
	sRot.Multiply(m_forward);
	return true;
}

void Player::OnDestroy() {
	DeleteGO(m_model);
}

void Player::Update() {
	Move();
	Rotation();
}

//feature move. �p�b�h�ŉ񂷂͉̂����x�N�g�������ɂ��āA���̃x�N�g����rot�����f���ɓK�p���邾���ɂ���
void Player::Move() {
	char message[256];

	float MOVE_SPEED = 50.0f;
	static float MOVE_SPEED_JUMP = 30.0f;
	float minSpeed = 1.3f;
	float x = Pad(0).GetLStickXF();
	float y = Pad(0).GetLStickYF();
	float r = Pad(0).GetRTrigger();
	float l = Pad(0).GetLTrigger();
	//�A�N�Z�������܂ꂽ�瓥�܂ꂽ�p�x�ɂ���ĉ����x�N�g���̑傫����ω�������
	CVector3 accVec = CVector3::One();
	accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	accVec.y = 0.f;
	//�X�e�B�b�N�i�n���h���j�ŉ����x�N�g���̌��������߂Ă���
	CQuaternion qRot;
	if (fabsf(m_moveSpeed.x) > minSpeed || fabsf(m_moveSpeed.z) > minSpeed) {
		qRot.SetRotationDeg(CVector3::AxisY(), 1.4f * x);
	}
	else {
		//����قǂ̑��x���o�ĂȂ���
		qRot = CQuaternion::Identity();
	}
	m_rot.Multiply(qRot);
	m_rot.Multiply(accVec);
	//�Ԃ̑O������ێ����Ă���
	qRot.Multiply(m_forward);
	//�O�����Ɖ����x�N�g�������Z����
	CVector3 toPos;
	toPos = accVec;
	//���C���v�Z����
	CVector3 friction = m_moveSpeed;
	friction *= m_frictionParam;
	//�����x�N�g����xz�����ɖ��C�����Z����
	m_moveSpeed.x +=  friction.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z +=  friction.z * GameTime().GetFrameDeltaTime();
	//�ړ��x�N�g���ɉ����x�N�g�������Z����
	m_moveSpeed += toPos;
	//���f���������x�N�g���̌����Ɍ�������(Rotation�ł���)
	
	//BoostTest
	if (Pad(0).IsPress(enButtonB)) {
		m_moveSpeed += m_forward * m_boostParam;
	}
	//���f���̍��W�Ɉړ��x�N�g�������Z����
	qRot.Multiply(m_moveSpeed);
	m_pos += m_moveSpeed;
	sprintf_s(message, "Speed x...%f z...%f\n", m_moveSpeed.x, m_moveSpeed.z);
	OutputDebugStringA(message);
	m_model->SetPosition(m_pos);
}

void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	CQuaternion nRot = m_rot;
	nRot.SetRotationDeg(CVector3::AxisY(), 45.f + 180.f);
	nRot.Multiply(m_rot);
	m_model->SetRotation(nRot);
}