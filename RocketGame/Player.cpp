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

//feature move. パッドで回すのは加速ベクトルだけにして、そのベクトルのrotをモデルに適用するだけにする
void Player::Move() {
	char message[256];

	float MOVE_SPEED = 50.0f;
	static float MOVE_SPEED_JUMP = 30.0f;
	float minSpeed = 1.3f;
	float x = Pad(0).GetLStickXF();
	float y = Pad(0).GetLStickYF();
	float r = Pad(0).GetRTrigger();
	float l = Pad(0).GetLTrigger();
	//アクセルが踏まれたら踏まれた角度によって加速ベクトルの大きさを変化させる
	CVector3 accVec = CVector3::One();
	accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	accVec.y = 0.f;
	//スティック（ハンドル）で加速ベクトルの向きを決めていく
	CQuaternion qRot;
	if (fabsf(m_moveSpeed.x) > minSpeed || fabsf(m_moveSpeed.z) > minSpeed) {
		qRot.SetRotationDeg(CVector3::AxisY(), 1.4f * x);
	}
	else {
		//回れるほどの速度が出てないよ
		qRot = CQuaternion::Identity();
	}
	m_rot.Multiply(qRot);
	m_rot.Multiply(accVec);
	//車の前方向を保持しておく
	qRot.Multiply(m_forward);
	//前方向と加速ベクトルを加算する
	CVector3 toPos;
	toPos = accVec;
	//摩擦を計算する
	CVector3 friction = m_moveSpeed;
	friction *= m_frictionParam;
	//加速ベクトルのxz成分に摩擦を加算する
	m_moveSpeed.x +=  friction.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z +=  friction.z * GameTime().GetFrameDeltaTime();
	//移動ベクトルに加速ベクトルを加算する
	m_moveSpeed += toPos;
	//モデルを加速ベクトルの向きに向かせる(Rotationでやるわ)
	
	//BoostTest
	if (Pad(0).IsPress(enButtonB)) {
		m_moveSpeed += m_forward * m_boostParam;
	}
	//モデルの座標に移動ベクトルを加算する
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