#pragma once
#include "physics/CSphereCollider.h"

//class CSphereCollider;
namespace ZekeEngine {
	class CCameraCollisionSlover
	{
	public:
		CCameraCollisionSlover();
		~CCameraCollisionSlover();
		void Init(float radius);

		bool Execute(CVector3& result, const CVector3& position, const CVector3& target);
	private:
		CSphereCollider		m_collider;
		float				m_radius = 0.0f;
	};
}