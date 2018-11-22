#include "stdafx.h"
#include "Player.h"
#include "Stage.h"
#include "Game.h"
#include "GameCamera.h"

Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start() {
	m_player = NewGO<Player>(0,"Player");
	m_stage = NewGO<Stage>(0, "Stage");
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
	return true;
}

void Game::OnDestroy() {
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_stage);
}

void Game::Update(){
}

void Game::Render() {
}