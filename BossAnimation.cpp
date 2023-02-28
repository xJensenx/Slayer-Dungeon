#include "main.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "BossAnimation.h"
#include "Boss.h"
#include "Boss_AttackEvent.h"

void BossAnimation::Init()
{
	// 初期状態は全部Idleから始めます
	m_isPrevAniFinish = false;

	m_CurAnimationName = "Idle";
	m_PrevAnimationName = "Idle";

	ChangeState<BossAnimation_Idle>();
}

void BossAnimation::Uninit()
{
}

void BossAnimation::Update()
{
	// アニメーションステート更新
	m_AnimationState->Update();
	
	// ブレンドレートを更新します
	if (m_BlendRate < 1.0f)
	{
		m_BlendRate += 0.03f;
		// ブレンドしている間前のフレームも更新します
		if (m_PrevLoop)
		{
			m_PrevFrame += 0.5f;
		}
	}
	// 現在のフレームを取得
	float _Frame = m_AnimationState->GetFrame();

	// 更新した数値をアニメーションモデルに代入します
	m_AnimModel->SetBlendRate(m_BlendRate);
	m_AnimModel->SetFrame(m_PrevFrame, _Frame);
}