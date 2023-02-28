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
	// ���[�v���Ă���
	m_Loop = true;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Idle");
}

void BossAnimation_Idle::Update()
{
	// �t���[���X�V
	m_Frame += m_PlayRate;
}

void BossAnimation_Run::Init()
{		
	// ���[�v���Ă���
	m_Loop = true;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Run");
}

void BossAnimation_Run::Update()
{
	// �t���[���X�V
	m_Frame += m_PlayRate;
}

void BossAnimation_Roar::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Roar");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
}

void BossAnimation_Roar::Update()
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
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_Jump::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Jump");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �W�����v���~�܂�t���[��
	m_Notify["Jump"] = 49.0f;
}

void BossAnimation_Jump::Update()
{	
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);
		
		// �W�����v���I����ĂȂ��ƃt���[���͂��̃t���[���Ɏ~�܂�
		if (!m_AnimationTree->GetJumpFinish())
		{
			m_Frame = m_Notify["Jump"];
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_HeavyPunch::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.4f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("HeavyPunch");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �U���^�C�~���O
	m_Notify["HeavyPunchDmg"] = 39.0f;
	m_NotifyDone["HeavyPunchDmg"] = false;

}

void BossAnimation_HeavyPunch::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �U���^�C�~���O�ʒm�𑗂�
		if (m_Frame >= m_Notify["HeavyPunchDmg"] && !m_NotifyDone["HeavyPunchDmg"])
		{
			m_NotifyDone["HeavyPunchDmg"] = true;
			m_Character->AttackEvent<Boss_Attack_HeavyAtk>();
			AudioManager::PlaySE("SEBossRage01");
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_JumpAtk::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("JumpAttack");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �W�����v����^�C�~���O
	m_Notify["JumpStart"] = 16.0f;
	// �W�����v�~�܂�^�C�~���O
	m_Notify["JumpPause"] = 43.0f;
	// �W�����v�U����i�ڔ����^�C�~���O
	m_Notify["ActivateJumpSecond"] = 65.0f;
	m_NotifyDone["ActivateJumpSecond"] = false;
}

void BossAnimation_JumpAtk::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �W�����v�ʒm�𑗂�
		if (m_Frame >= m_Notify["JumpStart"])
		{
			m_AnimationTree->SetReadyJump(true);
		}
		// �󒆂ɂ��鎞�̓W�����v�A�j���[�V�����~�܂�
		if (!m_AnimationTree->GetJumpFinish())
		{
			if (m_Frame >= m_Notify["JumpPause"])
			{
				m_Frame = m_Notify["JumpPause"];
			}
		}

		if (m_AnimationTree->GetJumpDmg())
		{
			// �\����Ԃ��Ƃ�����̍U����ǉ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �W�����v�U���I��鏈��
		m_Character->StartCoolDown();
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_JumpAtkSec::Init()
{	
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("JumpAtkSecond");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �W�����v�U����i�ڃ_���[�W�^�C�~���O
	m_Notify["JumpSecondAtkTiming"] = 30.0f;
	m_NotifyDone["JumpSecondAtkTiming"] = false;
}

void BossAnimation_JumpAtkSec::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �U���^�C�~���O
		if (m_Frame >= m_Notify["JumpSecondAtkTiming"] && !m_NotifyDone["JumpSecondAtkTiming"])
		{
			m_NotifyDone["JumpSecondAtkTiming"] = true;
			m_Character->AttackEvent<Boss_Attack_JumpAtkSec>();
			AudioManager::PlaySE("SEBossLand");
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �W�����v�U���I��鏈��
		m_Character->StartCoolDown();
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_Dead::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Dead");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
	// �{�X���|���ꂽ��̗����鎞��
	m_Notify["DeadStart"] = 50.0f;
	m_Notify["DeadEnd"] = 70.0f;

	// �J�����擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// ���W�ݒu
	D3DXVECTOR3 NewCamPos = m_Character->GetPosition();
	NewCamPos.y += 5.0f;
	NewCamPos.x -= 10.0f;
	

	// �J������Cinematic�ɂ��{�X�𒍖ڂ���
	_Camera->SetCinematicMode(true);
	_Camera->BlendTo(NewCamPos, m_Character->GetPosition(), 0.5f);
	

}

void BossAnimation_Dead::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["DeadStart"] && m_Frame <= m_Notify["DeadEnd"])
		{
			m_Character->SetPosition(D3DXVECTOR3(m_Character->GetPosition().x, m_Character->GetPosition().y - 0.1f, m_Character->GetPosition().z));
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
	}
}

void BossAnimation_QTERoar::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Roar");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

}

void BossAnimation_QTERoar::Update()
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
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_QTEAfterRoar::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("HeavyPunch");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

}

void BossAnimation_QTEAfterRoar::Update()
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
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_QTEInjured::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Injured");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
}

void BossAnimation_QTEInjured::Update()
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
		// QTE�̎��̃X�e�[�g�ɐi��
		m_Character->SetQTEState(29);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_RageAtk01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// RageAtk01DmgTiming
	m_Notify["RageAtk01Dmg01Timing"] = 28.0f;
	m_NotifyDone["RageAtk01Dmg01Timing"] = false;
	m_Notify["RageAtk01Dmg02Timing"] = 47.0f;
	m_NotifyDone["RageAtk01Dmg02Timing"] = false;
	m_Notify["RageAtk01Dmg03Timing"] = 79.0f;
	m_NotifyDone["RageAtk01Dmg03Timing"] = false;

	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("RageAtk01");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();
}

void BossAnimation_RageAtk01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}

void BossAnimation_SummonMeteor::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Roar");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// 覐΂���������^�C�~���O
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
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_ShootFireBall01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("ShootFireBall01");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// ���̃A�j���[�V�����ɐ؂�ւ��
	m_Notify["ChangeShootFireBall02"] = 40.0f;
	m_NotifyDone["ChangeShootFireBall02"] = false;
}

void BossAnimation_ShootFireBall01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}
}

void BossAnimation_ShootFireBall02::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("HeavyPunch");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// �t�@�C�A�{�[����ł�
	m_Notify["ShootFireBall"] = 39.0f;
	m_NotifyDone["ShootFireBall"] = false;

	m_Notify["ChangeNextAnimation"] = 46.0f;
	m_NotifyDone["ChangeNextAnimation"] = false;
}

void BossAnimation_ShootFireBall02::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_ShootFireBall03>();
	}

}

void BossAnimation_ShootFireBall03::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("LightPunch");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// �t�@�C�A�{�[����ł�
	m_Notify["ShootFireBallTwo"] = 9.0f;
	m_NotifyDone["ShootFireBallTwo"] = false;

}

void BossAnimation_ShootFireBall03::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		if (m_Frame >= m_Notify["ShootFireBallTwo"] && !m_NotifyDone["ShootFireBallTwo"])
		{
			m_NotifyDone["ShootFireBallTwo"] = true;
			m_Character->ShootHermiteBall();
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}

void BossAnimation_RageSummonMeteor::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("RageSummonMeteor");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// �����n�߂�^�C�~���O
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
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}

void BossAnimation_SummonRotateFireBall::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("SummonRotatingFireBall");
	// �A�j���[�V�����̒���
	m_Duration = m_AnimationTree->GetDuration();

	// �����n�߂�^�C�~���O
	m_Notify["SummonRotateFireBall"] = 17.0f;
	m_NotifyDone["SummonRotateFireBall"] = false;

	m_Notify["SummonRotateEndTime"] = 25.0f;
	m_NotifyDone["SummonRotateEndTime"] = false;

}

void BossAnimation_SummonRotateFireBall::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_Duration)
	{
		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �A�j���[�V�������I�����ĂȂ�
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
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<BossAnimation_Idle>();
	}

}
