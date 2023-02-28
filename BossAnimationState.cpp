#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "Boss.h"
#include "BossAnimation.h"

#include "BossAnimationState.h"
#include "Boss_AttackEvent.h"
#include "BossBehaviorTree.h"

#include "AudioManager.h"
#include "Camera.h"

void BossAnimation_Idle::Init()
{
	// ループしている
	m_Loop = true;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Idle");
}

void BossAnimation_Idle::Update()
{
	// フレーム更新
	m_Frame += m_PlayRate;
}

void BossAnimation_Run::Init()
{		
	// ループしている
	m_Loop = true;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Run");
}

void BossAnimation_Run::Update()
{
	// フレーム更新
	m_Frame += m_PlayRate;
}

void BossAnimation_Roar::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Roar");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
}

void BossAnimation_Roar::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_Jump::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Jump");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// ジャンプが止まるフレーム
	m_Notify["Jump"] = 49.0f;
}

void BossAnimation_Jump::Update()
{	
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);
		
		// ジャンプが終わってないとフレームはこのフレームに止まる
		if (!m_AnimationTree->GetJumpFinish())
		{
			m_Frame = m_Notify["Jump"];
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_HeavyPunch::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.4f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("HeavyPunch");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// 攻撃タイミング
	m_Notify["HeavyPunchDmg"] = 39.0f;
	m_NotifyDone["HeavyPunchDmg"] = false;

}

void BossAnimation_HeavyPunch::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		// 攻撃タイミング通知を送る
		if (m_Frame >= m_Notify["HeavyPunchDmg"] && !m_NotifyDone["HeavyPunchDmg"])
		{
			m_NotifyDone["HeavyPunchDmg"] = true;
			m_Character->AttackEvent<Boss_Attack_HeavyAtk>();
			AudioManager::PlaySE("SEBossRage01");
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_JumpAtk::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("JumpAttack");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// ジャンプするタイミング
	m_Notify["JumpStart"] = 16.0f;
	// ジャンプ止まるタイミング
	m_Notify["JumpPause"] = 43.0f;
	// ジャンプ攻撃二段目発動タイミング
	m_Notify["ActivateJumpSecond"] = 65.0f;
	m_NotifyDone["ActivateJumpSecond"] = false;
}

void BossAnimation_JumpAtk::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		// ジャンプ通知を送る
		if (m_Frame >= m_Notify["JumpStart"])
		{
			m_AnimationTree->SetReadyJump(true);
		}
		// 空中にいる時はジャンプアニメーション止まる
		if (!m_AnimationTree->GetJumpFinish())
		{
			if (m_Frame >= m_Notify["JumpPause"])
			{
				m_Frame = m_Notify["JumpPause"];
			}
		}

		if (m_AnimationTree->GetJumpDmg())
		{
			// 暴走状態だともう一つの攻撃を追加
			if (m_Character->GetBossPhase() == Boss::RagePhase)
			{
				if (m_Frame >= m_Notify["ActivateJumpSecond"] && !m_NotifyDone["ActivateJumpSecond"])
				{
					m_NotifyDone["ActivateJumpSecond"] = true;
					m_Character->ChangeBehaviorTree<BossJumpAtkSec>();
				}
			}
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// ジャンプ攻撃終わる処理
		m_Character->StartCoolDown();
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_JumpAtkSec::Init()
{	
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("JumpAtkSecond");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// ジャンプ攻撃二段目ダメージタイミング
	m_Notify["JumpSecondAtkTiming"] = 30.0f;
	m_NotifyDone["JumpSecondAtkTiming"] = false;
}

void BossAnimation_JumpAtkSec::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		// 攻撃タイミング
		if (m_Frame >= m_Notify["JumpSecondAtkTiming"] && !m_NotifyDone["JumpSecondAtkTiming"])
		{
			m_NotifyDone["JumpSecondAtkTiming"] = true;
			m_Character->AttackEvent<Boss_Attack_JumpAtkSec>();
			AudioManager::PlaySE("SEBossLand");
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// ジャンプ攻撃終わる処理
		m_Character->StartCoolDown();
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_Dead::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Dead");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// ボスが倒されたらの落ちる時間
	m_Notify["DeadStart"] = 50.0f;
	m_Notify["DeadEnd"] = 70.0f;

	// カメラ取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// 座標設置
	D3DXVECTOR3 NewCamPos = m_Character->GetPosition();
	NewCamPos.y += 5.0f;
	NewCamPos.x -= 10.0f;
	

	// カメラをCinematicにしボスを注目する
	_Camera->SetCinematicMode(true);
	_Camera->BlendTo(NewCamPos, m_Character->GetPosition(), 0.5f);
	

}

void BossAnimation_Dead::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["DeadStart"] && m_Frame <= m_Notify["DeadEnd"])
		{
			m_Character->SetPosition(D3DXVECTOR3(m_Character->GetPosition().x, m_Character->GetPosition().y - 0.1f, m_Character->GetPosition().z));
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
	}
}

void BossAnimation_QTERoar::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Roar");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

}

void BossAnimation_QTERoar::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_QTEAfterRoar::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("HeavyPunch");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

}

void BossAnimation_QTEAfterRoar::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_QTEInjured::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Injured");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
}

void BossAnimation_QTEInjured::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// QTEの次のステートに進む
		m_Character->SetQTEState(29);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_RageAtk01::Init()
{
	// ループしていない
	m_Loop = false;
	// RageAtk01DmgTiming
	m_Notify["RageAtk01Dmg01Timing"] = 28.0f;
	m_NotifyDone["RageAtk01Dmg01Timing"] = false;
	m_Notify["RageAtk01Dmg02Timing"] = 47.0f;
	m_NotifyDone["RageAtk01Dmg02Timing"] = false;
	m_Notify["RageAtk01Dmg03Timing"] = 79.0f;
	m_NotifyDone["RageAtk01Dmg03Timing"] = false;

	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("RageAtk01");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
}

void BossAnimation_RageAtk01::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["RageAtk01Dmg01Timing"] && !m_NotifyDone["RageAtk01Dmg01Timing"])
		{
			m_NotifyDone["RageAtk01Dmg01Timing"] = true;
			m_Character->AttackEvent<Boss_Attack_HeavyAtk>();
			AudioManager::PlaySE("SEBossRage01");
		}

		if (m_Frame >= m_Notify["RageAtk01Dmg02Timing"] && !m_NotifyDone["RageAtk01Dmg02Timing"])
		{
			m_NotifyDone["RageAtk01Dmg02Timing"] = true;
			m_Character->AttackEvent<Boss_Attack_HeavyAtk>();
			AudioManager::PlaySE("SEBossRage01");
		}

		if (m_Frame >= m_Notify["RageAtk01Dmg03Timing"] && !m_NotifyDone["RageAtk01Dmg03Timing"])
		{
			m_NotifyDone["RageAtk01Dmg03Timing"] = true;
			m_Character->AttackEvent<Boss_Attack_KnockBack>();
			AudioManager::PlaySE("SEBossRage02");
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}

void BossAnimation_SummonMeteor::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Roar");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// 隕石を召喚するタイミング
	m_Notify["SummonMeteor01"] = 50.0f;
	m_NotifyDone["SummonMeteor01"] = false;
	m_Notify["SummonMeteor02"] = 71.0f;
	m_NotifyDone["SummonMeteor02"] = false;
	m_Notify["SummonMeteor03"] = 92.0f;
	m_NotifyDone["SummonMeteor03"] = false;
	m_Notify["SummonMeteor04"] = 110.0f;
	m_NotifyDone["SummonMeteor04"] = false;
	m_Notify["SummonMeteor05"] = 127.0f;
	m_NotifyDone["SummonMeteor05"] = false;

}

void BossAnimation_SummonMeteor::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["SummonMeteor01"] && !m_NotifyDone["SummonMeteor01"])
		{
			m_NotifyDone["SummonMeteor01"] = true;
			m_Character->SummonMeteor();
		}
		if (m_Frame >= m_Notify["SummonMeteor02"] && !m_NotifyDone["SummonMeteor02"])
		{
			m_NotifyDone["SummonMeteor02"] = true;
			m_Character->SummonMeteor();
		}
		if (m_Frame >= m_Notify["SummonMeteor03"] && !m_NotifyDone["SummonMeteor03"])
		{
			m_NotifyDone["SummonMeteor03"] = true;
			m_Character->SummonMeteor();
		}
		if (m_Frame >= m_Notify["SummonMeteor04"] && !m_NotifyDone["SummonMeteor04"])
		{
			m_NotifyDone["SummonMeteor04"] = true;
			m_Character->SummonMeteor();
		}
		if (m_Frame >= m_Notify["SummonMeteor05"] && !m_NotifyDone["SummonMeteor05"])
		{
			m_NotifyDone["SummonMeteor05"] = true;
			m_Character->SummonMeteor();

			if (m_Character->GetBossPhase() == Boss::RagePhase)
			{
				m_Character->ChangeBehaviorTree<BossRageSummonMeteor>();
				return;
			}
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_ShootFireBall01::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("ShootFireBall01");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// 次のアニメーションに切り替わる
	m_Notify["ChangeShootFireBall02"] = 40.0f;
	m_NotifyDone["ChangeShootFireBall02"] = false;
}

void BossAnimation_ShootFireBall01::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["ChangeShootFireBall02"] && !m_NotifyDone["ChangeShootFireBall02"])
		{
			m_NotifyDone["ChangeShootFireBall02"] = true;
			m_AnimationTree->ChangeState<BossAnimation_ShootFireBall02>();
			return;
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_ShootFireBall02::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("HeavyPunch");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// ファイアボールを打つ
	m_Notify["ShootFireBall"] = 39.0f;
	m_NotifyDone["ShootFireBall"] = false;

	m_Notify["ChangeNextAnimation"] = 46.0f;
	m_NotifyDone["ChangeNextAnimation"] = false;
}

void BossAnimation_ShootFireBall02::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["ShootFireBall"] && !m_NotifyDone["ShootFireBall"])
		{
			m_NotifyDone["ShootFireBall"] = true;
			m_Character->ShootFireBall();
		}
		if (m_Frame >= m_Notify["ChangeNextAnimation"] && !m_NotifyDone["ChangeNextAnimation"])
		{
			m_NotifyDone["ChangeNextAnimation"] = true;
			m_AnimationTree->ChangeState<BossAnimation_ShootFireBall03>();
			return;
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_ShootFireBall03>();
	}

}

void BossAnimation_ShootFireBall03::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("LightPunch");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// ファイアボールを打つ
	m_Notify["ShootFireBallTwo"] = 9.0f;
	m_NotifyDone["ShootFireBallTwo"] = false;

}

void BossAnimation_ShootFireBall03::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["ShootFireBallTwo"] && !m_NotifyDone["ShootFireBallTwo"])
		{
			m_NotifyDone["ShootFireBallTwo"] = true;
			m_Character->ShootHermiteBall();
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}

void BossAnimation_RageSummonMeteor::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("RageSummonMeteor");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// 召喚始めるタイミング
	m_Notify["RageSummonMeteorAtk01"] = 26.0f;
	m_NotifyDone["RageSummonMeteorAtk01"] = false;
	m_Notify["RageSummonMeteorAtk02"] = 34.0f;
	m_NotifyDone["RageSummonMeteorAtk02"] = false;
	m_Notify["RageSummonMeteorAtk03"] = 42.0f;
	m_NotifyDone["RageSummonMeteorAtk03"] = false;
	m_Notify["RageSummonMeteorAtk04"] = 50.0f;
	m_NotifyDone["RageSummonMeteorAtk04"] = false;
	m_Notify["RageSummonMeteorEnd"] = 65.0f;
	m_NotifyDone["RageSummonMeteorEnd"] = false;

}

void BossAnimation_RageSummonMeteor::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["RageSummonMeteorAtk01"] && !m_NotifyDone["RageSummonMeteorAtk01"])
		{
			m_NotifyDone["RageSummonMeteorAtk01"] = true;
			m_Character->RageSummonMeteor(1);
		}
		if (m_Frame >= m_Notify["RageSummonMeteorAtk02"] && !m_NotifyDone["RageSummonMeteorAtk02"])
		{
			m_NotifyDone["RageSummonMeteorAtk02"] = true;
			m_Character->RageSummonMeteor(2);
		}
		if (m_Frame >= m_Notify["RageSummonMeteorAtk03"] && !m_NotifyDone["RageSummonMeteorAtk03"])
		{
			m_NotifyDone["RageSummonMeteorAtk03"] = true;
			m_Character->RageSummonMeteor(3);
		}
		if (m_Frame >= m_Notify["RageSummonMeteorAtk04"] && !m_NotifyDone["RageSummonMeteorAtk04"])
		{
			m_NotifyDone["RageSummonMeteorAtk04"] = true;
			m_Character->RageSummonMeteor(4);
		}

		if (m_Frame >= m_Notify["RageSummonMeteorEnd"] && !m_NotifyDone["RageSummonMeteorEnd"])
		{
			m_NotifyDone["RageSummonMeteorEnd"] = true;
			m_Character->StartCoolDown();
			m_Character->ChangeBehaviorTree<BossIdle>();
			return;
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}

void BossAnimation_SummonRotateFireBall::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.5f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("SummonRotatingFireBall");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// 召喚始めるタイミング
	m_Notify["SummonRotateFireBall"] = 17.0f;
	m_NotifyDone["SummonRotateFireBall"] = false;

	m_Notify["SummonRotateEndTime"] = 25.0f;
	m_NotifyDone["SummonRotateEndTime"] = false;

}

void BossAnimation_SummonRotateFireBall::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["SummonRotateFireBall"] && !m_NotifyDone["SummonRotateFireBall"])
		{
			m_NotifyDone["SummonRotateFireBall"] = true;
			m_Character->ShootSpinningFireBall();
		}

		if (m_Frame >= m_Notify["SummonRotateEndTime"] && !m_NotifyDone["SummonRotateEndTime"])
		{
			m_NotifyDone["SummonRotateEndTime"] = true;
			m_Character->StartCoolDown();
			m_Character->ChangeBehaviorTree<BossIdle>();
			return;
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}
