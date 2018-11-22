#pragma once
class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	bool Start() override;
	void Update() override;
private:
	SkinModelRender* m_model;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

