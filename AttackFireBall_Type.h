#pragma once
class AttackFireBall_Type
{
protected:
	// �t�@�C�A�{�[���̃N���X
	class AttackFireBall* m_FireBall;
	// �^�[�Q�b�g
	class GameObject* m_TargetObj;
	// �i�s������
	float m_CurTime;
	// �ړI�܂ł̎��Ԑݒu
	float m_TotalTime;
	// �������W
	D3DXVECTOR3 m_InitPos;


public:
	AttackFireBall_Type() {}
	~AttackFireBall_Type() {}

	// �t�@�C�A�{�[�����Z�b�g
	void SetCharacter(class AttackFireBall* pFireBall) { m_FireBall = pFireBall; }
	// �^�[�Q�b�g��ݒu
	void SetTarget(class GameObject* Target) { m_TargetObj = Target; }
	
	// ����������
	virtual void Init() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �_���[�W����
	virtual void DamageEvent();
	// �G�t�F�N�g����
	virtual void EffectEvent();
};

class AttackFireBall_Type_ShootTowardsTarget : public AttackFireBall_Type
{
public:
	void Init() override;
	void Update() override;
};

class AttackFireBall_Type_HermiteShoot : public AttackFireBall_Type
{
public:
	void Init() override;
	void Update() override;
};

class AttackFireBall_Type_ChargeShoot : public AttackFireBall_Type
{
private:
	// ���݂̃X�e�[�g�i�@�^�[�Q�b�g�̎��͂ňړ����Ă���A�A������ƌ��ɉ����Č���������A�B�^�[�Q�b�g�Ɍ����܂��j
	int m_State;
	// ����
	D3DXVECTOR3 m_Direction;
public:
	void Init() override;
	void Update() override;
};