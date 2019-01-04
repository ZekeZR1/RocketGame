#pragma once
namespace ZekeEngine{
	class CSaveSystem : Noncopyable
	{
	public:
		CSaveSystem();
		~CSaveSystem();
		struct SCameraData {
			int viewAngle;
			float distanceToTarget;
			float cameraHeight;
			float cameraRotationSpeed;
		};
		void Load();
		void Save();
		SCameraData GetGameCameraData() {
			return m_cameraData;
		}
	private:
		SCameraData m_cameraData;
	};
}
