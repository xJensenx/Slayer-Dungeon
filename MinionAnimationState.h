#pragma once
class MinionAnimationState
{
protected:
	// Minionのクラス
	class Minion* m_Character;

	// Minionのアニメーションマネージャー
	class MinionAnimation* m_AnimationTree;
	// 通知用
	std::unordered_map<std::string, float> m_Notify;
	// 通知用bool
	std::unordered_map<std::string, bool> m_NotifyDone;

	// フレーム数
	float m_Frame;
	// アニメーションの長さ
	float m_Duration;
	// ループ
	bool m_Loop;
	// プレイレート
	float m_PlayRate;

public:
	MinionAnimationState() {}
	~MinionAnimationState() {}

	// Minionを設置
	void SetCharacter(class Minion* _Minion) { m_Character = _Minion; }
	// アニメーションマネージャーをセット
	void SetAnimationTree(class MinionAnimation* _Animation) { m_AnimationTree = _Animation; }

	// フレームを取得
	float GetFrame() { return m_Frame; }
	// プレイレート取得
	float GetPlayRate() { return m_PlayRate; }
	// ループ取得
	bool GetLoop() { return m_Loop; }

	// 初期化処理
	virtual void Init() = 0;
	// 更新処理
	virtual void Update() = 0;
};

// 待機状態
class MinionAnimationState_Idle : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 走る状態
class MinionAnimationState_Run : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０１状態
class MinionAnimationState_Attack01 : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０２状態
class MinionAnimationState_Attack02 : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ダメージ受けた状態
class MinionAnimationState_Hit : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// カットシーン状態
class MinionAnimationState_Show : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 倒された状態
class MinionAnimationState_Dead : public MinionAnimationState
{
public:
	void Init() override;
	void Update() override;
};
