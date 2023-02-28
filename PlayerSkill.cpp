#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Player.h"
#include "PlayerAnimation.h"
#include "PlayerSkill.h"
#include "PlayerMpBar.h"
#include "AudioManager.h"
#include "Tutorial.h"

void PlayerShootAllSword::Init()
{

}

void PlayerShootAllSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 20.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 20.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill01>();
	}
}

void PlayerShootFromSky::Init()
{
}

void PlayerShootFromSky::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 30.0f) 
	{
		AudioManager::PlaySE("SEActivateFail"); 
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 30.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill02>();
	}
}

void PlayerChargeShoot::Init()
{
}

void PlayerChargeShoot::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 25.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 25.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill03>();
	}
}

void PlayerSwordMachineGun::Init()
{
}

void PlayerSwordMachineGun::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 50.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 50.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill04>();
	}
}

void PlayerRushSword::Init()
{
}

void PlayerRushSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 20.0f) 
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitRotCamSkill())
	{
		// Mp�����炷
		CurMp -= 20.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill05>();
	}

}

void PlayerShootMultipleTimeSword::Init()
{
}

void PlayerShootMultipleTimeSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 50.0f) 
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 50.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill06>();
	}

}

void PlayerSkillAttackCombo::Init()
{
}

void PlayerSkillAttackCombo::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 50.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 50.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// ���G���Ԃ�ݒu
		m_Character->SetInvulTime(1.2f);

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill07>();
	}

}

void PlayerSkillShootAtOnce::Init()
{
}

void PlayerSkillShootAtOnce::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 40.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 40.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill08>();
	}

}

void PlayerSummonBigSword::Init()
{
}

void PlayerSummonBigSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mp������Ȃ��ꍇ��return����
	if (CurMp < 30.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// ����������true��Ԃ��ƃX�L���𔭓�����
	if (m_Character->InitSkill())
	{
		// Mp�����炷
		CurMp -= 30.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// �N�[���_�E���t����
		m_Character->SetCoolDown(Slot);

		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mp���Z�b�g
		m_Character->SetCurMp(CurMp);

		// �A�j���[�V�����؂�ւ���
		m_Animation->ChangeState<PlayerAnimation_Skill09>();
	}

}
