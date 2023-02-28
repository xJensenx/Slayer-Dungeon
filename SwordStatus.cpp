#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "Sword.h"
#include "SwordStatus.h"
#include "Player.h"
#include "Math.h"
#include "PhysicsCast.h"
#include "Minion.h"
#include "Boss.h"
#include "Camera.h"
#include "MeshField.h"

void SwordIdle::Init()
{
	// キャラクターを取得
	m_Character = m_Sword->GetCharacter();

	// 初期座標を設置
	m_InitPos = m_Sword->GetPosition();
	// 時間を初期化
	m_CurShootTime = 0.0f;
}

void SwordIdle::Update()
{
	// キャラクターがNULLだったらreturn
	if (m_Character == NULL) return;

	// 時間経過中だと剣を置く場所まで移動させる
	if (m_CurShootTime < m_TotalIdleTime)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / m_TotalIdleTime;

		// プレイヤーの座標やRight
		D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
		PlayerPos.y += 1.0f;
		D3DXVECTOR3 PlayerRight = m_Character->GetRight();
		D3DXVECTOR3 PlayerRot = m_Character->GetRotation();
		// 置く場所の変数
		D3DXVECTOR3 PlacePos;
		// プレイヤーとどのぐらい離れるか
		float DistanceBetween = 0.75f;
		// 変数用意
		D3DXVECTOR2 PlaceValue;
		float Angle = 0.0f;
		float ValueXZ = 0.0f;
		float ValueY = 0.0f;

		// Lerp用変数
		D3DXVECTOR3 LerpPos;	

		// 剣の置いてる位置
		Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

		// 置いてる場所によってプレイヤーの指定した座標に置く
		switch (m_SwordPos)
		{
		case Sword::SwordPosition::First:
			PlaceValue = D3DXVECTOR2(0.5f, 0.3f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Second:
			PlaceValue = D3DXVECTOR2(0.3f, 0.5f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Third:
			PlaceValue = D3DXVECTOR2(0.0f, 0.5f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Fourth:
			PlaceValue = D3DXVECTOR2(-0.3f, 0.5f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Fifth:
			PlaceValue = D3DXVECTOR2(-0.5f, 0.3f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		}


		// 剣の座標を計算して置きます
		ValueXZ = DistanceBetween * cosf(Angle);
		PlayerRight *= ValueXZ;
		ValueY = DistanceBetween * sinf(Angle);

		PlacePos.x = PlayerPos.x + PlayerRight.x;
		PlacePos.y = PlayerPos.y + ValueY;
		PlacePos.z = PlayerPos.z + PlayerRight.z;

		// ポジションのLerp
		D3DXVec3Lerp(&LerpPos, &m_InitPos, &PlacePos, T);
		m_Sword->SetPosition(LerpPos);
	}
	else
	{
		// 座標更新
		{
			// プレイヤーの座標やRight
			D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
			PlayerPos.y += 1.0f;
			D3DXVECTOR3 PlayerRight = m_Character->GetRight();
			D3DXVECTOR3 PlayerRot = m_Character->GetRotation();
			// 置く場所の変数
			D3DXVECTOR3 PlacePos;
			// プレイヤーとどのぐらい離れるか
			float DistanceBetween = 0.75f;
			// 変数用意
			D3DXVECTOR2 PlaceValue;
			float Angle = 0.0f;
			float ValueXZ = 0.0f;
			float ValueY = 0.0f;
			D3DXVECTOR3 RotationValue;

			Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

			// 置いてる場所によってプレイヤーの指定した座標に置く
			switch (m_SwordPos)
			{
			case Sword::SwordPosition::First:
				PlaceValue = D3DXVECTOR2(0.5f, 0.3f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);



				break;
			case Sword::SwordPosition::Second:
				PlaceValue = D3DXVECTOR2(0.3f, 0.5f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

				break;
			case Sword::SwordPosition::Third:
				PlaceValue = D3DXVECTOR2(0.0f, 0.5f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
				break;
			case Sword::SwordPosition::Fourth:
				PlaceValue = D3DXVECTOR2(-0.3f, 0.5f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

				break;
			case Sword::SwordPosition::Fifth:
				PlaceValue = D3DXVECTOR2(-0.5f, 0.3f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
				break;
			}

			switch (m_IdleState)
			{
			case 0:
				m_IdleAnimTime += 1.0f / Manager::Time;
				if (m_IdleAnimTime >= 1.0f)
				{
					m_IdleState = 1;
				}
				break;
			case 1:
				m_IdleAnimTime -= 1.0f / Manager::Time;
				if (m_IdleAnimTime <= 0.0f)
				{
					m_IdleState = 0;
				}
				break;
			}

			// 浮いている感じを表します
			float MoveAmt = Math::FloatLerp(0.0f, 0.2f, m_IdleAnimTime);

			// ソードのUpを取得（Quaternionを使っているのでQuaternion用のUpで計算しています）
			D3DXVECTOR3 Up = m_Sword->GetQuaternionUp() * MoveAmt;

			// 座標計算
			ValueXZ = DistanceBetween * cosf(Angle);
			PlayerRight *= ValueXZ;
			ValueY = DistanceBetween * sinf(Angle);

			PlacePos.x = PlayerPos.x + PlayerRight.x;
			PlacePos.y = PlayerPos.y + ValueY;
			PlacePos.z = PlayerPos.z + PlayerRight.z;

			// 回転
			D3DXQUATERNION Q = Math::QuaternionLookAt(PlacePos, m_Character->GetPosition());
			m_Sword->SetQuaternion(Q);

			PlacePos.y += Up.y;
			PlacePos.x += Up.x;

			m_Sword->SetPosition(PlacePos);
		}
	}

}

void SwordShoot::Init()
{
	// キャラクターを取得
	m_Character = m_Sword->GetCharacter();

	// 目標が存在しないと前に撃ちます
	if (m_Sword->GetTargetObj() == NULL)
	{
		m_TargetPos = m_Sword->GetTargetPos();
	}
	else
	{
		// 存在すると目標まで撃ちます
		m_TargetObj = m_Sword->GetTargetObj();
	}
	// 初期化
	m_CurShootTime = 0.0f;
	m_InitPos = m_Sword->GetPosition();
	m_InitUp = m_Sword->GetQuaternionUp();
}

void SwordShoot::Update()
{
	// カメラ取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// 打ってる時間が制限時間内に目標と当たらないと消える
	if (m_CurShootTime < m_TotalShootTime)
	{
		// 時間増加
		m_CurShootTime++;
		// 1.0以内の長さを取る
		float T = m_CurShootTime / m_TotalShootTime;

		// エルミート曲線に代入する変数
		D3DXVECTOR3 HermitePos;
		// 初期座標
		D3DXVECTOR3 InitPos = m_InitPos;
		// 目的座標
		D3DXVECTOR3 TargetPos;
		if (m_TargetObj != NULL)
		{
			TargetPos = m_TargetObj->GetPosition();

			TargetPos.y += 1.5f;
		}
		else
		{
			TargetPos = m_TargetPos;
		}
		// Tangent1
		D3DXVECTOR3 Tangent1;
		// Tangent2
		D3DXVECTOR3 Tangent2;

		// Tangentの値取得
		Tangent1 = m_InitUp * 25.0f;
		Tangent2 = -Tangent1;

		// エルミート曲線計算
		D3DXVec3Hermite(&HermitePos, &InitPos, &Tangent1, &TargetPos, &Tangent2, T);

		// 回転処理
		// 方向を計算します
		D3DXVECTOR3 Dir = HermitePos - m_Sword->GetPosition();
		//D3DXVec3Normalize(&Dir, &Dir);

		D3DXQUATERNION Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// ポジションを更新する
		m_Sword->SetPosition(HermitePos);

		// エフェクト
		m_Sword->TrailEffect();
	}
	else
	{
		// ボックスキャスト用変数
		std::vector<PhysicsCast*> _Phy;
		PhysicsCast* _PhyBoss;

		// ボックスキャスト
		_Phy = PhysicsCast::AllPhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
		// 当たっているとエフェクトを出して破壊する
		for (auto P : _Phy)
		{
			P->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		}
		// ボックスキャスト
		_PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
		// 当たっているとエフェクトを出して破壊する
		if (_PhyBoss != NULL)
		{
			_PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		}
		m_Sword->HitEffect(m_Sword->GetPosition());
		// カメラシェークデバッグ
		if (_Camera != NULL)
		{
			_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
		}
		// オブジェクトを消します
		m_Sword->SetDestroy();
		return;
	}


}

void SwordAttack::Init()
{
	// キャラクターを取得
	m_Character = m_Sword->GetCharacter();

	// 初期化
	m_Damaged = false;
	m_InitPos = m_Sword->GetPosition();
	m_InitUp = m_Sword->GetInitUp();
	m_EndPos = m_Sword->GetEndPos();
	m_EndTan = m_Sword->GetEndTan();
	m_CurShootTime = 0.0f;
	m_TotalAttackTime = m_Sword->GetTotalAtkTime();
}

void SwordAttack::Update()
{
	if (m_Character == NULL) return;

	// 攻撃
	if (m_CurShootTime < m_TotalAttackTime)
	{
		// 時間増加
		m_CurShootTime++;
		// 1.0以内の長さを取る
		float T = m_CurShootTime / m_TotalAttackTime;

		// エルミート曲線に代入する変数
		D3DXVECTOR3 HermitePos;
		// 初期座標
		D3DXVECTOR3 InitPos = m_InitPos;
		// 目的座標
		D3DXVECTOR3 TargetPos = m_EndPos;
		// Tangent1
		D3DXVECTOR3 Tangent1 = m_InitUp;
		// Tangent2
		D3DXVECTOR3 Tangent2 = m_EndTan;

		// エルミート曲線計算
		D3DXVec3Hermite(&HermitePos, &InitPos, &Tangent1, &TargetPos, &Tangent2, T);

		// 回転処理
		// 方向を計算します
		D3DXVECTOR3 Dir = HermitePos - m_Sword->GetPosition();
		//D3DXVec3Normalize(&Dir, &Dir);

		D3DXQUATERNION Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// ポジションを更新する
		m_Sword->SetPosition(HermitePos);

		// トレールエフェクト
		m_Sword->TrailEffect();

		// ダメージしたかどうか
		if (!m_Damaged)
		{
			// ボックスキャスト用変数
			PhysicsCast* PhyBoss;
			PhysicsCast* PhyMinion;

			// Minionのボックスキャスト
			PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition() , D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyMinion != NULL)
			{
				Manager::PauseFor(0.1f);

				m_Character->AddMp(5.0f);
				PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
			// Bossのボックスキャスト
			PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyBoss != NULL)
			{
				Manager::PauseFor(0.1f);

				m_Character->AddMp(5.0f);
				PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
		}
	}
	else
	{
		// 剣の軌跡を初期化
		m_Sword->InitSwordTrail();
		// 目的地まで行ったので消します
		m_Sword->SetDestroy();
		return;
	}

}

void SwordBlock::Init()
{
	// キャラクターを取得
	m_Character = m_Sword->GetCharacter();
	// 初期化
	m_InitQua = m_Sword->GetQuaternion();
	m_InitPos = m_Sword->GetPosition();
	m_CurShootTime = 0.0f;
}

void SwordBlock::Update()
{
	// キャラクターがNULLだとreturn
	if (m_Character == NULL) return;

	// 防御
	if (m_CurShootTime < m_TotalBlockTime)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / m_TotalBlockTime;
		// Lerp用変数
		D3DXVECTOR3 LerpPos;
		// プレイヤーの座標
		D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
		// プレイヤーのForward
		D3DXVECTOR3 PlayerFor = -m_Character->GetForward();
		// プレイヤーのRight
		D3DXVECTOR3 PlayerRig = -m_Character->GetRight();
		// 次の座標
		D3DXVECTOR3 NextPos;
		// 線形補間用
		D3DXQUATERNION LerpQua;
		// 次のQuaternion
		D3DXQUATERNION NextQua;
		// Quaternionの初期化
		D3DXQuaternionIdentity(&NextQua);

		// 剣の置く位置を取得
		Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

		// 置く位置によって次の座標を更新します
		switch (m_SwordPos)
		{
		case Sword::SwordPosition::First:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos -= (PlayerRig * 0.5f);
			NextPos.y += 0.8f;
			break;
		case Sword::SwordPosition::Second:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos -= (PlayerRig * 0.25f);
			NextPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Third:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos.y += 1.0f;
			break;
		case Sword::SwordPosition::Fourth:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos += (PlayerRig * 0.25f);
			NextPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Fifth:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos += (PlayerRig * 0.5f);
			NextPos.y += 0.8f;
			break;
		}

		// 線形補間
		D3DXVec3Lerp(&LerpPos, &m_InitPos, &NextPos, T);
		// 座標設置
		m_Sword->SetPosition(LerpPos);
		// QuaternionのSlerp（線形補間）
		D3DXQuaternionSlerp(&LerpQua, &m_InitQua, &NextQua, T);
		
	}
	else
	{
		// 線形補間用座標
		D3DXVECTOR3 LerpPos;
		// プレイヤーの座標
		D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
		// プレイヤーのForward
		D3DXVECTOR3 PlayerFor = -m_Character->GetForward();
		// プレイヤーのRight
		D3DXVECTOR3 PlayerRig = -m_Character->GetRight();

		// ソードの位置
		Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

		// ソードの位置によって座標変更します
		switch (m_SwordPos)
		{
		case Sword::SwordPosition::First:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos -= (PlayerRig * 0.5f);
			LerpPos.y += 0.8f;
			break;
		case Sword::SwordPosition::Second:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos -= (PlayerRig * 0.25f);
			LerpPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Third:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos.y += 1.0f;
			break;
		case Sword::SwordPosition::Fourth:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos += (PlayerRig * 0.25f);
			LerpPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Fifth:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos += (PlayerRig * 0.5f);
			LerpPos.y += 0.8f;
			break;
		}

		// 座標設置
		m_Sword->SetPosition(LerpPos);
	}

}

void SwordUlt::Init()
{
	m_Character = m_Sword->GetCharacter();

	m_isShake = false;
	m_ShakeStr = m_Sword->GetShakeStr();
	m_CurShootTime = 0.0f;
}

void SwordUlt::Update()
{
	Scene* _Scene = Manager::GetScene();
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// 落下速度
	D3DXVECTOR3 NextPos = D3DXVECTOR3(m_Sword->GetPosition().x, m_Sword->GetPosition().y - 0.6f, m_Sword->GetPosition().z);

	D3DXQUATERNION Q;
	D3DXVECTOR3 Axis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXQuaternionRotationAxis(&Q, &Axis, Math::PI());
	m_Sword->SetQuaternion(Q);

	m_Sword->SetPosition(NextPos);
	
	D3DXVECTOR3 _Position = m_Sword->GetPosition();
	D3DXVECTOR3 _Scale = m_Sword->GetScale();

	if (_MeshField != NULL)
	{
		if (_Position.y <= _MeshField->GetHeight(_Position) + (_Scale.y * 1.5f))
		{
			m_Sword->SetPosition(D3DXVECTOR3(m_Sword->GetPosition().x, _MeshField->GetHeight(_Position) + (_Scale.y * 1.5f), m_Sword->GetPosition().z));
			// エフェクト
			m_Sword->TrailEffect();

			if (!m_isShake)
			{
				_Camera->ShakeCam(D3DXVECTOR3(m_ShakeStr, m_ShakeStr, 0.0f), 0.33f);
				m_isShake = true;
			}

			m_CurShootTime++;

			// ダメージしたかどうか
			if (!m_Damaged)
			{
				// ボックスキャスト用変数
				PhysicsCast* PhyBoss;
				PhysicsCast* PhyMinion;

				// Minionのボックスキャスト
				PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(_Position, D3DXVECTOR3(5.0f, 5.0f, 5.0f));
				if (PhyMinion != NULL)
				{
					PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
					D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
					EffectPos.y += 1.0f;
					m_Sword->HitEffect(EffectPos);
					m_Damaged = true;
				}
				// Bossのボックスキャスト
				PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(_Position, D3DXVECTOR3(5.0f, 5.0f, 5.0f));
				if (PhyBoss != NULL)
				{
					PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
					D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
					EffectPos.y += 1.0f;
					m_Sword->HitEffect(EffectPos);
					m_Damaged = true;
				}
			}

			if (m_CurShootTime >= m_TotalShootTime)
			{
				// 剣の軌跡を初期化
				m_Sword->InitSwordTrail();

				m_Sword->DissolveEffect();
				m_Sword->SetDestroy();
				return;
			}
		}
	}

}

void SwordQTE::Init()
{
	m_Character = m_Sword->GetCharacter();

	m_InitPos = m_Sword->GetPosition();
	m_EndPos = m_Sword->GetEndPos();
	m_CurShootTime = 0.0f;
}

void SwordQTE::Update()
{
	// QTE用
	if (m_CurShootTime < 3.0f * Manager::Time)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / (3.0f * Manager::Time);

		// 線形補間用変数
		D3DXVECTOR3 LerpPos;

		D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_EndPos, T);

		D3DXQUATERNION Q = Math::QuaternionLookAt(LerpPos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		m_Sword->SetPosition(LerpPos);

		if (m_CurShootTime >= 2.8f * Manager::Time)
		{
			m_Sword->HitEffect(m_Sword->GetPosition());
			m_Sword->SetDestroy();
			return;
		}
	}
	else
	{
		m_Sword->HitEffect(m_Sword->GetPosition());
		m_Sword->SetDestroy();
		return;
	}

}

void SwordShootStraight::Init()
{
	m_CurShootTime = 0.0f;
	m_InitPos = m_Sword->GetPosition();
	m_TargetPos = m_Sword->GetTargetPos();
	
}

void SwordShootStraight::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	if (m_CurShootTime < m_TotalShootTime)
	{
		m_CurShootTime++;

		float T = m_CurShootTime / m_TotalShootTime;

		// 初期座標
		D3DXVECTOR3 InitPos = m_InitPos;
		// 目的座標
		D3DXVECTOR3 TarPos = m_TargetPos;
		// Lerp用
		D3DXVECTOR3 LerpPos;

		// 線形補間
		D3DXVec3Lerp(&LerpPos, &InitPos, &TarPos, T);

		D3DXQUATERNION Q = Math::QuaternionLookAt(LerpPos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);
		// 座標更新
		m_Sword->SetPosition(LerpPos);
		// エフェクト
		m_Sword->TrailEffect();

		// ダメージ処理
		PhysicsCast* _Boss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Boss != NULL)
		{
			// カメラシェークデバッグ
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}

			_Boss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
			m_Sword->SetDestroy();
			return;
		}
		// ダメージ処理
		PhysicsCast* _Minion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Minion != NULL)
		{
			// カメラシェークデバッグ
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}

			_Minion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
			m_Sword->SetDestroy();
			return;
		}

	}
	else
	{
		// ダメージ処理
		PhysicsCast* _Boss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Boss != NULL)
		{
			// カメラシェークデバッグ
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}


			_Boss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
		}
		// ダメージ処理
		PhysicsCast* _Minion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Minion != NULL)
		{
			// カメラシェークデバッグ
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}


			_Minion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
		}

		// 剣の軌跡を初期化
		m_Sword->InitSwordTrail();

		m_Sword->SetDestroy();
		return;
	}
}

void SwordChargeShoot::Init()
{
	// キャラクター取得
	m_Character = m_Sword->GetCharacter();

	// Charge時向かってる方向
	m_TargetPos = m_Character->GetPosition();
	m_TargetPos.y += 2.0f;
	// 初期座標
	switch (m_Sword->GetSwordPos())
	{
	case Sword::First:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.5f + m_Character->GetRight() * 3.0f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Second:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.75f + m_Character->GetRight() * 1.5f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Third:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 2.0f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Fourth:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.75f - m_Character->GetRight() * 1.5f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Fifth:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.5f - m_Character->GetRight() * 3.0f;
		m_InitPos.y += 2.0f;
		break;
	}

	m_Direction = m_InitPos - m_TargetPos;

	// チャージ時間初期化
	m_ChargeTime = 0.0f;
	// 撃つ時間初期化
	m_CurShootTime = 0.0f;
	// チャージステート
	m_ChargeState = 0;
}

void SwordChargeShoot::Update()
{
	switch (m_ChargeState)
	{
	case 0:
		if (m_ChargeTime < m_FullChargeTime)
		{
			m_ChargeTime++;
			float T = m_ChargeTime / m_FullChargeTime;
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_TargetPos, T);

			D3DXQUATERNION Q = Math::QuaternionLookAt(m_InitPos, m_TargetPos);
			m_Sword->SetQuaternion(Q);

			m_Sword->SetPosition(LerpPos);
		}
		else
		{
			m_ChargeState = 1;
		}
		break;
	case 1:
		if (m_CurShootTime < 3.0f * Manager::Time)
		{
			m_CurShootTime++;
			
			D3DXVECTOR3 MoveValue = m_Sword->GetPosition() + m_Direction * 0.1f;

			D3DXQUATERNION Q = Math::QuaternionLookAt(MoveValue, m_Sword->GetPosition());
			m_Sword->SetQuaternion(Q);

			m_Sword->SetPosition(MoveValue);
			// エフェクト
			m_Sword->TrailEffect();

			PhysicsCast* PhyMinion;
			PhysicsCast* PhyBoss;
			// Minionのボックスキャスト
			PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
			if (PhyMinion != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Sword->SetDestroy();
				return;
			}
			// Bossのボックスキャスト
			PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
			if (PhyBoss != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Sword->SetDestroy();
				return;
			}
		}
		else
		{
			// 剣の軌跡を初期化
			m_Sword->InitSwordTrail();

			m_Sword->SetDestroy();
			return;
		}
		break;
	}
}

void SwordSkill05::Init()
{
	// キャラクター取得
	m_Character = m_Sword->GetCharacter();

	// 角度初期化
	m_Angle = 0.0f;

	// ダメージしたbool文初期化
	m_Damaged = false;
}

void SwordSkill05::Update()
{
	// プレイヤーの座標
	D3DXVECTOR3 CharPos = m_Character->GetPosition();
	CharPos.y += 1.5f;
	// 距離を設置
	float Dist = 1.0f;
	// 置く角度
	float _PlaceAngle;

	// 剣の置く場所によって変わる
	switch (m_Sword->GetSwordPos())
	{
	case Sword::First:
		// 色の変更
		m_Sword->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		_PlaceAngle = (72.0f * 1) + m_Angle;
		break;
	case Sword::Second:
		// 色の変更
		m_Sword->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		_PlaceAngle = (72.0f * 2) + m_Angle;
		break;
	case Sword::Third:
		// 色の変更
		m_Sword->ChangeTrailColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
		_PlaceAngle = (72.0f * 3) + m_Angle;
		break;
	case Sword::Fourth:
		// 色の変更
		m_Sword->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f));
		_PlaceAngle = (72.0f * 4) + m_Angle;
		break;
	case Sword::Fifth:
		// 色の変更
		m_Sword->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f));
		_PlaceAngle = (72.0f * 5) + m_Angle;
		break;
	}

	// 座標を計算する
	float RightValue = cosf(_PlaceAngle * Dist);
	float ForwardValue = sinf(_PlaceAngle * Dist);
	// 向いている方向を設置
	D3DXVECTOR3 PointTarget = CharPos;
	// 座標を設置
	CharPos += -m_Character->GetRight() * RightValue;
	CharPos += -m_Character->GetForward() * ForwardValue;
	m_Sword->SetPosition(CharPos);

	// 回転させる
	D3DXQUATERNION Q = Math::QuaternionLookAt(CharPos, PointTarget);
	m_Sword->SetQuaternion(Q);

	// 剣の軌跡エフェクト
	m_Sword->TrailEffect();

	// 角度を足す
	m_Angle += 0.2f;

	if (m_Damaged) return;

	// カメラ取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// ダメージ判定
	PhysicsCast* PhyMinion;
	PhysicsCast* PhyBoss;
	// Minionのボックスキャスト
	PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	if (PhyMinion != NULL)
	{
		// カメラシェークデバッグ
		if (_Camera != NULL)
		{
			_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
		}
		m_Damaged = true;
		PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
		EffectPos.y += 1.0f;
		m_Sword->HitEffect(EffectPos);
		return;
	}
	// Bossのボックスキャスト
	PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	if (PhyBoss != NULL)
	{
		// カメラシェークデバッグ
		if (_Camera != NULL)
		{
			_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
		}
		m_Damaged = true;
		PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
		EffectPos.y += 1.0f;
		m_Sword->HitEffect(EffectPos);
		return;
	}
}

void SwordSkill06::Init()
{
	// 撃つ時間初期化
	m_CurShootTime = 0.0f;

	// 初期座標記録
	m_InitPos = m_Sword->GetPosition();

	// 目標が存在していないと
	if (m_Sword->GetTargetObj() == NULL)
	{
		// 目標座標（前に撃つ）
		m_TargetPos = m_Sword->GetTargetPos();
	}
	else
	{
		// 目標座標（ターゲットに撃つ）
		m_TargetObj = m_Sword->GetTargetObj();
	}

	// 初期Tan
	m_InitUp = m_Sword->GetInitUp();

	// 撃つ回数を記録
	m_ShootCnt = m_Sword->GetShootCnt();

	// サイズを大きくする
	m_Sword->SetScale(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
}

void SwordSkill06::Update()
{
	if (m_CurShootTime < m_TotalShootTime)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / m_TotalShootTime;

		// エルミート用
		D3DXVECTOR3 HermitePos;
		// 初期座標
		D3DXVECTOR3 InitPos = m_InitPos;
		// 終点座標
		D3DXVECTOR3 TargetPos;
		if (m_TargetObj != NULL)
		{
			TargetPos = m_TargetObj->GetPosition();
			TargetPos.y += 1.5f;
		}
		else
		{
			TargetPos = m_TargetPos;
		}
		// 初期Tangent
		D3DXVECTOR3 InitTan = m_InitUp * 25.0f;
		// 終点Tangent
		D3DXVECTOR3 TargetTan = -m_InitUp * 25.0f;

		// エルミート
		D3DXVec3Hermite(&HermitePos, &InitPos, &InitTan, &TargetPos, &TargetTan, T);

		// 回転計算
		D3DXQUATERNION Q;
		Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// 座標設置
		m_Sword->SetPosition(HermitePos);

		// エフェクト
		m_Sword->TrailEffect();
	}
	else
	{
		// ダメージイベント
		// Minionのボックスキャスト
		PhysicsCast* PhyMinion;
		PhysicsCast* PhyBoss;
		// シーン取得
		Scene* _Scene = Manager::GetScene();
		// カメラ取得
		Camera* _Camera = _Scene->GetGameObject<Camera>();

		PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
		if (PhyMinion != NULL)
		{
			// カメラシェークデバッグ
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}
			PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
			EffectPos.y += 1.0f;
			m_Sword->HitEffect(EffectPos);
		}
		// Bossのボックスキャスト
		PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
		if (PhyBoss != NULL)
		{
			// カメラシェークデバッグ
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}
			PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
			EffectPos.y += 1.0f;
			m_Sword->HitEffect(EffectPos);
		}


		// 撃つ回数を減らす
		m_ShootCnt--;
		if (m_ShootCnt <= 0)
		{
			// 剣の軌跡を初期化
			m_Sword->InitSwordTrail();

			m_Sword->SetDestroy();
			return;
		}
		else
		{
			// 撃つ回数がまだある場合もう一回行います
			// 時間初期化
			m_CurShootTime = 0.0f;
			// 現在座標を更新します
			m_InitPos = m_Sword->GetPosition();
			// 初期Tangent更新
			m_InitUp = -m_Sword->GetQuaternionUp() * 2.0f;
		}
	}
}

void SwordAttack_ForSkill::Init()
{
	// キャラクターを取得
	m_Character = m_Sword->GetCharacter();

	// 初期化
	m_Damaged = false;
	m_InitPos = m_Sword->GetPosition();
	m_InitUp = m_Sword->GetInitUp();
	m_EndPos = m_Sword->GetEndPos();
	m_EndTan = m_Sword->GetEndTan();
	m_CurShootTime = 0.0f;
	m_TotalAttackTime = m_Sword->GetTotalAtkTime();

}

void SwordAttack_ForSkill::Update()
{
	if (m_Character == NULL) return;

	// 攻撃
	if (m_CurShootTime < m_TotalAttackTime)
	{
		// 時間増加
		m_CurShootTime++;
		// 1.0以内の長さを取る
		float T = m_CurShootTime / m_TotalAttackTime;

		// エルミート曲線に代入する変数
		D3DXVECTOR3 HermitePos;
		// 初期座標
		D3DXVECTOR3 InitPos = m_InitPos;
		// 目的座標
		D3DXVECTOR3 TargetPos = m_EndPos;
		// Tangent1
		D3DXVECTOR3 Tangent1 = m_InitUp;
		// Tangent2
		D3DXVECTOR3 Tangent2 = m_EndTan;

		// エルミート曲線計算
		D3DXVec3Hermite(&HermitePos, &InitPos, &Tangent1, &TargetPos, &Tangent2, T);

		// 回転処理
		// 方向を計算します
		D3DXVECTOR3 Dir = HermitePos - m_Sword->GetPosition();
		//D3DXVec3Normalize(&Dir, &Dir);

		D3DXQUATERNION Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// ポジションを更新する
		m_Sword->SetPosition(HermitePos);

		// トレールエフェクト
		m_Sword->TrailEffect();

		// ダメージしたかどうか
		if (!m_Damaged)
		{
			// ボックスキャスト用変数
			PhysicsCast* PhyBoss;
			PhysicsCast* PhyMinion;

			// Minionのボックスキャスト
			PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyMinion != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
			// Bossのボックスキャスト
			PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyBoss != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
		}
	}
	else
	{
		// 剣の軌跡を初期化
		m_Sword->InitSwordTrail();
		// 目的地まで行ったので消します
		m_Sword->SetDestroy();
		return;
	}

}
