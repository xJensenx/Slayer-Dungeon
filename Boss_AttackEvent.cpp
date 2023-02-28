#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "PhysicsCast.h"

#include "Boss_AttackEvent.h"
#include "MeshField.h"
#include "Boss.h"
#include "Player.h"
#include "Camera.h"

void Boss_Attack_HeavyAtk::DamageEvent()
{	
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// ボスの前に置く
	m_Origin = m_Character->GetPosition() + (m_Character->GetForward() * -2.5f);
	// Yを0にする
	m_Origin.y = 2.5f;
	// サイズを調整
	m_Size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	// ボックスキャスト
	m_Phy = PhysicsCast::PhysicBoxCast<Player>(m_Origin, m_Size);
	if (m_Phy != NULL)
	{
		// ダメージを与える
		m_Phy->GetColldeObj()->DealDamage(1.0f);
	}
}

void Boss_Attack_JumpAtk::DamageEvent()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// メッシュフィールドの高さ
	MeshField* _MF = _Scene->GetGameObject<MeshField>();
	float MeshHeight = _MF->GetHeight(m_Character->GetPosition());

	// ボスの前に置く
	m_Origin = m_Character->GetPosition();
	// Yを0にする
	m_Origin.y = MeshHeight;
	// サイズを調整
	m_SphereSize = 7.5f;

	// 攻撃のエフェクト
	m_Character->JumpAtkEffect();

	// 丸キャスト
	m_Phy = PhysicsCast::PhysicsSphereCast<Player>(m_Origin, m_SphereSize);

	if (m_Phy != NULL)
	{		
		// カメラシェーク
		_Scene->GetGameObject<Camera>()->ShakeCam(D3DXVECTOR3(0.025f, 0.025f, 0.0f), 0.7f);

		// 方向をゲット
		D3DXVECTOR3 DirOfTarget = m_Phy->GetColldeObj()->GetPosition() - m_Character->GetPosition();

		// 暴走している状態かどうか
		if (m_Character->GetBossPhase() == Boss::RagePhase)
		{
			// 暴走していると普通のダメージを与える（暴走のジャンプ攻撃は２段攻撃あるためノックバックしません）
			m_Phy->GetColldeObj()->DealDamage(2.0f);
		}
		else
		{
			// 暴走ではないとノックバックダメージを与える
			m_Phy->GetColldeObj()->KnockBackDamage(2.0f, DirOfTarget);
		}
	}
	

}

void Boss_Attack_JumpAtkSec::DamageEvent()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// メッシュフィールドの高さ
	MeshField* _MF = _Scene->GetGameObject<MeshField>();
	float MeshHeight = _MF->GetHeight(m_Character->GetPosition());

	// ボスの前に置く
	m_Origin = m_Character->GetPosition();
	// Yを0にする
	m_Origin.y = MeshHeight;
	// サイズを調整
	m_SphereSize = 7.5f;

	// 攻撃のエフェクト
	m_Character->JumpAtkEffect();

	// 丸キャスト
	m_Phy = PhysicsCast::PhysicsSphereCast<Player>(m_Origin, m_SphereSize);

	if (m_Phy != NULL)
	{
		// カメラシェーク
		_Scene->GetGameObject<Camera>()->ShakeCam(D3DXVECTOR3(0.025f, 0.025f, 0.0f), 0.7f);

		// 方向をゲット
		D3DXVECTOR3 DirOfTarget = m_Phy->GetColldeObj()->GetPosition() - m_Character->GetPosition();

		// ノックバックダメージを与える
		m_Phy->GetColldeObj()->KnockBackDamage(2.0f, DirOfTarget);
	}

}

void Boss_Attack_KnockBack::DamageEvent()
{	
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// ボスの前に置く
	m_Origin = m_Character->GetPosition() + (m_Character->GetForward() * -2.5f);
	// Yを0にする
	m_Origin.y = 2.5f;
	// サイズを調整
	m_Size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	// ボックスキャスト
	m_Phy = PhysicsCast::PhysicBoxCast<Player>(m_Origin, m_Size);

	// 攻撃のエフェクト
	m_Character->JumpAtkEffect();

	if (m_Phy != NULL)
	{
		// カメラシェーク
		_Scene->GetGameObject<Camera>()->ShakeCam(D3DXVECTOR3(0.025f, 0.025f, 0.0f), 0.7f);

		// 方向をゲット
		D3DXVECTOR3 DirOfTarget = m_Phy->GetColldeObj()->GetPosition() - m_Character->GetPosition();

		// ノックバックダメージを与える
		m_Phy->GetColldeObj()->KnockBackDamage(2.0f, DirOfTarget);
	}
}
