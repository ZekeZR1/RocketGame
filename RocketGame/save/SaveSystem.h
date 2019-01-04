#pragma once
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

	void SetGameCameraData(SCameraData data) {
		m_cameraData = data;
		Save();
	}

	SCameraData GetGameCameraData() {
		Load();
		return m_cameraData;
	}
private:
	void Load();
	void Save();
	SCameraData m_cameraData;
};

static CSaveSystem& SaveSystem() {
	static CSaveSystem savesystem;
	return savesystem;
}