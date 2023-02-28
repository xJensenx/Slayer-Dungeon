#pragma once
class BossAnimationState
{
protected:
	// ボスクラス
	class Boss* m_Character;
	// ボスのアニメーションマネージャークラス
	class BossAnimation* m_AnimationTree;
	// 通知用
	std::unordered_map<std::string, float> m_Notify;
	// 通知用bool
	std::unordered_map<std::string, bool> m_NotifyDone;
	// フレーム数
	float m_Frame;
	// プレイレート
	float m_PlayRate;
	// アニメーションの長さ
	float m_Duration;
	// ループしているかどうか
	bool m_Loop;


public:
	BossAnimationState() {}
	~BossAnimationState() {}

	// ボスを設置
	void SetCharacter(class Boss* Char) { m_Character = Char; }
	// アニメーションマネージャーをセット
	void SetAnimationTree(class BossAnimation* Animation) { m_AnimationTree = Animation; }

	// フレームを取得
	float GetFrame() { return m_Frame; }
	// ループのゲッター
	bool GetLoop() { return m_Loop; }

	// 初期化処理
	virtual void Init() = 0;
	// 更新処理
	virtual void Update() = 0;
	// 終了処理
	virtual void Uninit()
	{
		// メモリ解放
		m_Notify.clear();
		m_NotifyDone.clear();
	}
};

// 待機状態
class BossAnimation_Idle : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 走る状態
class BossAnimation_Run : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// Roar状態
class BossAnimation_Roar : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ジャンプ状態
class BossAnimation_Jump : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// HeavyPunch状態
class BossAnimation_HeavyPunch : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 隕石を召喚状態
class BossAnimation_SummonMeteor : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// JumpAtk状態
class BossAnimation_JumpAtk : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// JumpAtkSec状態
class BossAnimation_JumpAtkSec : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// Dead状態
class BossAnimation_Dead : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTERoar状態
class BossAnimation_QTERoar : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEAfterRoar状態
class BossAnimation_QTEAfterRoar : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEInjured状態
class BossAnimation_QTEInjured : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// RageAtk01状態
class BossAnimation_RageAtk01 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ShootFireBall01状態
class BossAnimation_ShootFireBall01 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ShootFireBall02状態
class BossAnimation_ShootFireBall02 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ShootFireBall03状態
class BossAnimation_ShootFireBall03 : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 暴走状態の隕石召喚状態
class BossAnimation_RageSummonMeteor : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// プレイヤーの周りに回っているファイアボールを召喚状態
class BossAnimation_SummonRotateFireBall : public BossAnimationState
{
public:
	void Init() override;
	void Update() override;
};