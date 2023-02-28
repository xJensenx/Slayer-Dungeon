#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Boss.h"
#include "BossAnimation.h"
#include "BossBehaviorTree.h"
#include "BossHpBar.h"
#include "Player.h"
#include "MeshField.h"
#include "Math.h"
#include "Fade.h"
#include "Boss_AttackWarning.h"
#include "Boss_AttackEvent.h"
#include "BossAnimationState.h"
#include "AudioManager.h"

void BossIdle::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_Idle>();
}

void BossIdle::Update()
{ 
	m_Character->SetisAttacking(false);
}

void BossChase::Init()
{
	Scene* _Scene = Manager::GetScene();
	BossHpBar* _BHB = _Scene->GetGameObject<BossHpBar>();
	if (_BHB == NULL)
	{
		_BHB = _Scene->AddGameObject<BossHpBar>(Scene::Layer_UILayer);
		_BHB->SetCharacter(m_Character);
	}
}

void BossChase::Update()
{	
	bool HalfHp = m_Character->GetHalfHp();
	// ボスのPos
	D3DXVECTOR3 _Position = m_Character->GetPosition();
	// ボスのForward
	D3DXVECTOR3 _Forward = m_Character->GetForward();
	// ターゲットのPos
	D3DXVECTOR3 _TargetPos = m_Character->GetTargetPos();

	if (!HalfHp)
	{
		if (m_Character->GetCurHp() <= m_Character->GetMaxHp() / 2)
		{
			m_Character->SetQTEState(0);
			m_Character->SetHalfHp(true);
			m_Character->SetQTEFinish(false);
			return;
		}
	}

	m_Character->SetisAttacking(false);
	// もし攻撃範囲に入ると攻撃判定に切り替える
	float Dist = Math::Distance(_Position, _TargetPos);
	if (Dist <= 15.0f)
	{
		if (!m_Character->GetCoolDown())
		{
			int RandNum = rand() % 4;
			switch (RandNum)
			{
			case 0:
			{			
				m_Character->SetBossJumpCurTime(0.0f);
				m_Character->SetBossJumpStartPosition(_Position);
				D3DXVECTOR3 EndPos = _TargetPos;
				EndPos += _Forward * 2.0f;
				m_Character->SetBossJumpEndPosition(EndPos);
				m_Character->ChangeBehaviorTree<BossJumpAtk>();
				return;
			}
			case 1:
				m_Character->ChangeBehaviorTree<BossSummonMeteor>();
				return;
			case 2:
				m_Character->ChangeBehaviorTree<BossShootFireBall>();
				return;
			case 3:
				m_Character->ChangeBehaviorTree<BossShootRotateFireBall>();
				return;
			default:
				break;
			}
		}
	}


	if (Dist <= 5.0f)
	{
		Boss::BossPhase Phase = m_Character->GetBossPhase();

		switch (Phase)
		{
		case Boss::NormalPhase:
			m_Character->ChangeBehaviorTree<BossAttack>();
			break;
		case Boss::RagePhase:
			m_Character->ChangeBehaviorTree<BossRageAtk>();
			break;
		}
		return;
	}

	if (!m_AnimationTree->GetCurAnimationState<BossAnimation_Run>())
	{
		m_AnimationTree->ChangeState<BossAnimation_Run>();
	}
	// ターゲットの方向を計算しNormalizeする
	D3DXVECTOR3 TargetDir;
	TargetDir = _TargetPos - _Position;
	D3DXVec3Normalize(&TargetDir, &TargetDir);
	TargetDir.y = 0.0f;	// Y方向（縦）を０にする（飛ばないように）

	// ボスをプレイヤーの方向に向く
	m_Character->SetRotation(D3DXVECTOR3(m_Character->GetRotation().x, Math::RotateTowards(_TargetPos, _Position) + Math::PI(), m_Character->GetRotation().z));

	// ターゲットを追う（方向　*　速度）
	m_Character->SetPosition(m_Character->GetPosition() + (TargetDir * m_Character->GetChaseSpd()));
	
}

void BossAttack::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_HeavyPunch>();
}

void BossAttack::Update()
{
	m_Character->SetisAttacking(true);

	m_Character->SetRotation(D3DXVECTOR3(m_Character->GetRotation().x, Math::RotateTowards(m_Character->GetTargetPos(), m_Character->GetPosition()) + Math::PI(), m_Character->GetRotation().z));

	// アニメーションが完了したらプレイヤーを追う動作に戻る
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->ChangeBehaviorTree<BossIdle>();
	}

}

void BossJumpAtk::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_JumpAtk>();
	m_AnimationTree->SetJumpFinish(false);
	m_isJump = false;
	m_JumpAtk = false;
	
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// 攻撃警告追加
	m_WarningEffect = _Scene->AddGameObject<Boss_AttackWarning>(Scene::Layer_ObjectLayer);
	m_WarningEffect->SetSize(D3DXVECTOR3(15.0f, 0.0f, 15.0f));
	
}

void BossJumpAtk::Update()
{
	// 攻撃中
	m_Character->SetisAttacking(true);

	//
	D3DXVECTOR3 _Position = m_Character->GetPosition();

	if (m_WarningEffect != NULL)
	{
		m_WarningEffect->SetPosition(D3DXVECTOR3(_Position.x, m_WarningEffect->GetPosition().y, _Position.z));
	}

	// ボスのジャンプタイム
	float BossJumpCurTime = m_Character->GetBossJumpCurTime();

	float BossJumpMaxTime = m_Character->GetBossJumpMaxTime();

	D3DXVECTOR3 JumpStartPos = m_Character->GetBossJumpStartPos();

	D3DXVECTOR3 JumpEndPos = m_Character->GetBossJumpEndPos();

	// アニメーションがジャンプ準備したら
	if (m_AnimationTree->GetReadyJump())
	{
		Scene* _Scene = Manager::GetScene();
		Player* _Player = _Scene->GetGameObject<Player>();
		MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

		if (m_AnimationTree->GetJumpFinish())
		{
			// 地面に着いた瞬間攻撃する
			if (_Position.y <= _MeshField->GetHeight(_Position))
			{
				if (!m_JumpAtk)
				{
					m_WarningEffect->SetDestroy();
					m_JumpAtk = true;
					m_Character->AttackEvent<Boss_Attack_JumpAtk>();
					m_AnimationTree->SetJumpDmg(true);

					AudioManager::PlaySE("SEBossLand");
				}
			}
		}

		// 一回ジャンプする
		if (!m_isJump)
		{
			RigidBody* _RGB = m_Character->GetComponent<RigidBody>();
			_RGB->AddForce(D3DXVECTOR3(0.0f, 0.70f, 0.0f));
			m_isJump = true;
		}


		// ジャンプ時間残り1秒だと座標更新を止まる（バランス調整のため）
		if (BossJumpCurTime < 2.0f * Manager::Time)
		{
			m_Character->SetBossJumpEndPosition(_Player->GetPosition());
			// 線形補間用
			D3DXVECTOR3 LerpPos;
			// 線形補間用時間
			float T = BossJumpCurTime / BossJumpMaxTime;
			// 線形補間
			D3DXVec3Lerp(&LerpPos, &JumpStartPos, &JumpEndPos, T);
			// Y座標をジャンプの高さの座標にする
			LerpPos.y = m_Character->GetPosition().y;
			// 座標を更新する
			m_Character->SetPosition(LerpPos);
			// ボスをプレイヤーの方向に向く
			m_Character->SetRotation(D3DXVECTOR3(m_Character->GetRotation().x, Math::RotateTowards(JumpEndPos, _Position) + Math::PI(), m_Character->GetRotation().z));
		}

		// 地面に近づく時ジャンプアニメーション再開する
		if (_Position.y - 0.75f >= _MeshField->GetHeight(_Position))
		{
			m_AnimationTree->SetJumpFinish(true);
		}

		// ジャンプの時間経過を更新
		if (BossJumpCurTime < BossJumpMaxTime)
		{
			BossJumpCurTime++;
			m_Character->SetBossJumpCurTime(BossJumpCurTime);
		}
	}

}

void BossJumpAtkSec::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_JumpAtkSec>();
}

void BossJumpAtkSec::Update()
{
}

void BossRageAtk::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_RageAtk01>();
}

void BossRageAtk::Update()
{
	m_Character->SetisAttacking(true);

	m_Character->SetRotation(D3DXVECTOR3(m_Character->GetRotation().x, Math::RotateTowards(m_Character->GetTargetPos(), m_Character->GetPosition()) + Math::PI(), m_Character->GetRotation().z));

	// アニメーションが完了したらプレイヤーを追う動作に戻る
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->ChangeBehaviorTree<BossIdle>();
	}
}

void BossDead::Init()
{
	if (!m_AnimationTree->GetCurAnimationState<BossAnimation_Dead>())
	{
		m_AnimationTree->ChangeState<BossAnimation_Dead>();
		RigidBody* _RGB = m_Character->GetComponent<RigidBody>();
		_RGB->SetGravity(0.0f);
		_RGB->SetMass(D3DXVECTOR3(0.f, 0.0f, 0.1f));
	}
}

void BossDead::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->SetDestroy();
		Fade::SetFade<FadeSceneType_Result>();
		return;
	}
}

void BossShow::Init()
{
	if (!m_AnimationTree->GetCurAnimationState<BossAnimation_Jump>())
	{
		m_AnimationTree->ChangeState<BossAnimation_Jump>();
	}
}

void BossShow::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->ChangeBehaviorTree<BossRoar>();
		return;
	}
}

void BossRoar::Init()
{
	if (!m_AnimationTree->GetCurAnimationState<BossAnimation_Roar>())
	{
		m_AnimationTree->ChangeState<BossAnimation_Roar>();
	}
}

void BossRoar::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->ChangeBehaviorTree<BossIdle>();
		return;
	}
}

void BossQTE::Init()
{
}

void BossQTE::Update()
{
}

void BossSummonMeteor::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_SummonMeteor>();
}

void BossSummonMeteor::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->StartCoolDown();
		m_Character->ChangeBehaviorTree<BossIdle>();
		return;
	}
}

void BossShootFireBall::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_ShootFireBall01>();
}

void BossShootFireBall::Update()
{
	m_Character->SetRotation(D3DXVECTOR3(m_Character->GetRotation().x, Math::RotateTowards(m_Character->GetTargetPos(), m_Character->GetPosition()) + Math::PI(), m_Character->GetRotation().z));

	if (m_AnimationTree->GetPrevAniStatus() && m_AnimationTree->GetPrevAnimationState<BossAnimation_ShootFireBall03>())
	{
		m_Character->StartCoolDown();
		m_Character->ChangeBehaviorTree<BossIdle>();
		return;
	}
}

void BossRageSummonMeteor::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_RageSummonMeteor>();
}

void BossRageSummonMeteor::Update()
{
}

void BossShootRotateFireBall::Init()
{
	m_AnimationTree->ChangeState<BossAnimation_SummonRotateFireBall>();
}

void BossShootRotateFireBall::Update()
{
}
