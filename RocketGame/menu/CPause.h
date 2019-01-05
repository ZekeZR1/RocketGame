#pragma once
class CPause : public GameObject
{
public:
	CPause();
	~CPause();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:

};
