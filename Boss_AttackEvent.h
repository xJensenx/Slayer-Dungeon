#pragma once
class Boss_AttackEvent
{
protected:
	// ボス
	class Boss* m_Character;
	
	// ボックスキャストの置く座標
	D3DXVECTOR3 m_Origin;
	// ボックスキャストのサイズ
	D3DXVECTOR3 m_Size;
	// 丸キャストのサイズ
	float m_SphereSize;
	// Physicsキャスト変数
	class PhysicsCast* m_Phy;

public:
	Boss_AttackEvent() {}
	~Boss_AttackEvent() {}

	// ボスのセッター
	void SetCharacter(class Boss* Char) { m_Character = Char; }
	
	// ダメージのイベント
	virtual void DamageEvent() = 0;
};

class Boss_Attack_HeavyAtk : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};

class Boss_Attack_JumpAtk : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};

class Boss_Attack_JumpAtkSec : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};

class Boss_Attack_KnockBack : public Boss_AttackEvent
{
public:
	void DamageEvent() override;
};