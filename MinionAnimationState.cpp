#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Minion.h"
#include "MinionAnimation.h"
#include "MinionAnimationState.h"

#include "AudioManager.h"

void MinionAnimationState_Idle::Init()
{
	// ループ設定
	m_Loop = true;
	// フレーム更新速度設定
	m_PlayRate = 0.75f;
	// フレーム初期化
	m_Frame = 0.0f;
	// 現在のアニメーション名前
	m_AnimationTree->SetAnimationName("Idle");
}

void MinionAnimationState_Idle::Update()
{
	// フレーム更新
	m_Frame += m_PlayRate;
}

void MinionAnimationState_Run::Init()
{
	// ループ設定
	m_Loop = true;
	// フレーム更新速度設定
	m_PlayRate = 0.75f;
	// フレーム初期化
	m_Frame = 0.0f;
	// 現在のアニメーション名前
	m_AnimationTree->SetAnimationName("Run");
}

void MinionAnimationState_Run::Update()
{
	// フレーム更新
	m_Frame += m_PlayRate;
}

void MinionAnimationState_Attack01::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.75f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Attack01");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// 攻撃のタイミング
	m_Notify["Attack01Dmg"] = 30.0f;
	m_NotifyDone["Attack01Dmg"] = false;
}

void MinionAnimationState_Attack01::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		// 攻撃処理
		if (m_Frame >= m_Notify["Attack01Dmg"] && !m_NotifyDone["Attack01Dmg"])
		{
			m_NotifyDone["Attack01Dmg"] = true;
			m_Character->AttackEvent();
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionAnimationState_Attack02::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.75f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Attack02");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// 攻撃のタイミング
	m_Notify["Attack02Dmg"] = 44.0f;
	m_NotifyDone["Attack02Dmg"] = false;
}

void MinionAnimationState_Attack02::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		// 攻撃処理
		if (m_Frame >= m_Notify["Attack02Dmg"] && !m_NotifyDone["Attack02Dmg"])
		{
			m_NotifyDone["Attack02Dmg"] = true;
			m_Character->AttackEvent();
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionAnimationState_Hit::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.75f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Hit");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
}

void MinionAnimationState_Hit::Update()
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
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionAnimationState_Show::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.75f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Show");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();

	// 叫ぶ通知
	m_Notify["MinionScream"] = 35.0f;
	m_NotifyDone["MinionScream"] = false;
}

void MinionAnimationState_Show::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		// 叫ぶ通知
		if (m_Frame >= m_Notify["MinionScream"] && !m_NotifyDone["MinionScream"])
		{
			m_NotifyDone["MinionScream"] = true;
			AudioManager::PlaySE("SEZombie");
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
		// 待機状態に戻る
		m_Character->ChangeBehavior<MinionBehaviorTree_Idle>();
	}
}

void MinionAnimationState_Dead::Init()
{
	// ループしていない
	m_Loop = false;
	// フレームの初期化
	m_Frame = 0.0f;
	// プレイレートの初期化
	m_PlayRate = 0.75f;
	// アニメーション名前の設置
	m_AnimationTree->SetAnimationName("Dead");
	// アニメーションの長さ
	m_Duration = m_AnimationTree->GetDuration();
	// 落ちる時間
	m_Notify["DeadFallTime"] = 48.0f;
}

void MinionAnimationState_Dead::Update()
{
	// 長さ以下だと更新する
	if (m_Frame < m_Duration)
	{
		// フレーム更新
		m_Frame += m_PlayRate;
		// アニメーションが終了してない
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame < m_Notify["DeadFallTime"])
		{
			m_Character->SetPosition(D3DXVECTOR3(m_Character->GetPosition().x, m_Character->GetPosition().y - 0.0125f, m_Character->GetPosition().z));
		}
	}
	else
	{
		// アニメーションが終了した
		m_AnimationTree->SetPrevAniFinish(true);
	}
}
