#include "stdafx.h"
#include "SoccerBall.h"


SoccerBall::SoccerBall()
{
}


SoccerBall::~SoccerBall()
{
}

bool SoccerBall::Start() {
	m_skinModel = NewGO<SkinModelRender>(0, "Ball");
	m_skinModel->Init(L"Assets/modelData/SoccerBall.cmo");
	m_skinModel->SetPosition(m_pos);
	m_skinModel->SetRotation(m_rot);
	return true;
}

void SoccerBall::Update() {

}

void SoccerBall::OnDestroy() {

}

