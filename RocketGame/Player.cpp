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

	//前軸回転
	CQuaternion uRot = CQuaternion::Identity();
	CQuaternion fRot = CQuaternion::Identity();
	CVector3 lforward;
	if (!m_charaCon->IsOnGround()) {
		if (Pad(0).IsPress(enButtonRB1)) {
			fRot.SetRotationDeg(m_forward, (-x * ROTATION_SPEED));
			m_rot.Multiply(fRot);
		}
		else {
			//上軸回転
			uRot.SetRotationDeg(m_up, x * ROTATION_SPEED);
			m_rot.Multiply(uRot);
		}
		//横軸回転 Holizontal Axis
		CQuaternion hRot = CQuaternion::Identity();
		hRot.SetRotationDeg(m_right, y * ROTATION_SPEED);
		m_rot.Multiply(hRot);
	}
	uRot.SetRotationDeg(m_up, x * ROTATION_SPEED);
	m_rot.Multiply(uRot);
	//軸が変化する
	lforward = m_forward;
	m_rot.Multiply(lforward);
	CVector3 accVec = lforward;
	accVec.Normalize();
	accVec.y = 0;
	accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	m_moveSpeed += accVec;
	//摩擦を計算する
	if (Pad(0).IsPress(enButtonRB1) && m_charaCon->IsOnGround()) {
		m_frictionParam = -0.3f;
	}
	else {
		m_frictionParam = -1.f;
	}
	CVector3 friction = m_moveSpeed;
	friction *= m_frictionParam;
	//加速ベクトルのxz成分に摩擦を加算する
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
	////アクセルが踏まれたら踏まれた角度によって加速ベクトルの大きさを変化させる
	//CVector3 accVec = CVector3::One();
	//accVec *= r * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	//accVec.y = 0.f;
	////スティック（ハンドル）で加速ベクトルの向きを決めていく
	//CQuaternion qRot;
	//if (fabsf(m_moveSpeed.x) > minSpeed || fabsf(m_moveSpeed.z) > minSpeed) {
	//	qRot.SetRotationDeg(CVector3::AxisY(), 1.4f * x);
	//}
	//else {
	//	//回れるほどの速度が出てないよ
	//	qRot = CQuaternion::Identity();
	//}
	//m_rot.Multiply(qRot);
	//m_rot.Multiply(accVec);
	////車の前と右方向を保持しておく
	//qRot.Multiply(m_forward);
	//qRot.Multiply(m_right);
	////前方向と加速ベクトルを加算する
	//CVector3 toPos;
	//toPos = accVec;
	////摩擦を計算する
	//CVector3 friction = m_moveSpeed;
	//friction *= m_frictionParam;
	////加速ベクトルのxz成分に摩擦を加算する
	//m_moveSpeed.x +=  friction.x * GameTime().GetFrameDeltaTime();
	//m_moveSpeed.z +=  friction.z * GameTime().GetFrameDeltaTime();
	////TODO : 重力追加したときに消す↓
	//m_moveSpeed.y +=  friction.y * GameTime().GetFrameDeltaTime();
	////移動ベクトルに加速ベクトルを加算する
	//m_moveSpeed += toPos;
	////モデルを加速ベクトルの向きに向かせる(Rotationでやるわ)
	//
	////BoostTest
	//m_boostVec = m_forward;
	//bRot.SetRotationDeg(m_right, 1.f * y);
	//bRot.Multiply(m_boostVec);
	//if (Pad(0).IsPress(enButtonB)) {
	//	m_moveSpeed += m_forward * m_boostParam;
	//}
	//else {
	//	//ブーストによる加速は無くなるよ
	//	m_boostVec = CVector3::Zero();
	//}
	//m_rot.Multiply(bRot);
	////回転テスト
	//if (Pad(0).IsPress(enButtonRight)) {
	//	m_moveSpeed += m_right;
	//}
	////
	////モデルの座標に移動ベクトルを加算する
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
	//移動ベクトルとは別のモデル自体の回転情報
	
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