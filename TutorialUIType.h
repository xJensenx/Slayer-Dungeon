#pragma once
#include "ComponentInclude.h"

class TutorialUIType
{
protected:
	// �`���[�g���A��UI�̃N���X
	class TutorialUI* m_Character;
	// �N���A���ĂȂ���UI�X�v���C�g
	class SpriteComponent* m_Sprite;
	// �N���A����UI�X�v���C�g
	class SpriteComponent* m_ClearedSprite;
	// ���ԗp
	float m_Time;

public:
	TutorialUIType() {}
	~TutorialUIType() {}

	// �`���[�g���A��UI���Z�b�g
	void SetCharacter(class TutorialUI* UI) { m_Character = UI; }

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void TutorialClear()
	{
		if (m_Sprite != NULL)
		{
			m_Sprite->SetVisibility(false);
		}

		if (m_ClearedSprite != NULL)
		{
			m_ClearedSprite->SetVisibility(true);
		}
	}
};

// �~�b�V������UI
class TutorialUIType_MissionUI : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �~�b�V�����P��UI
class TutorialUIType_Mission01 : public TutorialUIType
{
private:
	// �A�j���[�V�����X�e�[�g
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// �~�b�V�����Q��UI
class TutorialUIType_Mission02 : public TutorialUIType
{
private:
	// �A�j���[�V�����X�e�[�g
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// �~�b�V�����R��UI
class TutorialUIType_Mission03 : public TutorialUIType
{
private:
	// �A�j���[�V�����X�e�[�g
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// �~�b�V�����S��UI
class TutorialUIType_Mission04 : public TutorialUIType
{
private:
	// �A�j���[�V�����X�e�[�g
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// �~�b�V�����T��UI
class TutorialUIType_Mission05 : public TutorialUIType
{
private:
	// �A�j���[�V�����X�e�[�g
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// �~�b�V�����U��UI
class TutorialUIType_Mission06 : public TutorialUIType
{
private:
	// �A�j���[�V�����X�e�[�g
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// �q���g�P��UI
class TutorialUIType_Mission01Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �q���g�Q��UI
class TutorialUIType_Mission02Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �q���g�R��UI
class TutorialUIType_Mission03Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �q���g�S��UI
class TutorialUIType_Mission04Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �q���g�T��UI
class TutorialUIType_Mission05Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �q���g�U��UI
class TutorialUIType_Mission06Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ���A��UI
class TutorialUIType_GreetingHint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// �`���[�g���A��������UI
class TutorialUIType_TutorialFinish : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};