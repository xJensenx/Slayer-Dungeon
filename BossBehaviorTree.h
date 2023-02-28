#pragma once
class BossBehaviorTree
{
protected:
	// ボスクラス
	class Boss* m_Character;
	// ボスのアニメーションマネージャー
	class BossAnimation* m_AnimationTree;
public:
	BossBehaviorTree() {}
	~BossBehaviorTree() {}

	// キャラクターをセット
	void SetCharacter(Boss* Character) { m_Character = Character; }
	// アニメーションマネージャーをセット
	void SetAnimationTree(BossAnimation* Animation) { m_AnimationTree = Animation; }

	// 初期化
	virtual void Init() = 0;
	// 更新処理
	virtual void Update() = 0;
};

// 待機状態
class BossIdle : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 追う状態
class BossChase : public BossBehaviorTree
{
private:

public:
	void Init() override;
	void Update() override;
};

// 攻撃状態
class BossAttack : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// ジャンプ攻撃
class BossJumpAtk : public BossBehaviorTree
{
private:
	// ジャンプしているかどうか
	bool m_isJump;
	// ジャンプ攻撃したかどうか
	bool m_JumpAtk;
	// 攻撃の警告
	class Boss_AttackWarning* m_WarningEffect;

public:
	void Init() override;
	void Update() override;
};

// ジャンプ攻撃２段目
class BossJumpAtkSec : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 暴走攻撃
class BossRageAtk : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 倒されている状態
class BossDead : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// カットシーン状態
class BossShow : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 叫ぶ状態
class BossRoar : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// QTE状態
class BossQTE : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 隕石を召喚状態
class BossSummonMeteor : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// ファイアボールを召喚する状態
class BossShootFireBall : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// 暴走して隕石を召喚する状態
class BossRageSummonMeteor : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

// プレイヤーの周りにファイアボールを召喚する状態
class BossShootRotateFireBall : public BossBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};