#pragma once
class PlayerAnimationState
{
protected:
	// �v���C���[�N���X
	class Player* m_Character;
	// �v���C���[�̃A�j���[�V�����}�l�[�W���[�N���X
	class PlayerAnimation* m_AnimationTree;
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
	PlayerAnimationState() {}
	~PlayerAnimationState() {}

	// �{�X��ݒu
	void SetCharacter(class Player* Char) { m_Character = Char; }
	// �A�j���[�V�����}�l�[�W���[���Z�b�g
	void SetAnimationTree(class PlayerAnimation* Animation) { m_AnimationTree = Animation; }

	// �t���[�����擾
	float GetFrame() { return m_Frame; }
	// ���[�v�̃Q�b�^�[
	bool GetLoop() { return m_Loop; }
	// �v���C���[�g���Q�b�g
	float GetPlayRate() { return m_PlayRate; }

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
class PlayerAnimation_Idle : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ������
class PlayerAnimation_Run : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�P���
class PlayerAnimation_Attack01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�Q���
class PlayerAnimation_Attack02 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�R���
class PlayerAnimation_Attack03 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�S���
class PlayerAnimation_Attack04 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U���O�T���
class PlayerAnimation_Attack05 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �u���b�N���
class PlayerAnimation_Block : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �u���b�N�I�����
class PlayerAnimation_BlockFinish : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �h�䐬���������
class PlayerAnimation_BlockCounter : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �U�����ꂽ���
class PlayerAnimation_Hit : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �E���g�O�P�̂P�i�ڏ��
class PlayerAnimation_Ult01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �E���g�O�P�̂Q�i�ڏ��
class PlayerAnimation_Ult0102 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTE�̔�����P���
class PlayerAnimation_QTEDodge01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTE�̔�����Q���
class PlayerAnimation_QTEDodge02 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTE�̌��𓊂�����
class PlayerAnimation_QTEThrowSword : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ���������
class PlayerAnimation_Dead : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �|�����
class PlayerAnimation_KnockedDown : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �N������
class PlayerAnimation_GetUp : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ��������
class PlayerAnimation_Dodge : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���P���
class PlayerAnimation_Skill01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���Q���
class PlayerAnimation_Skill02 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���R���
class PlayerAnimation_Skill03 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���S���
class PlayerAnimation_Skill04 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���T���
class PlayerAnimation_Skill05 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���U���
class PlayerAnimation_Skill06 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���V���
class PlayerAnimation_Skill07 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���W���
class PlayerAnimation_Skill08 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// �X�L���X���
class PlayerAnimation_Skill09 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};