#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start() {
	m_model.Init(L"Assets/modelData/Octane.cmo",enFbxUpAxisY);
	m_rot = CQuaternion::Identity();
	m_rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	m_model.UpdateWorldMatrix(m_modelPos, m_rot, CVector3::One());
	return true;
}

void Game::Update(){
	if (Pad(0).IsPress(enButtonRB2)){
		m_modelPos.z -= 5.0f;
	}
	if (Pad(0).IsPress(enButtonLB2)) {
		m_modelPos.z += 5.0f;
	}
	m_model.UpdateWorldMatrix(m_modelPos, m_rot, CVector3::One());
}

void Game::Render() {
	m_model.Draw();
}