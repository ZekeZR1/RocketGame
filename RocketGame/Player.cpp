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
	m_pos.y += 50.f;
	m_model->SetPosition(m_pos);
	m_model->SetRotation(m_rot);

	m_forward = MainCamera().GetForward();
	m_right = MainCamera().GetRight();
	m_up = MainCamera().GetUp();

	m_charaCon = new CharacterController;
	CVector3 initPos = m_pos;
	initPos.y -= 50.f;
	m_charaCon->Init(100.0f, 300.0f, initPos, enFbxUpAxisY);
	//CQuaternion sRot = m_rot;
	//sRot.SetRotationDeg(CVector3::AxisY(), 45.f + 180.f);
	//m_model->SetRotation(sRot);
	//m_forward = MainCamera().GetForward();
	//m_forward.Normalize();
	//m_right = MainCamera().GetRight();
	//m_right.Normalize();
	//sRot.Multiply(m_forward);
	//sRot.Multiply(m_right);
	return true;
}

void Player::OnDestroy() {
	DeleteGO(m_model);
}

void Player::Update() {
	Movef();
	//Rotation();
}

void Player::Movef() {
	//TODO : implement virtual button
	float MOVE_SPEED = 500.f;
	static float MOVE_SPEED_JUMP = 30.0f;
	static float JUMP_SPEED = 630.0f;
	static float ROTATION_SPEED = 2.0f;
	//float minSpeed = 1.3f;
	float minSpeed = 0.f;
	float x = Pad(0).GetLStickXF();
	float y = Pad(0).GetLStickYF();
	float r = Pad(0).GetRTrigger();
	float l = Pad(0).GetLTrigger();

	//�O����]
	CQuaternion uRot = CQuaternion::Identity();
	CQuaternion fRot = CQuaternion::Identity();
	CVector3 lforward;
	if (!m_charaCon->IsOnGround()) {
		if (Pad(0).IsPress(enButtonRB1)) {
			fRot.SetRotationDeg(m_forward, (-x * ROTATION_SPEED));
			m_rot.Multiply(fRot);
		}
		else {
			//�㎲��]
			uRot.SetRotationDeg(m_up, x * ROTATION_SPEED);
			m_rot.Multiply(uRot);
		}
		//������] Holizontal Axis
		CQuaternion hRot = CQuaternion::Identity();
		hRot.SetRotationDeg(m_right, y * ROTATION_SPEED);
		m_rot.Multiply(hRot);
	}
	uRot.SetRotationDeg(m_up, x * ROTATION_SPEED);
	m_rot.Multiply(uRot);
	//�����ω�����
	lforward = m_forward;
	m_rot.Multiply(lforward);
	CVector3 accVec = lforward;
	accVec.Normalize();
	accVec.y = 0;
	accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	m_moveSpeed += accVec;
	//���C���v�Z����
	if (Pad(0).IsPress(enButtonRB1) && m_charaCon->IsOnGround()) {
		m_frictionParam = -0.3f;
	}
	else {
		m_frictionParam = -1.f;
	}
	CVector3 friction = m_moveSpeed;
	friction *= m_frictionParam;
	//�����x�N�g����xz�����ɖ��C�����Z����
	m_moveSpeed.x +=  friction.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z +=  friction.z * GameTime().GetFrameDeltaTime();
	//TODO : Boost
	if (Pad(0).IsPress(enButtonB)) {
		m_boostVec = lforward * m_boostParam;
	}
	else {
		m_boostVec = CVector3::Zero();
	}
	m_moveSpeed += m_boostVec;
	//TODO : Jump
	if (Pad(0).IsTrigger(enButtonA)) {
		m_moveSpeed.y = JUMP_SPEED;
	}
	//Collider
	//Gravity
	m_moveSpeed.y -= m_gravityParam;
	//Set
	m_pos = m_charaCon->Execute(1.0f / 30.0f, m_moveSpeed);
	m_model->SetPosition(m_pos);
	m_model->SetRotation(m_rot);
}

void Player::Move() {
	//char message[256];

	//float MOVE_SPEED = 50.0f;
	//static float MOVE_SPEED_JUMP = 30.0f;
	////float minSpeed = 1.3f;
	//float minSpeed = 0.f;
	//float x = Pad(0).GetLStickXF();
	//float y = Pad(0).GetLStickYF();
	//float r = Pad(0).GetRTrigger();
	//float l = Pad(0).GetLTrigger();
	////�A�N�Z�������܂ꂽ�瓥�܂ꂽ�p�x�ɂ���ĉ����x�N�g���̑傫����ω�������
	//CVector3 accVec = CVector3::One();
	//accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	//accVec.y = 0.f;
	////�X�e�B�b�N�i�n���h���j�ŉ����x�N�g���̌��������߂Ă���
	//CQuaternion qRot;
	//if (fabsf(m_moveSpeed.x) > minSpeed || fabsf(m_moveSpeed.z) > minSpeed) {
	//	qRot.SetRotationDeg(CVector3::AxisY(), 1.4f * x);
	//}
	//else {
	//	//����قǂ̑��x���o�ĂȂ���
	//	qRot = CQuaternion::Identity();
	//}
	//m_rot.Multiply(qRot);
	//m_rot.Multiply(accVec);
	////�Ԃ̑O�ƉE������ێ����Ă���
	//qRot.Multiply(m_forward);
	//qRot.Multiply(m_right);
	////�O�����Ɖ����x�N�g�������Z����
	//CVector3 toPos;
	//toPos = accVec;
	////���C���v�Z����
	//CVector3 friction = m_moveSpeed;
	//friction *= m_frictionParam;
	////�����x�N�g����xz�����ɖ��C�����Z����
	//m_moveSpeed.x +=  friction.x * GameTime().GetFrameDeltaTime();
	//m_moveSpeed.z +=  friction.z * GameTime().GetFrameDeltaTime();
	////TODO : �d�͒ǉ������Ƃ��ɏ�����
	//m_moveSpeed.y +=  friction.y * GameTime().GetFrameDeltaTime();
	////�ړ��x�N�g���ɉ����x�N�g�������Z����
	//m_moveSpeed += toPos;
	////���f���������x�N�g���̌����Ɍ�������(Rotation�ł���)
	//
	////BoostTest
	//m_boostVec = m_forward;
	//bRot.SetRotationDeg(m_right, 1.f * y);
	//bRot.Multiply(m_boostVec);
	//if (Pad(0).IsPress(enButtonB)) {
	//	m_moveSpeed += m_forward * m_boostParam;
	//}
	//else {
	//	//�u�[�X�g�ɂ������͖����Ȃ��
	//	m_boostVec = CVector3::Zero();
	//}
	//m_rot.Multiply(bRot);
	////��]�e�X�g
	//if (Pad(0).IsPress(enButtonRight)) {
	//	m_moveSpeed += m_right;
	//}
	////
	////���f���̍��W�Ɉړ��x�N�g�������Z����
	//qRot.Multiply(m_moveSpeed);
	//m_pos += m_moveSpeed;
	//sprintf_s(message, "Speed x...%f z...%f\n", m_moveSpeed.x, m_moveSpeed.z);
	//OutputDebugStringA(message);
	//m_model->SetPosition(m_pos);
}

void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//�ړ��x�N�g���Ƃ͕ʂ̃��f�����̂̉�]���
	
	//CQuaternion nRot = m_rot;
	//nRot.SetRotationDeg(CVector3::AxisY(), 45.f + 180.f);
	//nRot.Multiply(m_rot);
	//nRot.Multiply(bRot);
	//float angle;
	//CQuaternion yRot;
	//angle = atan2(m_moveSpeed.y, m_forward.x + m_forward.z);
	//yRot.SetRotation(m_right, angle);
	//nRot.Multiply(yRot);
	//nRot.Multiply(m_rRot);
	CQuaternion nRot = CQuaternion::Identity();
	nRot.SetRotationDeg(CVector3::AxisY(), 45.f + 180.f);
	nRot.Multiply(m_rot);
	m_model->SetRotation(nRot);
}