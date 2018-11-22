#pragma once
class GameCamera :  public GameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;

	void SetTarget(CVector3 tar) {
		m_target = tar;
	}
	void SetPosition(CVector3 pos) {
		m_toCameraPos = pos;
	}
private:
	CVector3 m_target = { 0.0f, 20.0f, 0.0f };
	CVector3 m_toCameraPos = { 0.0f, 50.0f, 250.0f };
};

