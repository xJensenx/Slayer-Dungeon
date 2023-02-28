#pragma once
#include "GameObject.h"
#include "PlayerSkill.h"

class Player :public GameObject // �p��
{
public:
	// �U���̎��
	enum AttackType
	{
		NotAttacking = 0,
		Attack01,
		Attack02,
		Attack03,
		Attack04,
		Attack05,
		Block
	};
private:
	// �v���C���[�A�j���[�V����
	class PlayerAnimation* m_PlayerAnimation;

	class PlayerSkillUI* m_SkillUI[3];

	// Mp�o�[�̃N���X
	class PlayerMpBar* m_MpBar;

	// Dp�o�[�̃N���X
	class PlayerDpBar* m_DpBar;

	// �ړ����x
	float m_MovementSpd = 0.01f;
	// �U�����Ă��邩�ǂ���
	bool m_isAttacking;
	// ���̍U�����s���Ă���
	bool m_NextAtk;
	// ���݂̍U���̎��
	AttackType m_AttackType;
	// ������������
	bool m_ReadyToMove = false;
	// ��������
	float m_ReadyTime;
	// WalkValue
	D3DXVECTOR2 m_KeyValue;

	// �U�����x
	float m_AttackSpd;

	// �X�e�[�^�X�̐F��t�������
	bool m_StatusColor;
	// �X�e�[�^�X�̐F�͉��b�㌳�ɖ߂�
	float m_StatusTime;
	// 
	float m_StatusInitTime;
	// �X�e�[�^�X�̍ŏ��̐F
	D3DXVECTOR4 m_StatusInitColor;

	// ���̏��
	class Sword* m_Swords[5];
	// �����񕜂���
	float m_SwordRecover[5];
	// �����񕜂��鎞��
	float m_RecoverTime = 5.0f * Manager::Time;
	// ���݂̌��̔ԍ�
	int m_CurrentNo;

	// ����ł邩�ǂ���
	bool m_isDead;

	// ������Ă��邩�ǂ���
	bool m_Dodge;

	// ���݂�Hp
	float m_CurHp;

	// �t����Hp
	float m_MaxHp;

	// ���݂�Hp
	float m_CurMp;

	// �t����Hp
	float m_MaxMp;

	// ���݂�Dp
	float m_CurDp;

	// �t����Dp
	float m_MaxDp;

	// �v���C���[�̃R�}���h�̃X���b�g�ԍ�
	int m_Slot;

	// �O�̃X���b�g�ԍ�
	int m_LastSlot;

	// �R�}���h���X�g
	class PlayerCommand* m_CommandSlot[3];

	// �v���C���[�X�e�[�^�X�ϐ�
	class PlayerStatusWarning* m_PlayerStatus;

	// �v���C���[�X�L��
	class PlayerSkill* m_SkillSlot[3];


	// �h�䂵�Ă��邩�ǂ���
	bool m_isBlock;

	// �h�䐬�����ǂ���
	bool m_BlockSuccess;

	// ���G����
	float m_InvulTime;

	// ���G�ɓ����Ă��邩�ǂ���
	bool m_Invulnerable;

	// Ult�p�ϐ���������������������������������������������=
	// Ult�pState
	int m_UltState;
	// Ult���g���Ă��邩�ǂ���
	bool m_isUlt;
	// Ult�p�҂�����
	float m_UltWaitTime;

	// ������������������������������������������������������

	// Skill�p�ϐ���������������������������������������������=
	// �N�[���_�E��
	float m_CurCoolDown[3];
	// �ő�N�[���_�E��
	float m_MaxCoolDown[3];
	
	// ���̉J�̃^�C��
	float m_SwordRainTime;
	
	// ������������������������������������������������������

public:
	void Init()override;	// ��������
	void Update()override;	// �X�V����
	void Draw()override;	// �`�揈��

	// �_���[�W�󂯂���
	void DealDamage(float Damage) override;

	// �X�L���Z�b�g
	template <typename T>
	void SetSkill(int Slot)
	{
		if (m_SkillSlot[Slot] != NULL)
		{
			delete m_SkillSlot[Slot];
			m_SkillSlot[Slot] = NULL;
		}

		T* Skill = new T();
		Skill->Init();
		Skill->SetCharacter(this);
		Skill->SetAnimationManager(m_PlayerAnimation);

		m_SkillSlot[Slot] = Skill;
	}

	// �v���C���[�X�L�����g��
	void ActivateSkill(int Slot)
	{
		if (m_SkillSlot[Slot] != NULL && m_CurCoolDown[Slot] <= 0.0f)
		{
			m_SkillSlot[Slot]->Activate(Slot);
		}
	}

	// ���G���Ԃ��Z�b�g
	void SetInvulTime(float Time) { m_InvulTime = Time * Manager::Time; }

	// �X�L���𑕔�
	void SetInitSkill();

	// �X�L���R�}���h
	void SkillShortCut();

	// �V�������ɐ؂�ւ���
	void PrepareNewSwords();

	// ��_���[�W�󂯂���
	void KnockBackDamage(float Damage, D3DXVECTOR3 Dir) override;

	// �U������
	void AttackCombo(AttackType AT);

	// ���̍U���������s���Ă����Z�b�^�[
	void ReadyToAtk() { m_NextAtk = true; }

	// ���������Z�b�^�[
	void ReadyToMove(float Time)
	{
		m_ReadyToMove = true;
		m_ReadyTime = Time * Manager::Time;
	}
	// �������
	void TimeToDodge();

	// �U���C�x���g
	void AttackEvent();

	// �R�}���h����
	void CommandEvent();

	// �R�}���h�`�F�b�N
	void CommandCheck();

	// �����[����
	void RecoverSword();

	// Dodge�C�x���g
	void DodgeEvent();

	// ����ł��Ԃ��擾
	bool GetIsDead() { return m_isDead; }

	// Mp���Z�b�g
	void SetCurMp(float Mp) { m_CurMp = Mp; }

	// Mp�𑝂₷
	void AddMp(float AddAmt)
	{ 
		float TotalAmt = m_CurMp + AddAmt;
		if (TotalAmt > m_MaxMp)
		{
			m_CurMp = m_MaxMp;
			return;
		}

		m_CurMp = TotalAmt;
	}

	// Dp���Z�b�g
	void SetCurDp(float Dp) { m_CurDp = Dp; }

	// Dp�𑝂₷
	void AddDp(float AddAmt) { m_CurDp += AddAmt; }

	// Hp,Mp,Dp�̒���
	void AdjustGauge();

	// MpBar�̃Q�b�^�[
	class PlayerMpBar* GetMpBar() { return m_MpBar; }

	// DpBar�̃Q�b�^�[
	class PlayerDpBar* GetDpBar() { return m_DpBar; }

	// Ult�����ǂ���
	bool GetisUlt() { return m_isUlt; }

	// ���݂�Hp���擾
	float GetCurHp() { return m_CurHp; }

	// �t����Hp���擾
	float GetMaxHp() { return m_MaxHp; }

	// ���݂�Mp���擾
	float GetCurMp() { return m_CurMp; }

	// �t����Mp���擾
	float GetMaxMp() { return m_MaxMp; }

	// ���݂�Dp���擾
	float GetCurDp() { return m_CurDp; }

	// �t����Dp���擾
	float GetMaxDp() { return m_MaxDp; }

	// ���݂̃N�[���_�E�����擾
	float GetCurCooldown(int SlotNo) { return m_CurCoolDown[SlotNo]; }
	
	// ���݂̃N�[���_�E�����擾
	float GetMaxCooldown(int SlotNo) { return m_MaxCoolDown[SlotNo]; }

	// �U�����x���Q�b�g
	float GetAttackSpd() { return m_AttackSpd; }

	// ���S���̏���
	void DeadEvent();

	// Ult�𔭓�����
	void ActivateUlt();

	// Ult����
	void UltCommand();

	// Ult�̃X�e�[�g��؂�ւ���
	void ChangeUltState(int State) { m_UltState = State; }

	// �ړ�����
	void MoveEvent();
	
	// ��]����
	void RotateEvent();

	// �h�䂪�I���
	void BlockFinish() { m_isBlock = false; m_BlockSuccess = false; }

	// ���̖h��A�j���[�V����
	void SwordBlock(bool isBlock);

	// �ҋ@��Ԃɖ߂�
	void BackToIdle();

	// �v���C���[�̐F
	void StatusChangeColor();

	// �v���C���[�̐F��ς��鏈��
	void ChangeBackColor(D3DXVECTOR4 Color, float Time);

	// �X�L���p�֐�������������������������������������������������������������
	// �X�L���g���O�̏�������� 
	bool InitSkill();
	// �J�����Ɍ����ď��������
	bool InitRotCamSkill();
	// �N�[���_�E���p�֐�
	void CoolDownEvent();
	// �N�[���_�E�����Z�b�g����
	void SetCoolDown(int Slot) { m_CurCoolDown[Slot] = m_MaxCoolDown[Slot]; }

	// �S���̌����ˏo����
	void ShootAllSword();
	// ���̉J
	void RainSword();
	// �`���[�W����
	void ChargeSword();
	// ����A���O�ɑł�
	void SwordMachineGun();
	// �X�L���O�U
	void ShootSwordSkill06();
	// �X�L���O�V�iCombo�̐����ɂ���ď������ς��܂��A�P�͍ŏ��̍U���A�Q�͓�ځA�R�͍Ō�j
	void Skill07Combo(int Combo);
	// �X�L���O�W
	void Skill08Combo();
	// �X�L���O�X
	void Skill09Combo();


	// �O�ɓ˂�����ōU������
	void RushSword();

	// ������������������������������������������������������������������������
};