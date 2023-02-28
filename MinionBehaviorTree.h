#pragma once
class MinionBehaviorTree
{
protected:
	// Minion�N���X
	class Minion* m_Character;
	// Minion�̃A�j���[�V�����}�l�[�W���[
	class MinionAnimation* m_AnimationTree;
public:
	MinionBehaviorTree() {}
	~MinionBehaviorTree() {}

	// �L�����N�^�[���Z�b�g
	void SetCharacter(Minion* Character) { m_Character = Character; }
	// �A�j���[�V�����}�l�[�W���[���Z�b�g
	void SetAnimationTree(MinionAnimation* Animation) { m_AnimationTree = Animation; }

	// ������
	virtual void Init() = 0;
	// �X�V����
	virtual void Update() = 0;
};

class MinionBehaviorTree_Idle : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Chase : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Attack : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_BeenHit : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_TutorialBeenHit : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Show : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Dead : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

