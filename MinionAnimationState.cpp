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
	// ���[�v�ݒ�
	m_Loop = true;
	// �t���[���X�V���x�ݒ�
	m_PlayRate = 0.75f;
	// �t���[��������
	m_Frame = 0.0f;
	// ���݂̃A�j���[�V�������O
	m_AnimationTree->SetAnimationName("Idle");
}

void MinionAnimationState_Idle::Update()
{
	// �t���[���X�V
	m_Frame += m_PlayRate;
}

void MinionAnimationState_Run::Init()
{
	// ���[�v�ݒ�
	m_Loop = true;
	// �t���[���X�V���x�ݒ�
	m_PlayRate = 0.75f;
	// �t���[��������
	m_Frame = 0.0f;
	// ���݂̃A�j���[�V�������O
	m_AnimationTree->SetAnimationName("Run");
}

void MinionAnimationState_Run::Update()
{
	// �t���[���X�V
	m_Frame += m_PlayRate;
}

void MinionAnimationState_Attack01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.75f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack01");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �U���̃^�C�~���O
	m_Notify["Attack01Dmg"] = 30.0f;
	m_NotifyDone["Attack01Dmg"] = false;
}

void MinionAnimationState_Attack01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �U������
		if (m_Frame >= m_Notify["Attack01Dmg"] && !m_NotifyDone["Attack01Dmg"])
		{
			m_NotifyDone["Attack01Dmg"] = true;
			m_Character->AttackEvent();
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionAnimationState_Attack02::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.75f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack02");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �U���̃^�C�~���O
	m_Notify["Attack02Dmg"] = 44.0f;
	m_NotifyDone["Attack02Dmg"] = false;
}

void MinionAnimationState_Attack02::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �U������
		if (m_Frame >= m_Notify["Attack02Dmg"] && !m_NotifyDone["Attack02Dmg"])
		{
			m_NotifyDone["Attack02Dmg"] = true;
			m_Character->AttackEvent();
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionAnimationState_Hit::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.75f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Hit");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
}

void MinionAnimationState_Hit::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionAnimationState_Show::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.75f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Show");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// ���Ԓʒm
	m_Notify["MinionScream"] = 35.0f;
	m_NotifyDone["MinionScream"] = false;
}

void MinionAnimationState_Show::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// ���Ԓʒm
		if (m_Frame >= m_Notify["MinionScream"] && !m_NotifyDone["MinionScream"])
		{
			m_NotifyDone["MinionScream"] = true;
			AudioManager::PlaySE("SEZombie");
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_Character->ChangeBehavior<MinionBehaviorTree_Idle>();
	}
}

void MinionAnimationState_Dead::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.75f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Dead");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �����鎞��
	m_Notify["DeadFallTime"] = 48.0f;
}

void MinionAnimationState_Dead::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame < m_Notify["DeadFallTime"])
		{
			m_Character->SetPosition(D3DXVECTOR3(m_Character->GetPosition().x, m_Character->GetPosition().y - 0.0125f, m_Character->GetPosition().z));
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
	}
}
