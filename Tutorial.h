#pragma once
#include "Scene.h"
#include "TutorialState.h"

class Tutorial :
    public Scene
{
private:
	// 全部のチュートリアル完成したかどうか
	bool m_TutorialFinish = false;

	// チュートリアルのステート
	class TutorialState* m_TutorialState;

	// プレイヤー
	class Player* m_TutorialPlayer;
	// Minion
	class Minion* m_TutorialMinion;
	// ミッションUI
	class TutorialUI* m_MissionUI;

public:
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// チュートリアル完了をセット
	void SetTutorialFinish() { m_TutorialState->SetTutorialFinish(); }

	// ボタン押されたをセット
	void SetPushButton(int Num) { m_TutorialState->SetPushButton(Num); }

	// チュートリアル完了
	void SetFinish() { m_TutorialFinish = true; }

	// チュートリアルのステート変更
	template <typename T>
	void ChangeState()
	{
		// 既に存在している場合は削除
		if (m_TutorialState != NULL)
		{
			m_TutorialState->Uninit();
			delete m_TutorialState;
			m_TutorialState = NULL;
		}

		// 新しいステートを作る
		T* State = new T();
		State->SetTutorial(this);
		State->Init();

		// ステートを変数に入れる
		m_TutorialState = State;
	}

	// チュートリアルのステートをゲット
	template <typename T>
	bool GetTutorialState()
	{
		if (typeid(*m_TutorialState) == typeid(T))
		{
			return true;
		}
		
		return false;
	}

	// チュートリアル完成した状態を取得
	bool GetTutorialFinish() { return m_TutorialFinish; }

	// チュートリアルのプレイヤーを取得
	class Player* GetPlayer() { return m_TutorialPlayer; }

	// チュートリアルのMinionを取得
	class Minion* GetMinion() { return m_TutorialMinion; }
};

