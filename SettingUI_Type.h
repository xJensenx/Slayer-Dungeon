#pragma once
class SettingUI_Type
{
protected:
	// �ݒ��UI�N���X
	class SettingUI* m_SettingUI;
	// �����{�^���N���X
	class SettingAdjustButton* m_AdjustButton;
public:
	SettingUI_Type() {}
	~SettingUI_Type() {}

	// UI�N���X��ݒu
	void SetSettingUI(class SettingUI* _UI) { m_SettingUI = _UI; }

	virtual void Init() = 0;
	virtual void Update();
};

class SettingUI_Type_BGM : public SettingUI_Type
{
public:
	void Init() override;
	void Update() override;
};

class SettingUI_Type_SE : public SettingUI_Type
{
public:
	void Init() override;
	void Update() override;
};
