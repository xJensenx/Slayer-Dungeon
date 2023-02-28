#pragma once
#include <unordered_map>
#include "AnimModelManager.h"

class AnimationManager
{
protected:
	// タイミングの期間
	struct Timing
	{
		float StartTime = -1;
		float EndTime = -1;
	};
	// 所属しているゲームオブジェクト
	class GameObject* m_GameObject = nullptr;
	// 所属しているゲームオブジェクトのアニメーションモデル
	class AnimModelManager* m_AnimModel = nullptr;
	// 現在のアニメーションの名前
	const char* m_CurAnimationName;
	// 前のアニメーションの名前
	const char* m_PrevAnimationName;
	// 現在のステート
	int m_State = 0;
	// 前回のステート
	int m_PreviousState = 0;
	//// 現在のステート
	//class StateMachine* m_State = 0;
	//// 前回のステート
	//class StateMachine* m_PreviousState = 0;
	// ブレンドレート
	float m_BlendRate = 0.0f;
	// 現在のアニメーションのフレーム
	float m_CurFrame = 0.0f;
	// 前のアニメーションのフレーム
	float m_PrevFrame = 0.0f;
	// 現在のアニメーションループさせるか
	bool m_CurLoop = true;
	// 前回のアニメーションループさせるか
	bool m_PrevLoop = true;
	// 前のフレームの更新速度
	float m_PrevPlayRate;
	// アニメーションの長さ
	float m_Duration;
	// 前のアニメーションが完了したか（ループではない時に使う）
	bool m_isPrevAniFinish;
	// 通知を送るタイミング
	std::unordered_map<std::string, Timing> m_Timing;
	// ぴったりそのタイミングに通知を送るため
	std::unordered_map<std::string, float> m_Notify;
	// 通知イベントやりましたか
	std::unordered_map<std::string, bool> m_NotifyDone;
	// PlayRate（アニメーションの速度）
	std::unordered_map<std::string, float> m_PlayRate;

public:
	AnimationManager() {}
	virtual ~AnimationManager() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void TimingManager() {}

	//template <typename T>
	//T* ChangeState()
	//{
	//	if (m_State != NULL) m_PreviousState = m_State;

	//	T* State = new T();
	//	State->SetCharacter(m_GameObject);
	//	State->SetAnimationManager(this);
	//	m_State = State;
	//	if (m_PreviousState == NULL) m_PreviousState = State;
	//}

	// 現在のステートの情報取得
	int GetState() { return m_State; }
	// 前回のステートの情報取得
	int GetPreviousState() { return m_PreviousState; }
	// 前のアニメーションが完了したかの変数のゲッター
	bool GetPrevAniStatus() { return m_isPrevAniFinish; }
	// 現在の長さを取得
	float GetDuration() { return m_AnimModel->GetAnimDuration(m_CurAnimationName); }

	// 現在のAnimation名前やループの設置
	void SetAnimationName(const char* Name)
	{
		m_CurAnimationName = Name;
	}

	// 所属するゲームオブジェクトを設置する
	void SetGameObject(GameObject* _Parent)
	{
		m_GameObject = _Parent;
	}
	// 所属するアニメーションモデルを設置する
	void SetAnimModel(AnimModelManager* _AnimModelManager)
	{
		m_AnimModel = _AnimModelManager;
	}
	// 前のアニメーションが終了したの設置
	void SetPrevAniFinish(bool Finish) { m_isPrevAniFinish = Finish; }

	// 現在のフレームを取得
	float GetCurFrame() { return m_CurFrame; }
};