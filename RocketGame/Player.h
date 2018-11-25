#pragma once
class Player : public GameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
	void Move();
	void Rotation();
public:
	CVector3 GetPosition(){
		return m_pos;
	}
	CQuaternion GetRotation() {
		return m_rot;
	}
private:
	SkinModelRender* m_model;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_forward;
	CQuaternion m_rot = CQuaternion::Identity();
	const float m_frictionParam = -1.0;
	float m_boostParam = 1.5f;
};

