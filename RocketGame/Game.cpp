#include "stdafx.h"
#include "Game.h"


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
	m_stage->Init(L"Assets/modelData/Stage.cmo");
	return true;
}

void Game::Update(){
	m_octane->SetPosition(m_pos);
	m_octane->SetRotation(m_rot);
}

void Game::Render() {
}