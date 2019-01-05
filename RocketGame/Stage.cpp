#include "stdafx.h"
#include "Stage.h"


Stage::Stage()
{

}


Stage::~Stage()
{
	DeleteGO(m_model);
}

bool Stage::Start() {
	m_model = NewGO<SkinModelRender>(0, "Stage");
	m_model->Init(L"Assets/modelData/Tofu.cmo", nullptr, 0, enFbxUpAxisZ);
	m_model->SetPosition(m_pos);
	m_rot.SetRotationDeg(CVector3::AxisY(), 90.f);
	m_model->SetRotation(m_rot);
	m_physicsStaticObject.CreateMeshObject(m_model, m_pos, m_rot);
	return true;
}

void Stage::Update() {

}
