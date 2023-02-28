#pragma once
class PlayerAnimationState
{
protected:
	// プレイヤークラス
	class Player* m_Character;
	// プレイヤーのアニメーションマネージャークラス
	class PlayerAnimation* m_AnimationTree;
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
	PlayerAnimationState() {}
	~PlayerAnimationState() {}

	// ボスを設置
	void SetCharacter(class Player* Char) { m_Character = Char; }
	// アニメーションマネージャーをセット
	void SetAnimationTree(class PlayerAnimation* Animation) { m_AnimationTree = Animation; }

	// フレームを取得
	float GetFrame() { return m_Frame; }
	// ループのゲッター
	bool GetLoop() { return m_Loop; }
	// プレイレートをゲット
	float GetPlayRate() { return m_PlayRate; }

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
class PlayerAnimation_Idle : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 走る状態
class PlayerAnimation_Run : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０１状態
class PlayerAnimation_Attack01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０２状態
class PlayerAnimation_Attack02 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０３状態
class PlayerAnimation_Attack03 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０４状態
class PlayerAnimation_Attack04 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃０５状態
class PlayerAnimation_Attack05 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ブロック状態
class PlayerAnimation_Block : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ブロック終わる状態
class PlayerAnimation_BlockFinish : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 防御成功した状態
class PlayerAnimation_BlockCounter : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 攻撃された状態
class PlayerAnimation_Hit : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ウルト０１の１段目状態
class PlayerAnimation_Ult01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// ウルト０１の２段目状態
class PlayerAnimation_Ult0102 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEの避ける１状態
class PlayerAnimation_QTEDodge01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEの避ける２状態
class PlayerAnimation_QTEDodge02 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// QTEの剣を投げる状態
class PlayerAnimation_QTEThrowSword : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 負けた状態
class PlayerAnimation_Dead : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 倒れる状態
class PlayerAnimation_KnockedDown : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 起きる状態
class PlayerAnimation_GetUp : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// 避ける状態
class PlayerAnimation_Dodge : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル１状態
class PlayerAnimation_Skill01 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル２状態
class PlayerAnimation_Skill02 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル３状態
class PlayerAnimation_Skill03 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル４状態
class PlayerAnimation_Skill04 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル５状態
class PlayerAnimation_Skill05 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル６状態
class PlayerAnimation_Skill06 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル７状態
class PlayerAnimation_Skill07 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル８状態
class PlayerAnimation_Skill08 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};

// スキル９状態
class PlayerAnimation_Skill09 : public PlayerAnimationState
{
public:
	void Init() override;
	void Update() override;
};