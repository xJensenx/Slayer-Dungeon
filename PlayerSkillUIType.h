#pragma once
class PlayerSkillUIType
{
protected:
	class PlayerSkillUI* m_Skill;

public:
	virtual void Init() = 0;

	void SetCharacter(class PlayerSkillUI* _Skill) { m_Skill = _Skill; }
};

class PlayerSkill01UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill02UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill03UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill04UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill05UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill06UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill07UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill08UI : public PlayerSkillUIType
{
public:
	void Init() override;
};

class PlayerSkill09UI : public PlayerSkillUIType
{
public:
	void Init() override;
};