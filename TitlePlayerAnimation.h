#pragma once
#include "AnimationManager.h"
class TitlePlayerAnimation :
	public AnimationManager
{
public:
	// �v���C���[�̃X�e�[�g���O
	enum PlayerState
	{
		Idle01 = 0,
		Idle02,
		Idle03,
		Chosen
	};
private:
	class TitleCharacter* m_Character = NULL;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	void ChangeState(PlayerState NextState)
	{
		m_PreviousState = m_State;	// �O��̃X�e�[�g���X�V����
		m_State = NextState;		// ���݂̃X�e�[�g���X�V����
		m_PrevFrame = m_CurFrame;	// �O�̃t���[���������݂̃t���[�����ɍX�V����
		m_CurFrame = 0.0f;			// ���݂̃t���[�������O�ɂ���i�ŏ�����n�߂�j
		m_BlendRate = 0.0f;			// �u�����h���[�g���O�ɂ���
		m_PrevLoop = m_CurLoop;		// �O��̃��[�v��Ԃ��X�V����

		switch (m_State)
		{
		case Idle01:
			m_CurAnimationName = "Idle01";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle02:
				m_AnimModel->LoadAnimation("Idle02", "Idle01");
				break;
			case Idle03:
				m_AnimModel->LoadAnimation("Idle03", "Idle01");
				break;
			}
			break;
		case Idle02:
			m_CurAnimationName = "Idle02";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle01:
				m_AnimModel->LoadAnimation("Idle01", "Idle02");
				break;
			case Idle03:
				m_AnimModel->LoadAnimation("Idle03", "Idle02");
				break;
			}
			break;
		case Idle03:
			m_CurAnimationName = "Idle03";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle02:
				m_AnimModel->LoadAnimation("Idle02", "Idle03");
				break;
			case Idle01:
				m_AnimModel->LoadAnimation("Idle01", "Idle03");
				break;
			}
			break;
		case Chosen:
			m_CurAnimationName = "Chosen";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle01:
				m_AnimModel->LoadAnimation("Idle01", "Chosen");
				break;
			case Idle02:
				m_AnimModel->LoadAnimation("Idle02", "Chosen");
				break;
			case Idle03:
				m_AnimModel->LoadAnimation("Idle03", "Chosen");
				break;
			}

			break;
		default:
			break;
		}
	}

	// �{�X�̕ϐ�������
	void SetCharacter(class TitleCharacter* Character)
	{
		m_Character = Character;
	}

};

