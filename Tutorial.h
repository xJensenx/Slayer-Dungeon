#pragma once
#include "Scene.h"
#include "TutorialState.h"

class Tutorial :
    public Scene
{
private:
	// �S���̃`���[�g���A�������������ǂ���
	bool m_TutorialFinish = false;

	// �`���[�g���A���̃X�e�[�g
	class TutorialState* m_TutorialState;

	// �v���C���[
	class Player* m_TutorialPlayer;
	// Minion
	class Minion* m_TutorialMinion;
	// �~�b�V����UI
	class TutorialUI* m_MissionUI;

public:
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �`���[�g���A���������Z�b�g
	void SetTutorialFinish() { m_TutorialState->SetTutorialFinish(); }

	// �{�^�������ꂽ���Z�b�g
	void SetPushButton(int Num) { m_TutorialState->SetPushButton(Num); }

	// �`���[�g���A������
	void SetFinish() { m_TutorialFinish = true; }

	// �`���[�g���A���̃X�e�[�g�ύX
	template <typename T>
	void ChangeState()
	{
		// ���ɑ��݂��Ă���ꍇ�͍폜
		if (m_TutorialState != NULL)
		{
			m_TutorialState->Uninit();
			delete m_TutorialState;
			m_TutorialState = NULL;
		}

		// �V�����X�e�[�g�����
		T* State = new T();
		State->SetTutorial(this);
		State->Init();

		// �X�e�[�g��ϐ��ɓ����
		m_TutorialState = State;
	}

	// �`���[�g���A���̃X�e�[�g���Q�b�g
	template <typename T>
	bool GetTutorialState()
	{
		if (typeid(*m_TutorialState) == typeid(T))
		{
			return true;
		}
		
		return false;
	}

	// �`���[�g���A������������Ԃ��擾
	bool GetTutorialFinish() { return m_TutorialFinish; }

	// �`���[�g���A���̃v���C���[���擾
	class Player* GetPlayer() { return m_TutorialPlayer; }

	// �`���[�g���A����Minion���擾
	class Minion* GetMinion() { return m_TutorialMinion; }
};

