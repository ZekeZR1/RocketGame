#pragma once
#include "PhysicsDebugDraw.h"

namespace ZekeEngine {

	class RigidBody;

	class PhysicsWorld {
		btDefaultCollisionConfiguration* collisionConfig = nullptr;
		btCollisionDispatcher* collisionDispatcher = nullptr;
		btBroadphaseInterface* overlappingPairCache = nullptr;
		btSequentialImpulseConstraintSolver* constraintSolver = nullptr;
		btDiscreteDynamicsWorld*	 dynamicWorld = nullptr;
//		CPhysicsDebugDraw									 m_debugDraw;
	public:
		~PhysicsWorld();
		void Init();
		void Update();
		void DebubDrawWorld();
		void Release();
		/*!
		* @brief	�_�C�i�~�b�N���[���h���擾�B
		*/
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return dynamicWorld;
		}
		/*!
		* @brief	���̂�o�^�B
		*/
		void AddRigidBody(RigidBody& rb);
		/*!
		* @brief	���̂�j���B
		*/
		void RemoveRigidBody(RigidBody& rb);
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}
		void ContactText(
			btCollisionObject* colObj,
			btCollisionWorld::ContactResultCallback& resultCallback
		)
		{
			dynamicWorld->contactTest(colObj, resultCallback);
		}
	};
}