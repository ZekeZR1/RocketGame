#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"

Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start() {
	m_octane = NewGO<SkinModelRender>(0, "octane");
	m_octane->Init(L"Assets/modelData/Octane.cmo", nullptr, 0, enFbxUpAxisY);
	m_stage = NewGO<SkinModelRender>(0, "stage");
	m_stage->Init(L"Assets/modelData/Stage.cmo",nullptr,0,enFbxUpAxisY);
	m_rot.SetRotationDeg(CVector3::AxisY(), 90.f);
	m_stage->SetRotation(m_rot);

	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");

	return true;
}

void Game::Update(){
	m_octane->SetPosition(m_pos);
	m_octane->SetRotation(m_rot);
	if (Pad(0).IsPress(enButtonUp)) {
		m_cameraPos.x -= 10.f;
	}
	if (Pad(0).IsPress(enButtonDown)) {
		m_cameraPos.x += 10.f;
	}
	if (Pad(0).IsPress(enButtonRight)) {
		m_cameraPos.z += 10.f;
	}
	if (Pad(0).IsPress(enButtonLeft)) {
		m_cameraPos.z -= 10.f;
	}
	m_octane->SetPosition(m_cameraPos);
}

void Game::Render() {
}