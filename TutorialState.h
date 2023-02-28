#pragma once
#include "GameObject.h"
#include "TutorialUI.h"

class TutorialState
{
protected:
	// ミッションクラス
	class TutorialUI* m_MissionUI;
	// ミッションのヒントクラス
	class TutorialUI* m_MissionHint;
	// チュートリアルシーンのクラス
	class Tutorial* m_Tutorial;
	// 順番番号
	int m_State;
	// ステート用時間
	float m_CurTime;
	// チュートリアル完了
	bool m_Finish;
	// 全部のボタンが押されたの確認
	bool m_PushButton[4];

public:
	TutorialState() {}
	~TutorialState() {}

	// チュートリアルシーンを取得
	void SetTutorial(class Tutorial* pTutorial) { m_Tutorial = pTutorial; }

	// チュートリアル完了のセッター
	void SetTutorialFinish() { m_Finish = true; }

	// 全部のボタンが押されたの確認
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

// 挨拶のステート
class TutorialState_Greeting : public TutorialState
{
public:
	void Update() override;
};

// ミッション１のステート
class TutorialState_Mission01 : public TutorialState
{
public:
	void Update() override;
};

// ミッション２のステート
class TutorialState_Mission02 : public TutorialState
{
public:
	void Update() override;
};

// ミッション３のステート
class TutorialState_Mission03 : public TutorialState
{
public:
	void Update() override;
};

// ミッション４のステート
class TutorialState_Mission04 : public TutorialState
{
public:
	void Update() override;
};

// ミッション５のステート
class TutorialState_Mission05 : public TutorialState
{
public:
	void Update() override;
};

// ミッション６のステート
class TutorialState_Mission06 : public TutorialState
{
public:
	void Update() override;
};

// ミッション全部クリアした状態
class TutorialState_TutorialFinish : public TutorialState
{
public:
	void Update() override;
};