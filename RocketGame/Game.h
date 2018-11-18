#pragma once
class Game : public GameObject
{
public:
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render() override;
private:
	SkinModel m_model;
	CVector3 m_modelPos;
};

