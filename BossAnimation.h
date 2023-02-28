#pragma once
#include "AnimationManager.h"
#include "BossAnimationState.h"

class BossAnimation :
    public AnimationManager
{
private:
	// �{�X
	class Boss* m_Character = NULL;
	// �A�j���[�V�����X�e�[�g
	class BossAnimationState* m_AnimationState;
	// �O�̃A�j���[�V�����X�e�[�g
	class BossAnimationState* m_PrevAnimationState;

	// �Q�[���p
	bool m_isJumpFinish = false; // �W�����v���̓t���[�����~�܂�
	bool m_isReadyJump = false; // �W�����v�̏���
	bool m_isJumpDmg = false;	// �W�����v�̍U���_���[�W�������ǂ���

public:
    void Init() override;
    void Uninit() override;
    void Update() override;

	// �W�����v�̃_���[�W���擾
	bool GetJumpDmg() { return m_isJumpDmg; }
	// �W�����v�̏����̏������
	bool GetReadyJump() { return m_isReadyJump; }
	// �W�����v���I���̃Q�b�^�[
	bool GetJumpFinish() { return m_isJumpFinish; }

	// �O�̃A�j���[�V�����X�e�[�g���擾
	template <typename T>
	bool GetPrevAnimationState()
	{
		// �X�e�[�g���Ȃ���false��return
		if (m_PrevAnimationState == NULL) return false;
		
		// ������ނȂ�return����
		if (typeid(*m_PrevAnimationState) == typeid(T)) return true;


		return false;
	}

	// ���݂̃A�j���[�V�����X�e�[�g���擾
	template <typename T>
	bool GetCurAnimationState()
	{
		// �X�e�[�g���Ȃ���false��return
		if (m_AnimationState == NULL) return false;

		// ������ނȂ�return����
		if (typeid(*m_AnimationState) == typeid(T)) return true;


		return false;
	}

	// �X�e�[�g��ς��鏈��
	template <typename T>
	void ChangeState()
	{
		// �A�j���[�V�����X�e�[�g��NULL�ł͂Ȃ��ꍇ�͏I���������s��
		if (m_AnimationState != NULL)
		{
			if (m_PrevAnimationState != NULL)
			{
				m_PrevAnimationState->Uninit();
				delete m_PrevAnimationState;
				m_PrevAnimationState = NULL;
			}
			m_PrevAnimationState = m_AnimationState;
			m_CurFrame = m_AnimationState->GetFrame();
			m_PrevLoop = m_AnimationState->GetLoop();		// �O��̃��[�v��Ԃ��X�V����
		}

		m_PrevFrame = m_CurFrame;	// �O�̃t���[���������݂̃t���[�����ɍX�V����
		m_CurFrame = 0.0f;			// ���݂̃t���[�������O�ɂ���i�ŏ�����n�߂�j
		m_BlendRate = 0.0f;			// �u�����h���[�g���O�ɂ���
		m_PrevAnimationName = m_CurAnimationName; // �O�̃A�j���[�V�������O���X�V����
		m_isReadyJump = false;		// �W�����v�p
		m_isJumpDmg = false;		// �W�����v�_���[�W�p

		// �A�j���[�V�����X�e�[�g��ǉ�����
		m_AnimationState = new T();
		// �{�X�̐ݒu
		m_AnimationState->SetCharacter(m_Character);
		// �A�j���[�V�����}�l�[�W���[�̐ݒu
		m_AnimationState->SetAnimationTree(this);
		// �A�j���[�V�����X�e�[�g�̏�����
		m_AnimationState->Init();
		// ���݂̃��[�v���擾
		m_CurLoop = m_AnimationState->GetLoop();

		// �A�j���[�V���������[�h
		m_AnimModel->LoadAnimation(m_PrevAnimationName, m_CurAnimationName);
	}

	// �{�X�̕ϐ�������
	void SetCharacter(class Boss* Character)
	{
		m_Character = Character;
	}

	// �W�����v�̕ϐ��𒲐�����
	void SetJumpFinish(bool isFinish)
	{
		m_isJumpFinish = isFinish;
	}
	// �W�����v�����̃Z�b�^�[
	void SetReadyJump(bool Ready)
	{
		m_isReadyJump = Ready;
	}
	// �W�����v�_���[�W�̃Z�b�^�[
	void SetJumpDmg(bool Dmg)
	{
		m_isJumpDmg = Dmg;
	}
};

