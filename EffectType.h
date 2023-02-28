#pragma once
class EffectType
{
protected:
	// �G�t�F�N�g�N���X
	class Effect* m_Effect;
	// �e�N�X�`���̏c������܂������L�^
	int m_Tate;
	// �e�N�X�`���̉�������܂������L�^
	int m_Yoko;
	// �e�N�X�`���A�j���[�V�����p
	int m_Cnt;
public:
	EffectType() {}
	~EffectType() {}

	// �G�t�F�N�g���Z�b�g
	void SetEffect(class Effect* pEffect) { m_Effect = pEffect; }

	// ��������
	virtual void Init() = 0;
	// �X�V����
	virtual void Update();
};

class EffectType_Block : public EffectType
{
public:
	void Init() override;
};

class EffectType_AttackHit : public EffectType
{
public:
	void Init() override;
};

class EffectType_BossMeteor : public EffectType
{
public:
	void Init() override;
};