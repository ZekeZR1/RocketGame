#pragma once
class SoccerBall : public GameObject
{
public:
	SoccerBall();
	~SoccerBall();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	SkinModelRender * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

