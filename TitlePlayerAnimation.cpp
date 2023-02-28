#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "TitlePlayerAnimation.h"
#include "TitleCharacter.h"
#include "Math.h"

void TitlePlayerAnimation::Init()
{
	// 初期状態は全部Idleから始めます
	m_State = Idle01;
	m_PreviousState = Idle01;
	//m_CurLoop = false;

	m_AnimModel->LoadAnimation("Idle01", "Idle01");
	ChangeState(Idle01);
}

void TitlePlayerAnimation::Uninit()
{
}

void TitlePlayerAnimation::Update()
{
	// フレームを更新します
	if (!m_CurLoop)
	{
		if (m_CurFrame < m_AnimModel->GetAnimDuration(m_CurAnimationName))
		{
			m_isPrevAniFinish = false;
			m_CurFrame += 0.5f;

			if (m_State == Chosen)
			{
				if (m_CurFrame >= 50.0f)
				{
					m_Character->SetAnimationFinish();
				}
			}
		}
		else
		{
			m_isPrevAniFinish = true;
			switch (m_State)
			{
			case Chosen:
				break;
			default:
				int RandNum = Math::IntRandBetween(0, 2);
				ChangeState((PlayerState)RandNum);
				break;
			}
		}
	}
	else
	{
		m_CurFrame += 0.5f;
	}

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

	// 更新した数値をアニメーションモデルに代入します
	m_AnimModel->SetBlendRate(m_BlendRate);
	m_AnimModel->SetFrame(m_PrevFrame, m_CurFrame);

}
