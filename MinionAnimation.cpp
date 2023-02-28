#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "MinionAnimation.h"
#include "Minion.h"

void MinionAnimation::Init()
{
	m_CurAnimationName = "Idle";
	m_PrevAnimationName = "Idle";

	m_isPrevAniFinish = false;

	ChangeState<MinionAnimationState_Idle>();
}

void MinionAnimation::Uninit()
{
}

void MinionAnimation::Update()
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
			m_PrevFrame += m_PrevPlayRate;
		}
	}

	float _Frame = m_AnimationState->GetFrame();

	// 更新した数値をアニメーションモデルに代入します
	m_AnimModel->SetBlendRate(m_BlendRate);
	m_AnimModel->SetFrame(m_PrevFrame, _Frame);

}
