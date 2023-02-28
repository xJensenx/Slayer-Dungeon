#include "main.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "AttackFireBall.h"
#include "AttackFireBall_Type.h"
#include "PhysicsCast.h"
#include "Player.h"
#include "Camera.h"
#include "Effect.h"

void AttackFireBall_Type_ShootTowardsTarget::Init()
{
	// 進行中時間初期化
	m_CurTime = 0.0f;
	// 目標までの時間
	m_TotalTime = 1.0f * Manager::Time;
	// 初期座標
	m_InitPos = m_FireBall->GetPosition();
}

void AttackFireBall_Type_ShootTowardsTarget::Update()
{
	// 目標
	if (m_TargetObj == NULL) return;

	if (m_CurTime < m_TotalTime)
	{
		m_CurTime++;
		float T = m_CurTime / m_TotalTime;

		// 線形補間用座標
		D3DXVECTOR3 LerpPos;
		D3DXVECTOR3 TargetPos = m_TargetObj->GetPosition();
		
		// 線形補間
		D3DXVec3Lerp(&LerpPos, &m_InitPos, &TargetPos, T);

		// 座標設置
		m_FireBall->SetPosition(LerpPos);

		// ダメージ処理
		DamageEvent();
	}
	else
	{
		// 目的地に到達したら破壊する
		m_FireBall->SetDestroy();
		return;
	}
}

void AttackFireBall_Type_HermiteShoot::Init()
{
	// 進行中時間初期化
	m_CurTime = 0.0f;
	// 目標までの時間
	m_TotalTime = 0.75f * Manager::Time;
	// 初期座標
	m_InitPos = m_FireBall->GetPosition();

}

void AttackFireBall_Type_HermiteShoot::Update()
{
	// ターゲットが存在しないとreturnします
	if (m_TargetObj == NULL) return;

	if (m_CurTime < m_TotalTime)
	{
		m_CurTime++;
		float T = m_CurTime / m_TotalTime;

		// エルミート用
		D3DXVECTOR3 HermitePos;

		// Tan1
		D3DXVECTOR3 ShootTan = m_FireBall->GetHermiteTan();

		// Tan2
		D3DXVECTOR3 TargetTan = m_TargetObj->GetForward();

		// ターゲットの目標
		D3DXVECTOR3 TargetPos = m_TargetObj->GetPosition();

		// エルミート
		D3DXVec3Hermite(&HermitePos, &m_InitPos, &ShootTan, &TargetPos, &TargetTan, T);

		m_FireBall->SetPosition(HermitePos);

		DamageEvent();
	}
	else
	{
		// 目的地に到達したら破壊する
		m_FireBall->SetDestroy();
		return;
	}
}

void AttackFireBall_Type::DamageEvent()
{
	// 自分のポジション
	D3DXVECTOR3 _Pos = m_FireBall->GetPosition();

	// サイズ取得
	float _Size = m_FireBall->GetScale().x - 0.1f;

	// PhysicsCast処理
	PhysicsCast* _Phy = PhysicsCast::PhysicsSphereCast<Player>(_Pos, _Size);

	// プレイヤーに当たらないとreturnする
	if (_Phy == NULL) return;

	// ダメージを与える
	_Phy->GetColldeObj()->DealDamage(1.0f);
	// カメラ取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// カメラ揺れる
	_Camera->ShakeCam(D3DXVECTOR3(0.01f, 0.01f, 0.0f), 0.5f);
	EffectEvent();

	m_FireBall->SetDestroy();
	return;
	
}

void AttackFireBall_Type::EffectEvent()
{
	// エフェクト処理
	Scene* _Scene = Manager::GetScene();
	Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);

	_Effect->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	// 種類設置
	_Effect->SetEffectType<EffectType_BossMeteor>();
	_Effect->SetPosition(m_FireBall->GetPosition());
}

void AttackFireBall_Type_ChargeShoot::Init()
{
	// 進行中時間初期化
	m_CurTime = 0.0f;
	// 目標までの時間
	m_TotalTime = 1.0f * Manager::Time;
	// 初期座標
	m_InitPos = m_FireBall->GetPosition();
	// ステートの初期化
	m_State = 0;
	// 距離の初期化
	m_Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void AttackFireBall_Type_ChargeShoot::Update()
{
	// ターゲットが存在しないとreturnします
	if (m_TargetObj == NULL) return;

	switch (m_State)
	{
	case 0:
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;
			
			// 角度増加
			float Angle = m_FireBall->GetInitAngle();
			Angle += 0.1f;
			m_FireBall->SetInitAngle(Angle);
			
			// 距離設置
			float Dist = 2.0f;

			// 座標計算
			D3DXVECTOR3 NextPos = m_TargetObj->GetPosition();
			NextPos.x += cosf(Angle) * Dist;
			NextPos.z += sinf(Angle) * Dist;
			NextPos.y += 1.5f;

			// 座標設置
			m_FireBall->SetPosition(NextPos);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 合計時間更新
			m_TotalTime = 0.5f * Manager::Time;

			// 次のステートに進む
			m_State = 1;

			// 距離計算
			m_Direction = m_FireBall->GetPosition() - m_TargetObj->GetPosition();
			m_Direction.y = 0.0f;
			D3DXVec3Normalize(&m_Direction, &m_Direction);

			m_Direction = m_FireBall->GetPosition() + (m_Direction * 2.0f);

			// 初期座標設置
			m_InitPos = m_FireBall->GetPosition();
		}
		break;
	case 1:
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;

			float T = m_CurTime / m_TotalTime;

			// 線形補間用
			D3DXVECTOR3 LerpPos;

			// 線形補間
			D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_Direction, T);

			// 座標設置
			m_FireBall->SetPosition(LerpPos);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 合計時間更新
			m_TotalTime = 0.5f * Manager::Time;

			// 初期座標更新
			m_InitPos = m_FireBall->GetPosition();

			// 目標座標設置
			m_Direction = m_TargetObj->GetPosition();
			m_Direction.y += 1.5f;

			// ステート更新
			m_State = 2;
		}
		break;
	case 2:
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;
			float T = m_CurTime / m_TotalTime;

			// 線形補間用
			D3DXVECTOR3 LerpPos;

			// 線形補間
			D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_Direction, T);

			// 座標設置
			m_FireBall->SetPosition(LerpPos);

			// ダメージ処理
			DamageEvent();
		}
		else
		{
			// ダメージ処理
			DamageEvent();

			// エフェクト出す
			EffectEvent();

			// 自分を破壊する
			m_FireBall->SetDestroy();
			return;
		}
		break;

	}
}
