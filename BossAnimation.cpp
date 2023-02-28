#include "main.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "BossAnimation.h"
#include "Boss.h"
#include "Boss_AttackEvent.h"

void BossAnimation::Init()
{
	// ������Ԃ͑S��Idle����n�߂܂�
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
	// �A�j���[�V�����X�e�[�g�X�V
	m_AnimationState->Update();
	
	// �u�����h���[�g���X�V���܂�
	if (m_BlendRate < 1.0f)
	{
		m_BlendRate += 0.03f;
		// �u�����h���Ă���ԑO�̃t���[�����X�V���܂�
		if (m_PrevLoop)
		{
			m_PrevFrame += 0.5f;
		}
	}
	// ���݂̃t���[�����擾
	float _Frame = m_AnimationState->GetFrame();

	// �X�V�������l���A�j���[�V�������f���ɑ�����܂�
	m_AnimModel->SetBlendRate(m_BlendRate);
	m_AnimModel->SetFrame(m_PrevFrame, _Frame);
}