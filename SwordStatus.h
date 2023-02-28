#pragma once
class SwordStatus
{
protected:
	class Sword* m_Sword;
	class Player* m_Character;
	class GameObject* m_TargetObj;

	float m_CurShootTime;
	// �ҋ@��Ԃɖ߂鎞��
	const float m_TotalIdleTime = 0.2f * Manager::Time;
	float m_IdleAnimTime;
	// �ڕW�܂œ��B����܂ł̎���
	const float m_TotalShootTime = 1.0f * Manager::Time;

	D3DXVECTOR3 m_InitPos;
	D3DXVECTOR3 m_TargetPos;
	D3DXVECTOR3 m_InitUp;
	D3DXVECTOR3 m_EndPos;
	D3DXVECTOR3 m_EndTan;

	int m_IdleState;
public:
	SwordStatus() {}
	~SwordStatus() {}

	void SetCharacter(class Sword* pSword) { m_Sword = pSword; }

	virtual void Init() = 0;
	virtual void Update() = 0;
};

class SwordIdle : public SwordStatus
{
public:
	void Init() override;
	void Update() override;
};

class SwordShoot : public SwordStatus
{
public:
	void Init() override;
	void Update() override;
};

class SwordAttack : public SwordStatus
{
private:
	float m_TotalAttackTime = 0.0f;

	bool m_Damaged = false;
public:
	void Init() override;
	void Update() override;
};

class SwordAttack_ForSkill : public SwordStatus
{
private:
	float m_TotalAttackTime = 0.0f;

	bool m_Damaged = false;
public:
	void Init() override;
	void Update() override;
};

class SwordBlock : public SwordStatus
{
private:
	// �h��̎��������鎞��
	const float m_TotalBlockTime = 0.2f * Manager::Time;

	D3DXQUATERNION m_InitQua;

public:
	void Init() override;
	void Update() override;
};

class SwordUlt : public SwordStatus
{
private:
	bool m_isShake;
	bool m_Damaged;

	float m_ShakeStr;
public:
	void Init() override;
	void Update() override;
};

class SwordQTE : public SwordStatus
{
public:
	void Init() override;
	void Update() override;
};

class SwordShootStraight : public SwordStatus
{
public:
	void Init() override;
	void Update() override;
};

class SwordChargeShoot : public SwordStatus
{
private:
	float m_ChargeTime;
	const float m_FullChargeTime = 35.0f;

	D3DXVECTOR3 m_Direction;

	int m_ChargeState;
public:
	void Init() override;
	void Update() override;
};

class SwordSkill05 : public SwordStatus
{
private:
	// �p�x
	float m_Angle;
	// �_���[�W�������ǂ���
	bool m_Damaged;
public:
	void Init() override;
	void Update() override;
};

class SwordSkill06 : public SwordStatus
{
private:
	// ����
	int m_ShootCnt;
public:
	void Init() override;
	void Update() override;
};