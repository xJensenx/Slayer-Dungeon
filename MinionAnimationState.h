#pragma once
class MinionAnimationState
{
protected:
	// Minion�̃N���X
	class Minion* m_Character;

	// Minion�̃A�j���[�V�����}�l�[�W���[
	class MinionAnimation* m_AnimationTree;
	// �ʒm�p
	std::unordered_map<std::string, float> m_Notify;
	// �ʒm�pbool
	std::unordered_map<std::string, bool> m_NotifyDone;

	// �t���[����
	float m_Frame;
	// �A�j���[�V�����̒���
	float m_Duration;
	// ���[�v
	bool m_Loop;
	// �v���C���[�g
	float m_PlayRate;

public:
	MinionAnimationState() {}
	~MinionAnimationState() {}

	// Minion��ݒu
	void SetCharacter(class Minion* _Minion) { m_Character = _Minion; }
	// �A�j���[�V�����}�l�[�W���[���Z�b�g
	void SetAnimationTree(class MinionAnimation* _Animation) { m_AnimationTree = _Animation; }

	// �t���[�����擾
	float GetFrame() { return m_Frame; }
	// �v���C���[�g�擾
	float GetPlayRate() { return m_PlayRate; }
	// ���[�v�擾
	bool GetLoop() { return m_Loop; }

	// ����������
	virtual void Init() = 0;
	// �X�V����
	virtual void Update() = 0;
};

// �ҋ@���
class MinionAnimationState_Idle : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ������
class MinionAnimationState_Run : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�P���
class MinionAnimationState_Attack01 : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�Q���
class MinionAnimationState_Attack02 : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �_���[�W�󂯂����
class MinionAnimationState_Hit : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �J�b�g�V�[�����
class MinionAnimationState_Show : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �|���ꂽ���
class MinionAnimationState_Dead : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};
