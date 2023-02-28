#pragma once
class BossBehaviorTree
{
protected:
	// �{�X�N���X
	class Boss* m_Character;
	// �{�X�̃A�j���[�V�����}�l�[�W���[
	class BossAnimation* m_AnimationTree;
public:
	BossBehaviorTree() {}
	~BossBehaviorTree() {}

	// �L�����N�^�[���Z�b�g
	void SetCharacter(Boss* Character) { m_Character = Character; }
	// �A�j���[�V�����}�l�[�W���[���Z�b�g
	void SetAnimationTree(BossAnimation* Animation) { m_AnimationTree = Animation; }

	// ������
	virtual void Init() = 0;
	// �X�V����
	virtual void Update() = 0;
};

// �ҋ@���
class BossIdle : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �ǂ����
class BossChase : public BossBehaviorTree
{
private:

public:
	void Init() override;
	void Update() override;
};

// �U�����
class BossAttack : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �W�����v�U��
class BossJumpAtk : public BossBehaviorTree
{
private:
	// �W�����v���Ă��邩�ǂ���
	bool m_isJump;
	// �W�����v�U���������ǂ���
	bool m_JumpAtk;
	// �U���̌x��
	class Boss_AttackWarning* m_WarningEffect;

public:
	void Init() override;
	void Update() override;
};

// �W�����v�U���Q�i��
class BossJumpAtkSec : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �\���U��
class BossRageAtk : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �|����Ă�����
class BossDead : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �J�b�g�V�[�����
class BossShow : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// ���ԏ��
class BossRoar : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// QTE���
class BossQTE : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 覐΂��������
class BossSummonMeteor : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �t�@�C�A�{�[��������������
class BossShootFireBall : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �\������覐΂�����������
class BossRageSummonMeteor : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// �v���C���[�̎���Ƀt�@�C�A�{�[��������������
class BossShootRotateFireBall : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};