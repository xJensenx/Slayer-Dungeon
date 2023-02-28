#pragma once
class TitleSkillUIType
{
protected:
	class SpriteComponent* m_Sprite;
	class SpriteComponent* m_SpriteNS;
	class TitleSkillUI* m_SkillUI;

public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void Activate() = 0;

	void SetInfo(class TitleSkillUI* SkillUI, class SpriteComponent* Sprite, class SpriteComponent* SpriteNS)
	{
		m_SkillUI = SkillUI;
		m_Sprite = Sprite;
		m_SpriteNS = SpriteNS;
	}
};

class TitleSkillUISkill01 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill02 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill03 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill04 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill05 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill06 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill07 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill08 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};

class TitleSkillUISkill09 : public TitleSkillUIType
{
public:
	void Init() override;
	void Activate() override;
};