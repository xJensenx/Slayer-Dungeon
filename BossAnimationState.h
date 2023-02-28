#pragma once
class BossAnimationState
{
protected:
	// �{�X�N���X
	class Boss* m_Character;
	// �{�X�̃A�j���[�V�����}�l�[�W���[�N���X
	class BossAnimation* m_AnimationTree;
	// �ʒm�p
	std::unordered_map<std::string, float> m_Notify;
	// �ʒm�pbool
	std::unordered_map<std::string, bool> m_NotifyDone;
	// �t���[����
	float m_Frame;
	// �v���C���[�g
	float m_PlayRate;
	// �A�j���[�V�����̒���
	float m_Duration;
	// ���[�v���Ă��邩�ǂ���
	bool m_Loop;


public:
	BossAnimationState() {}
	~BossAnimationState() {}

	// �{�X��ݒu
	void SetCharacter(class Boss* Char) { m_Character = Char; }
	// �A�j���[�V�����}�l�[�W���[���Z�b�g
	void SetAnimationTree(class BossAnimation* Animation) { m_AnimationTree = Animation; }

	// �t���[�����擾
	float GetFrame() { return m_Frame; }
	// ���[�v�̃Q�b�^�[
	bool GetLoop() { return m_Loop; }

	// ����������
	virtual void Init() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �I������
	virtual void Uninit()
	{
		// ���������
		m_Notify.clear();
		m_NotifyDone.clear();
	}
};

// �ҋ@���
class BossAnimation_Idle : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ������
class BossAnimation_Run : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// Roar���
class BossAnimation_Roar : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �W�����v���
class BossAnimation_Jump : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// HeavyPunch���
class BossAnimation_HeavyPunch : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 覐΂��������
class BossAnimation_SummonMeteor : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// JumpAtk���
class BossAnimation_JumpAtk : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// JumpAtkSec���
class BossAnimation_JumpAtkSec : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// Dead���
class BossAnimation_Dead : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTERoar���
class BossAnimation_QTERoar : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEAfterRoar���
class BossAnimation_QTEAfterRoar : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEInjured���
class BossAnimation_QTEInjured : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// RageAtk01���
class BossAnimation_RageAtk01 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ShootFireBall01���
class BossAnimation_ShootFireBall01 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ShootFireBall02���
class BossAnimation_ShootFireBall02 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ShootFireBall03���
class BossAnimation_ShootFireBall03 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �\����Ԃ�覐Ώ������
class BossAnimation_RageSummonMeteor : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �v���C���[�̎���ɉ���Ă���t�@�C�A�{�[�����������
class BossAnimation_SummonRotateFireBall : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};