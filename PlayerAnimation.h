#pragma once
#include "AnimationManager.h"
#include "PlayerAnimationState.h"
#include "Player.h"
#include "Tutorial.h"

class PlayerAnimation : public AnimationManager
{
private:
	// �v���C���[�̃L�����N�^�[�����擾
	class Player* m_Character;
	// �v���C���[�̃A�j���[�V�����X�e�[�g
	class PlayerAnimationState* m_AnimationState;
	// �O�̃A�j���[�V�����X�e�[�g
	class PlayerAnimationState* m_PrevAniState;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	// �v���C���[�̃Z�b�^�[
	void SetCharacter(Player* Player) { m_Character = Player; }

	// �v���C���[�̃A�j���[�V������ς���
	template <typename T>
	void ChangeState()
	{
		if (m_AnimationState != NULL)
		{
			if (m_PrevAniState != NULL)
			{
				m_PrevAniState->Uninit();
				delete m_PrevAniState;
				m_PrevAniState = NULL;
			}
			m_PrevAniState = m_AnimationState;
			m_CurFrame = m_AnimationState->GetFrame();
			m_PrevLoop = m_AnimationState->GetLoop();
			m_PrevPlayRate = m_AnimationState->GetPlayRate();
		}

		m_PrevAnimationName = m_CurAnimationName;
		m_PrevFrame = m_CurFrame;	// �O�̃t���[���������݂̃t���[�����ɍX�V����
		m_CurFrame = 0.0f;			// ���݂̃t���[�������O�ɂ���i�ŏ�����n�߂�j
		m_BlendRate = 0.0f;			// �u�����h���[�g���O�ɂ���
		m_PrevLoop = m_CurLoop;		// �O��̃��[�v��Ԃ��X�V����

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

		m_AnimModel->LoadAnimation(m_PrevAnimationName, m_CurAnimationName);
	}

	// �O�̃A�j���[�V�����X�e�[�g���擾
	template <typename T>
	bool GetPrevAnimationState()
	{
		// �X�e�[�g���Ȃ���false��return
		if (m_PrevAniState == NULL) return false;

		// ������ނȂ�return����
		if (typeid(*m_PrevAniState) == typeid(T)) return true;


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
};

