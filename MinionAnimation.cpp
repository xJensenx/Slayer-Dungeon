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
	// �A�j���[�V�����X�e�[�g�X�V
	m_AnimationState->Update();

	// �u�����h���[�g���X�V���܂�
	if (m_BlendRate < 1.0f)
	{
		m_BlendRate += 0.03f;
		// �u�����h���Ă���ԑO�̃t���[�����X�V���܂�
		if (m_PrevLoop)
		{
			m_PrevFrame += m_PrevPlayRate;
		}
	}

	float _Frame = m_AnimationState->GetFrame();

	// �X�V�������l���A�j���[�V�������f���ɑ�����܂�
	m_AnimModel->SetBlendRate(m_BlendRate);
	m_AnimModel->SetFrame(m_PrevFrame, _Frame);

}
