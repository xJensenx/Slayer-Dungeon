#pragma once
#include "GameObject.h"
#include "TutorialUI.h"

class TutorialState
{
protected:
	// �~�b�V�����N���X
	class TutorialUI* m_MissionUI;
	// �~�b�V�����̃q���g�N���X
	class TutorialUI* m_MissionHint;
	// �`���[�g���A���V�[���̃N���X
	class Tutorial* m_Tutorial;
	// ���Ԕԍ�
	int m_State;
	// �X�e�[�g�p����
	float m_CurTime;
	// �`���[�g���A������
	bool m_Finish;
	// �S���̃{�^���������ꂽ�̊m�F
	bool m_PushButton[4];

public:
	TutorialState() {}
	~TutorialState() {}

	// �`���[�g���A���V�[�����擾
	void SetTutorial(class Tutorial* pTutorial) { m_Tutorial = pTutorial; }

	// �`���[�g���A�������̃Z�b�^�[
	void SetTutorialFinish() { m_Finish = true; }

	// �S���̃{�^���������ꂽ�̊m�F
	void SetPushButton(int Num) { m_PushButton[Num] = true; }

	virtual void Init() { m_State = 0; m_CurTime = 0.0f; }
	virtual void Update() = 0;
	virtual void Uninit()
	{
		if (m_MissionUI != NULL)
		{
			m_MissionUI->SetDestroy();
			m_MissionUI = NULL;
		}
		
		if (m_MissionHint != NULL)
		{
			m_MissionHint->SetDestroy();
			m_MissionHint = NULL;
		}
	}
};

// ���A�̃X�e�[�g
class TutorialState_Greeting : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����P�̃X�e�[�g
class TutorialState_Mission01 : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����Q�̃X�e�[�g
class TutorialState_Mission02 : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����R�̃X�e�[�g
class TutorialState_Mission03 : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����S�̃X�e�[�g
class TutorialState_Mission04 : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����T�̃X�e�[�g
class TutorialState_Mission05 : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����U�̃X�e�[�g
class TutorialState_Mission06 : public TutorialState
{
public:
	void Update() override;
};

// �~�b�V�����S���N���A�������
class TutorialState_TutorialFinish : public TutorialState
{
public:
	void Update() override;
};