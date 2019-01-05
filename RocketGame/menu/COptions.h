#pragma once
class COptions : public GameObject
{
public:
	COptions();
	~COptions();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
};

