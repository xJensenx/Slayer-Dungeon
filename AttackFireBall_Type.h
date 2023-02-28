#pragma once
class AttackFireBall_Type
{
protected:
	// ファイアボールのクラス
	class AttackFireBall* m_FireBall;
	// ターゲット
	class GameObject* m_TargetObj;
	// 進行中時間
	float m_CurTime;
	// 目的までの時間設置
	float m_TotalTime;
	// 初期座標
	D3DXVECTOR3 m_InitPos;


public:
	AttackFireBall_Type() {}
	~AttackFireBall_Type() {}

	// ファイアボールをセット
	void SetCharacter(class AttackFireBall* pFireBall) { m_FireBall = pFireBall; }
	// ターゲットを設置
	void SetTarget(class GameObject* Target) { m_TargetObj = Target; }
	
	// 初期化処理
	virtual void Init() = 0;
	// 更新処理
	virtual void Update() = 0;
	// ダメージ処理
	virtual void DamageEvent();
	// エフェクト処理
	virtual void EffectEvent();
};

class AttackFireBall_Type_ShootTowardsTarget : public AttackFireBall_Type
{
public:
	void Init() override;
	void Update() override;
};

class AttackFireBall_Type_HermiteShoot : public AttackFireBall_Type
{
public:
	void Init() override;
	void Update() override;
};

class AttackFireBall_Type_ChargeShoot : public AttackFireBall_Type
{
private:
	// 現在のステート（①ターゲットの周囲で移動している、②ちょっと後ろに下げて撃つ準備する、③ターゲットに撃ちます）
	int m_State;
	// 距離
	D3DXVECTOR3 m_Direction;
public:
	void Init() override;
	void Update() override;
};