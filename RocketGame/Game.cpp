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
	m_model.UpdateWorldMatrix(m_modelPos, CQuaternion::Identity(), CVector3::One());
	return true;
}

void Game::Update() {

}

void Game::Render() {
	m_model.Draw();
}