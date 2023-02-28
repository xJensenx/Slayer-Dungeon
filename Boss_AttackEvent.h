#pragma once
class Boss_AttackEvent
{
protected:
	// �{�X
	class Boss* m_Character;
	
	// �{�b�N�X�L���X�g�̒u�����W
	D3DXVECTOR3 m_Origin;
	// �{�b�N�X�L���X�g�̃T�C�Y
	D3DXVECTOR3 m_Size;
	// �ۃL���X�g�̃T�C�Y
	float m_SphereSize;
	// Physics�L���X�g�ϐ�
	class PhysicsCast* m_Phy;

public:
	Boss_AttackEvent() {}
	~Boss_AttackEvent() {}

	// �{�X�̃Z�b�^�[
	void SetCharacter(class Boss* Char) { m_Character = Char; }
	
	// �_���[�W�̃C�x���g
	virtual void DamageEvent() = 0;
};

class Boss_Attack_HeavyAtk : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};

class Boss_Attack_JumpAtk : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};

class Boss_Attack_JumpAtkSec : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};

class Boss_Attack_KnockBack : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};