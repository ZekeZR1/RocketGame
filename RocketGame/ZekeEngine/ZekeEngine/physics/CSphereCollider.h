#pragma once
namespace ZekeEngine {
	class CSphereCollider
	{
	public:
		CSphereCollider();
		~CSphereCollider();
		void Create(const float radius);
		btCollisionShape* GetBody()
		{
			return shape;
		}
	private:
		btSphereShape * shape;
	};
}