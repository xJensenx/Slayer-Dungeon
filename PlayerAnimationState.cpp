#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Player.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationState.h"

void PlayerAnimation_Idle::Init()
{
	// ���[�v���Ă���
	m_Loop = true;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Idle");
}

void PlayerAnimation_Idle::Update()
{
	// �t���[���X�V
	m_Frame += m_PlayRate;
}

void PlayerAnimation_Run::Init()
{
	// ���[�v���Ă���
	m_Loop = true;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Run");

}

void PlayerAnimation_Run::Update()
{
	// �t���[���X�V
	m_Frame += m_PlayRate;
}

void PlayerAnimation_Attack01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack01");

	// Attack01�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Attack01DmgTiming"] = 24.0f;
	m_NotifyDone["Attack01DmgTiming"] = false;

	m_Notify["Attack01ChgStart"] = 25.0f;
	m_Notify["Attack01ChgEnd"] = 50.0f;
}

void PlayerAnimation_Attack01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V�i�U�����x�ɂ���ĕς��j
		m_Frame += m_PlayRate * m_Character->GetAttackSpd();

		// �U������
		if (m_Frame >= m_Notify["Attack01DmgTiming"] && !m_NotifyDone["Attack01DmgTiming"])
		{
			m_NotifyDone["Attack01DmgTiming"] = true;
			m_Character->AttackEvent();
		}

		if (m_Frame >= m_Notify["Attack01ChgStart"] && m_Frame < m_Notify["Attack01ChgEnd"])
		{
			m_Character->ReadyToAtk();
		}

		if (m_Frame >= m_Notify["Attack01ChgEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);

		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Attack02::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack02");

	// Attack02�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Attack02DmgTiming"] = 19.0f;
	m_NotifyDone["Attack02DmgTiming"] = false;

	m_Notify["Attack02ChgStart"] = 35.0f;
	m_Notify["Attack02ChgEnd"] = 60.0f;
}

void PlayerAnimation_Attack02::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V�i�U�����x�ɂ���ĕς��j
		m_Frame += m_PlayRate * m_Character->GetAttackSpd();

		// �U������
		if (m_Frame >= m_Notify["Attack02DmgTiming"] && !m_NotifyDone["Attack02DmgTiming"])
		{
			m_NotifyDone["Attack02DmgTiming"] = true;
			m_Character->AttackEvent();
		}

		if (m_Frame >= m_Notify["Attack02ChgStart"] && m_Frame < m_Notify["Attack02ChgEnd"])
		{
			m_Character->ReadyToAtk();
		}

		if (m_Frame >= m_Notify["Attack02ChgEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);

		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Attack03::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack03");
	// Attack03�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Attack03DmgTiming"] = 15.0f;
	m_NotifyDone["Attack03DmgTiming"] = false;

	m_Notify["Attack03ChgStart"] = 30.0f;
	m_Notify["Attack03ChgEnd"] = 60.0f;
}

void PlayerAnimation_Attack03::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V�i�U�����x�ɂ���ĕς��j
		m_Frame += m_PlayRate * m_Character->GetAttackSpd();

		// �U������
		if (m_Frame >= m_Notify["Attack03DmgTiming"] && !m_NotifyDone["Attack03DmgTiming"])
		{
			m_NotifyDone["Attack03DmgTiming"] = true;
			m_Character->AttackEvent();
		}

		if (m_Frame >= m_Notify["Attack03ChgStart"] && m_Frame < m_Notify["Attack03ChgEnd"])
		{
			m_Character->ReadyToAtk();
		}

		if (m_Frame >= m_Notify["Attack03ChgEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);

		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Attack04::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack04");

	// Attack04�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Attack04DmgTiming"] = 24.0f;
	m_NotifyDone["Attack04DmgTiming"] = false;

	m_Notify["Attack04ChgStart"] = 25.0f;
	m_Notify["Attack04ChgEnd"] = 50.0f;
}

void PlayerAnimation_Attack04::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V�i�U�����x�ɂ���ĕς��j
		m_Frame += m_PlayRate * m_Character->GetAttackSpd();

		// �U������
		if (m_Frame >= m_Notify["Attack04DmgTiming"] && !m_NotifyDone["Attack04DmgTiming"])
		{
			m_NotifyDone["Attack04DmgTiming"] = true;
			m_Character->AttackEvent();
		}

		if (m_Frame >= m_Notify["Attack04ChgStart"] && m_Frame < m_Notify["Attack04ChgEnd"])
		{
			m_Character->ReadyToAtk();
		}

		if (m_Frame >= m_Notify["Attack04ChgEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);

		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}

}

void PlayerAnimation_Attack05::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Attack05");

	// Attack05�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Attack05DmgTiming"] = 20.0f;
	m_NotifyDone["Attack05DmgTiming"] = false;

	m_Notify["Attack05ChgStart"] = 40.0f;
	m_Notify["Attack05ChgEnd"] = 60.0f;
}

void PlayerAnimation_Attack05::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V�i�U�����x�ɂ���ĕς��j
		m_Frame += m_PlayRate * m_Character->GetAttackSpd();

		// �U������
		if (m_Frame >= m_Notify["Attack05DmgTiming"] && !m_NotifyDone["Attack05DmgTiming"])
		{
			m_NotifyDone["Attack05DmgTiming"] = true;
			m_Character->AttackEvent();
		}

		if (m_Frame >= m_Notify["Attack05ChgStart"] && m_Frame < m_Notify["Attack05ChgEnd"])
		{
			m_Character->ReadyToAtk();
		}

		if (m_Frame >= m_Notify["Attack05ChgEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);

		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Block::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Block");


}

void PlayerAnimation_Block::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);

		// �ҋ@��Ԃɖ߂�
		m_Character->BlockFinish();
		m_Character->SwordBlock(false);
		// �u���b�N�I���̃A�j���[�V�����ɐ؂�ւ���
		m_AnimationTree->ChangeState<PlayerAnimation_BlockFinish>();
	}

}

void PlayerAnimation_BlockFinish::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("BlockFinish");
	// Block���I���̃^�C�~���O�ݒ�
	m_Notify["BlockFinishTiming"] = 21.0f;
	m_NotifyDone["BlockFinishTiming"] = false;
}

void PlayerAnimation_BlockFinish::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;

		if (m_Frame >= m_Notify["BlockFinishTiming"] && !m_NotifyDone["BlockFinishTiming"])
		{
			m_NotifyDone["BlockFinishTiming"] = true;
			m_Character->ReadyToAtk();
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_BlockCounter::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.5f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("BlockCounter");
}

void PlayerAnimation_BlockCounter::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �u���b�N�I��
		m_Character->BlockFinish();
		m_Character->SwordBlock(false);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Hit::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.65f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Hit");
}

void PlayerAnimation_Hit::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Ult01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Ult01");

	// Ult01�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Ult01SummonTiming"] = 30.0f;
	m_NotifyDone["Ult01SummonTiming"] = false;

	// Ult01�̏I���^�C�~���O�ݒ�
	m_Notify["Ult01FinishTiming"] = 103.0f;
	m_NotifyDone["Ult01FinishTiming"] = false;
}

void PlayerAnimation_Ult01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;

		if (m_Frame >= m_Notify["Ult01SummonTiming"] && !m_NotifyDone["Ult01SummonTiming"])
		{
			m_NotifyDone["Ult01SummonTiming"] = true;
			m_Character->ChangeUltState(5);
		}

		if (m_Frame >= m_Notify["Ult01FinishTiming"] && !m_NotifyDone["Ult01FinishTiming"])
		{
			m_NotifyDone["Ult01FinishTiming"] = true;
			m_Character->ChangeUltState(4);
			m_AnimationTree->ChangeState<PlayerAnimation_Ult0102>();
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}

}

void PlayerAnimation_Ult0102::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Ult0102");

	// Ult0102�̒ʒm�^�C�~���O�ݒ�
	m_Notify["Ult0102SummonTiming"] = 37.0f;
	m_NotifyDone["Ult0102SummonTiming"] = false;
}

void PlayerAnimation_Ult0102::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;

		if (m_Frame >= m_Notify["Ult0102SummonTiming"] && !m_NotifyDone["Ult0102SummonTiming"])
		{
			m_NotifyDone["Ult0102SummonTiming"] = true;
			m_Character->ChangeUltState(7);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_QTEDodge01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("QTEDodge01");

	// QTEDodge01�̃W�����v�^�C�~���O
	m_Notify["QTEDodge01JumpTiming"] = 15.0f;
	m_NotifyDone["QTEDodge01JumpTiming"] = false;
}

void PlayerAnimation_QTEDodge01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;

		if (m_Frame >= m_Notify["QTEDodge01JumpTiming"] && !m_NotifyDone["QTEDodge01JumpTiming"])
		{
			m_NotifyDone["QTEDodge01JumpTiming"] = true;
			RigidBody* _RG = m_Character->GetComponent<RigidBody>();
			_RG->AddForce(D3DXVECTOR3(-1.0f, 0.0f, 0.6f));
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_QTEDodge02::Init()
{	
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("QTEDodge02");

	// QTEDodge02�̃W�����v�^�C�~���O
	m_Notify["QTEDodge02JumpTiming"] = 18.0f;
	m_NotifyDone["QTEDodge02JumpTiming"] = false;
}

void PlayerAnimation_QTEDodge02::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;

		if (m_Frame >= m_Notify["QTEDodge02JumpTiming"] && !m_NotifyDone["QTEDodge02JumpTiming"])
		{
			m_NotifyDone["QTEDodge02JumpTiming"] = true;
			RigidBody* _RG = m_Character->GetComponent<RigidBody>();
			_RG->AddForce(D3DXVECTOR3(1.0f, 0.0f, 0.6f));
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_QTEThrowSword::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("QTEThrowSword");
	
}

void PlayerAnimation_QTEThrowSword::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Dead::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.6f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Dead");
	// �|��鎞��
	m_Notify["DeadStart"] = 50.0f;
	m_Notify["DeadEnd"] = 67.0f;
}

void PlayerAnimation_Dead::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;

		if (m_Frame > m_Notify["DeadStart"] && m_Frame <= m_Notify["DeadEnd"])
		{
			m_Character->SetPosition(D3DXVECTOR3(m_Character->GetPosition().x, m_Character->GetPosition().y - 0.03f, m_Character->GetPosition().z));
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �����鏈�����s��
		m_Character->DeadEvent();
	}
}

void PlayerAnimation_KnockedDown::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 1.0f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("KnockedDown");

}

void PlayerAnimation_KnockedDown::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_GetUp>();
	}
}

void PlayerAnimation_GetUp::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 1.0f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("GetUp");
}

void PlayerAnimation_GetUp::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Dodge::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 1.0f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Dodge");

	// Dodge�̃^�C�~���O
	m_Notify["DodgeTiming"] = 16.0f;
	m_NotifyDone["DodgeTiming"] = false;
}

void PlayerAnimation_Dodge::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// ����^�C�~���O
		if (m_Frame >= m_Notify["DodgeTiming"] && !m_NotifyDone["DodgeTiming"])
		{
			m_NotifyDone["DodgeTiming"] = true;
			m_Character->TimeToDodge();
		}

	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Skill01::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill01");

	// Skill01�̑ł^�C�~���O
	m_Notify["Skill01ShootTiming"] = 60.0f;
	m_NotifyDone["Skill01ShootTiming"] = false;
	m_Notify["Skill01ReadyAtkStart"] = 76.0f;
	m_Notify["Skill01ReadyAtkEnd"] = 93.0f;
}

void PlayerAnimation_Skill01::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O�P�^�C�~���O
		if (m_Frame >= m_Notify["Skill01ShootTiming"] && !m_NotifyDone["Skill01ShootTiming"])
		{
			m_NotifyDone["Skill01ShootTiming"] = true;
			m_Character->ShootAllSword();
		}

		if (m_Frame >= m_Notify["Skill01ReadyAtkStart"] && m_Frame < m_Notify["Skill01ReadyAtkEnd"])
		{
			m_Character->RecoverSword();
			m_Character->ReadyToAtk();
		}

		if (m_Frame >= m_Notify["Skill01ReadyAtkEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}

	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}

}

void PlayerAnimation_Skill02::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill02");

	// Skill02�̑ł^�C�~���O
	m_Notify["Skill02ShootTimingStart"] = 35.0f;
	m_Notify["Skill02ShootTimingEnd"] = 55.0f;

}

void PlayerAnimation_Skill02::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O�Q�^�C�~���O
		if (m_Frame >= m_Notify["Skill02ShootTimingStart"] && m_Frame < m_Notify["Skill02ShootTimingEnd"])
		{
			m_Character->RainSword();
		}

		if (m_Frame >= m_Notify["Skill02ShootTimingEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Skill03::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill03");

	// Skill03�̃`���[�W�^�C�~���O�ƏI���^�C�~���O
	m_Notify["Skill03Charge"] = 18.0f;
	m_NotifyDone["Skill03Charge"] = false;
	m_Notify["Skill03Finish"] = 75.0f;
	m_NotifyDone["Skill03Finish"] = false;
}

void PlayerAnimation_Skill03::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O�R�^�C�~���O
		if (m_Frame >= m_Notify["Skill03Charge"] && !m_NotifyDone["Skill03Charge"])
		{
			m_NotifyDone["Skill03Charge"] = true;
			m_Character->ChargeSword();
		}

		if (m_Frame >= m_Notify["Skill03Finish"] && !m_NotifyDone["Skill03Finish"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Skill04::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill04");

	// Skill04�̑ł���
	m_Notify["Skill04ShootTimingStart"] = 34.0f;
	m_Notify["Skill04ShootTimingEnd"] = 51.0f;
}

void PlayerAnimation_Skill04::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O�S�^�C�~���O
		if (m_Frame >= m_Notify["Skill04ShootTimingStart"] && m_Frame < m_Notify["Skill04ShootTimingEnd"])
		{
			m_Character->SwordMachineGun();
		}
		if (m_Frame >= m_Notify["Skill04ShootTimingEnd"])
		{
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Skill05::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill05");

	// Skill05�̑ł���
	m_Notify["Skill05ShootTiming"] = 27.0f;
	m_NotifyDone["Skill05ShootTiming"] = false;
	// Skill05�̏I������
	m_Notify["Skill05EndTime"] = 53.0f;
	m_NotifyDone["Skill05EndTime"] = false;


}

void PlayerAnimation_Skill05::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O�T�^�C�~���O
		if (m_Frame >= m_Notify["Skill05ShootTiming"] && !m_NotifyDone["Skill05ShootTiming"])
		{
			m_NotifyDone["Skill05ShootTiming"] = true;
			m_Character->RushSword();
		}
		if (m_Frame >= m_Notify["Skill05EndTime"] && !m_NotifyDone["Skill05EndTime"])
		{
			m_NotifyDone["Skill05EndTime"] = true;
			m_Character->PrepareNewSwords();
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Skill06::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 0.8f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill06");

	// Skill06�̑ł���
	m_Notify["Skill06ShootTiming"] = 31.0f;
	m_NotifyDone["Skill06ShootTiming"] = false;

	// Skill06�̏I������
	m_Notify["Skill06EndTiming"] = 85.0f;
	m_NotifyDone["Skill06EndTiming"] = false;
}

void PlayerAnimation_Skill06::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O�U�^�C�~���O
		if (m_Frame >= m_Notify["Skill06ShootTiming"] && !m_NotifyDone["Skill06ShootTiming"])
		{
			m_NotifyDone["Skill06ShootTiming"] = true;
			m_Character->ShootSwordSkill06();
		}
		if (m_Frame >= m_Notify["Skill06EndTiming"] && !m_NotifyDone["Skill06EndTiming"])
		{
			m_NotifyDone["Skill06EndTiming"] = true;
			m_Character->RecoverSword();
			m_Character->AttackCombo(Player::NotAttacking);
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}

}

void PlayerAnimation_Skill07::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 1.0f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill07");

	// Skill07�̑ł���
	m_Notify["Skill07FirstAtk"] = 21.0f;
	m_NotifyDone["Skill07FirstAtk"] = false;

	m_Notify["Skill07SecondAtk"] = 50.0f;
	m_NotifyDone["Skill07SecondAtk"] = false;

	m_Notify["Skill07LastAtk"] = 75.0f;
	m_NotifyDone["Skill07LastAtk"] = false;

	m_Notify["Skill07AtkFinish"] = 92.0f;
	m_NotifyDone["Skill07AtkFinish"] = false;
}

void PlayerAnimation_Skill07::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O7�^�C�~���O
		if (m_Frame >= m_Notify["Skill07FirstAtk"] && !m_NotifyDone["Skill07FirstAtk"])
		{
			m_NotifyDone["Skill07FirstAtk"] = true;
			m_Character->Skill07Combo(1);
		}
		if (m_Frame >= m_Notify["Skill07SecondAtk"] && !m_NotifyDone["Skill07SecondAtk"])
		{
			m_NotifyDone["Skill07SecondAtk"] = true;
			m_Character->Skill07Combo(2);
		}
		if (m_Frame >= m_Notify["Skill07LastAtk"] && !m_NotifyDone["Skill07LastAtk"])
		{
			m_NotifyDone["Skill07LastAtk"] = true;
			m_Character->Skill07Combo(3);
		}
		if (m_Frame >= m_Notify["Skill07AtkFinish"] && !m_NotifyDone["Skill07AtkFinish"])
		{
			m_NotifyDone["Skill07AtkFinish"] = true;
			m_Character->RecoverSword();
			m_Character->AttackCombo(Player::NotAttacking);
			m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
			return;
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}

void PlayerAnimation_Skill08::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 1.0f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill08");

	// Skill08�̑ł���
	m_Notify["Skill08SummonTiming"] = 61.0f;
	m_NotifyDone["Skill08SummonTiming"] = false;

	m_Notify["Skill08EndTime"] = 104.0f;
	m_NotifyDone["Skill08EndTime"] = false;

}

void PlayerAnimation_Skill08::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O7�^�C�~���O
		if (m_Frame >= m_Notify["Skill08SummonTiming"] && !m_NotifyDone["Skill08SummonTiming"])
		{
			m_NotifyDone["Skill08SummonTiming"] = true;
			m_Character->Skill08Combo();
		}
		if (m_Frame >= m_Notify["Skill08EndTime"] && !m_NotifyDone["Skill08EndTime"])
		{
			m_NotifyDone["Skill08EndTime"] = true;
			m_Character->AttackCombo(Player::NotAttacking);
			m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
			return;
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}

}

void PlayerAnimation_Skill09::Init()
{
	// ���[�v���Ă��Ȃ�
	m_Loop = false;
	// �t���[���̏�����
	m_Frame = 0.0f;
	// �v���C���[�g�̏�����
	m_PlayRate = 1.0f;
	// �A�j���[�V�������O�̐ݒu
	m_AnimationTree->SetAnimationName("Skill09");

	// Skill09�̑ł���
	m_Notify["Skill09ShootTiming"] = 46.0f;
	m_NotifyDone["Skill09ShootTiming"] = false;

	m_Notify["Skill09EndTime"] = 80.0f;
	m_NotifyDone["Skill09EndTime"] = false;

}

void PlayerAnimation_Skill09::Update()
{
	// �����ȉ����ƍX�V����
	if (m_Frame < m_AnimationTree->GetDuration())
	{
		// �A�j���[�V�������I�����ĂȂ�
		m_AnimationTree->SetPrevAniFinish(false);

		// �t���[���X�V
		m_Frame += m_PlayRate;
		// �X�L���O7�^�C�~���O
		if (m_Frame >= m_Notify["Skill09ShootTiming"] && !m_NotifyDone["Skill09ShootTiming"])
		{
			m_NotifyDone["Skill09ShootTiming"] = true;
			m_Character->Skill09Combo();
		}
		if (m_Frame >= m_Notify["Skill09EndTime"] && !m_NotifyDone["Skill09EndTime"])
		{
			m_NotifyDone["Skill09EndTime"] = true;
			m_Character->AttackCombo(Player::NotAttacking);
			m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
			return;
		}
	}
	else
	{
		// �A�j���[�V�������I������
		m_AnimationTree->SetPrevAniFinish(true);
		// �ҋ@��Ԃɖ߂�
		m_AnimationTree->ChangeState<PlayerAnimation_Idle>();
	}
}
