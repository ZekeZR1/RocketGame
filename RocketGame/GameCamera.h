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
	//TODO : ‹–ìŠp‚à—~‚µ‚¢‚Æ‚±‚ë
	//TODO : json‚ÉƒZ[ƒu‚µ‚Ä‚ ‚éİ’è‚ğ“Ç‚İ‚Ş‚æ‚¤‚É‚·‚é
	const float m_distanceMoveParam = 50.f;
	const float m_raiseViewPoint = 20.f;
	const float m_maxDistance = 650.f;
	const float m_minDistance = 200.f;
	float m_distanceToTarget = 300.f;
	float m_cameraRotationSpeed = 2.f;
	CVector3 m_target = { 0.0f, 20.0f, 0.0f };
	CVector3 m_toCameraPos = { 0.0f, 50.0f, 300};
};

