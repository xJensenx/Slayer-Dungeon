#pragma once
class PlayerSkill
{
protected:
	class Player* m_Character;
	class PlayerAnimation* m_Animation;
	bool m_ActivateSuccess;
public:
	PlayerSkill() {}
	~PlayerSkill() {}

	virtual void Init() = 0;
	virtual void Activate(int Slot) = 0;

	// プレイヤーをセット
	void SetCharacter(class Player* Char) { m_Character = Char; }
	// アニメーションマネージャーをセット
	void SetAnimationManager(class PlayerAnimation* Anim) { m_Animation = Anim; }
};

class PlayerShootAllSword : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerShootFromSky : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerChargeShoot : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerSwordMachineGun : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerRushSword : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerShootMultipleTimeSword : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerSkillAttackCombo : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerSkillShootAtOnce : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};

class PlayerSummonBigSword : public PlayerSkill
{
public:
	void Init() override;
	void Activate(int Slot) override;
};