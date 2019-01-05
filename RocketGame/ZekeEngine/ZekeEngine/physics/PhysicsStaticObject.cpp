/*!
* @brief	静的オブジェクト。
*/

#include "stdafx.h"
#include "../graphics/SkinModel.h"
#include "../graphics/SkinModelRender.h"
#include "PhysicsStaticObject.h"

namespace ZekeEngine {
	PhysicsStaticObject::PhysicsStaticObject()
	{
	}

	PhysicsStaticObject::~PhysicsStaticObject()
	{
		Engine().GetPhysicsWorld().RemoveRigidBody(m_rigidBody);
	}

	void PhysicsStaticObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot)
	{
		//メッシュコライダーを作成。
		m_meshCollider.CreateFromSkinModel(skinModel, nullptr);
		//剛体を作成、
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
		rbInfo.mass = 0.0f;
		rbInfo.pos = pos;
		rbInfo.rot = rot;
		m_rigidBody.Create(rbInfo);
		//剛体を物理ワールドに追加する。
		Engine().GetPhysicsWorld().AddRigidBody(m_rigidBody);
	}
	void PhysicsStaticObject::CreateMeshObject(SkinModelRender* skinModelRender, CVector3 pos, CQuaternion rot)
	{
		//メッシュコライダーを作成。
		m_meshCollider.CreateFromSkinModel(skinModelRender->GetSkinModel(), nullptr);
		//剛体を作成、
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
		rbInfo.mass = 0.0f;
		rbInfo.pos = pos;
		rbInfo.rot = rot;
		m_rigidBody.Create(rbInfo);
		//剛体を物理ワールドに追加する。
		Engine().GetPhysicsWorld().AddRigidBody(m_rigidBody);
	}
}