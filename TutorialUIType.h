#pragma once
#include "ComponentInclude.h"

class TutorialUIType
{
protected:
	// チュートリアルUIのクラス
	class TutorialUI* m_Character;
	// クリアしてないのUIスプライト
	class SpriteComponent* m_Sprite;
	// クリアしたUIスプライト
	class SpriteComponent* m_ClearedSprite;
	// 時間用
	float m_Time;

public:
	TutorialUIType() {}
	~TutorialUIType() {}

	// チュートリアルUIをセット
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

// ミッションのUI
class TutorialUIType_MissionUI : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ミッション１のUI
class TutorialUIType_Mission01 : public TutorialUIType
{
private:
	// アニメーションステート
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// ミッション２のUI
class TutorialUIType_Mission02 : public TutorialUIType
{
private:
	// アニメーションステート
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// ミッション３のUI
class TutorialUIType_Mission03 : public TutorialUIType
{
private:
	// アニメーションステート
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// ミッション４のUI
class TutorialUIType_Mission04 : public TutorialUIType
{
private:
	// アニメーションステート
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// ミッション５のUI
class TutorialUIType_Mission05 : public TutorialUIType
{
private:
	// アニメーションステート
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// ミッション６のUI
class TutorialUIType_Mission06 : public TutorialUIType
{
private:
	// アニメーションステート
	int m_AnimationState;
public:
	void Init() override;
	void Update() override;
};

// ヒント１のUI
class TutorialUIType_Mission01Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ヒント２のUI
class TutorialUIType_Mission02Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ヒント３のUI
class TutorialUIType_Mission03Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ヒント４のUI
class TutorialUIType_Mission04Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ヒント５のUI
class TutorialUIType_Mission05Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// ヒント６のUI
class TutorialUIType_Mission06Hint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// 挨拶のUI
class TutorialUIType_GreetingHint : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};

// チュートリアル完了のUI
class TutorialUIType_TutorialFinish : public TutorialUIType
{
public:
	void Init() override;
	void Update() override;
};