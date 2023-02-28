#pragma once
#include <unordered_map>
#include "AnimModelManager.h"

class AnimationManager
{
protected:
	// �^�C�~���O�̊���
	struct Timing
	{
		float StartTime = -1;
		float EndTime = -1;
	};
	// �������Ă���Q�[���I�u�W�F�N�g
	class GameObject* m_GameObject = nullptr;
	// �������Ă���Q�[���I�u�W�F�N�g�̃A�j���[�V�������f��
	class AnimModelManager* m_AnimModel = nullptr;
	// ���݂̃A�j���[�V�����̖��O
	const char* m_CurAnimationName;
	// �O�̃A�j���[�V�����̖��O
	const char* m_PrevAnimationName;
	// ���݂̃X�e�[�g
	int m_State = 0;
	// �O��̃X�e�[�g
	int m_PreviousState = 0;
	//// ���݂̃X�e�[�g
	//class StateMachine* m_State = 0;
	//// �O��̃X�e�[�g
	//class StateMachine* m_PreviousState = 0;
	// �u�����h���[�g
	float m_BlendRate = 0.0f;
	// ���݂̃A�j���[�V�����̃t���[��
	float m_CurFrame = 0.0f;
	// �O�̃A�j���[�V�����̃t���[��
	float m_PrevFrame = 0.0f;
	// ���݂̃A�j���[�V�������[�v�����邩
	bool m_CurLoop = true;
	// �O��̃A�j���[�V�������[�v�����邩
	bool m_PrevLoop = true;
	// �O�̃t���[���̍X�V���x
	float m_PrevPlayRate;
	// �A�j���[�V�����̒���
	float m_Duration;
	// �O�̃A�j���[�V�����������������i���[�v�ł͂Ȃ����Ɏg���j
	bool m_isPrevAniFinish;
	// �ʒm�𑗂�^�C�~���O
	std::unordered_map<std::string, Timing> m_Timing;
	// �҂����肻�̃^�C�~���O�ɒʒm�𑗂邽��
	std::unordered_map<std::string, float> m_Notify;
	// �ʒm�C�x���g���܂�����
	std::unordered_map<std::string, bool> m_NotifyDone;
	// PlayRate�i�A�j���[�V�����̑��x�j
	std::unordered_map<std::string, float> m_PlayRate;

public:
	AnimationManager() {}
	virtual ~AnimationManager() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void TimingManager() {}

	//template <typename T>
	//T* ChangeState()
	//{
	//	if (m_State != NULL) m_PreviousState = m_State;

	//	T* State = new T();
	//	State->SetCharacter(m_GameObject);
	//	State->SetAnimationManager(this);
	//	m_State = State;
	//	if (m_PreviousState == NULL) m_PreviousState = State;
	//}

	// ���݂̃X�e�[�g�̏��擾
	int GetState() { return m_State; }
	// �O��̃X�e�[�g�̏��擾
	int GetPreviousState() { return m_PreviousState; }
	// �O�̃A�j���[�V�����������������̕ϐ��̃Q�b�^�[
	bool GetPrevAniStatus() { return m_isPrevAniFinish; }
	// ���݂̒������擾
	float GetDuration() { return m_AnimModel->GetAnimDuration(m_CurAnimationName); }

	// ���݂�Animation���O�⃋�[�v�̐ݒu
	void SetAnimationName(const char* Name)
	{
		m_CurAnimationName = Name;
	}

	// ��������Q�[���I�u�W�F�N�g��ݒu����
	void SetGameObject(GameObject* _Parent)
	{
		m_GameObject = _Parent;
	}
	// ��������A�j���[�V�������f����ݒu����
	void SetAnimModel(AnimModelManager* _AnimModelManager)
	{
		m_AnimModel = _AnimModelManager;
	}
	// �O�̃A�j���[�V�������I�������̐ݒu
	void SetPrevAniFinish(bool Finish) { m_isPrevAniFinish = Finish; }

	// ���݂̃t���[�����擾
	float GetCurFrame() { return m_CurFrame; }
};