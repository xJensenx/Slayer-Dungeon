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
	// Mpが足りない場合はreturnする
	if (CurMp < 20.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 20.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill01>();
	}
}

void PlayerShootFromSky::Init()
{
}

void PlayerShootFromSky::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 30.0f) 
	{
		AudioManager::PlaySE("SEActivateFail"); 
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 30.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill02>();
	}
}

void PlayerChargeShoot::Init()
{
}

void PlayerChargeShoot::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 25.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 25.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill03>();
	}
}

void PlayerSwordMachineGun::Init()
{
}

void PlayerSwordMachineGun::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 50.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 50.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill04>();
	}
}

void PlayerRushSword::Init()
{
}

void PlayerRushSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 20.0f) 
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}

	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitRotCamSkill())
	{
		// Mpを減らす
		CurMp -= 20.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill05>();
	}

}

void PlayerShootMultipleTimeSword::Init()
{
}

void PlayerShootMultipleTimeSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 50.0f) 
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 50.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill06>();
	}

}

void PlayerSkillAttackCombo::Init()
{
}

void PlayerSkillAttackCombo::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 50.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 50.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// 無敵時間を設置
		m_Character->SetInvulTime(1.2f);

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill07>();
	}

}

void PlayerSkillShootAtOnce::Init()
{
}

void PlayerSkillShootAtOnce::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 40.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 40.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill08>();
	}

}

void PlayerSummonBigSword::Init()
{
}

void PlayerSummonBigSword::Activate(int Slot)
{
	float CurMp = m_Character->GetCurMp();
	// Mpが足りない場合はreturnする
	if (CurMp < 30.0f)
	{
		AudioManager::PlaySE("SEActivateFail");
		m_Character->GetMpBar()->SetInsufficient();
		return;
	}


	// 準備がもしtrueを返すとスキルを発動する
	if (m_Character->InitSkill())
	{
		// Mpを減らす
		CurMp -= 30.0f;
		if (CurMp <= 0.0f) CurMp = 0.0f;

		// クールダウン付ける
		m_Character->SetCoolDown(Slot);

		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission05>())
			{
				_Tutorial->SetPushButton(Slot);
			}
		}

		// Mpをセット
		m_Character->SetCurMp(CurMp);

		// アニメーション切り替える
		m_Animation->ChangeState<PlayerAnimation_Skill09>();
	}

}
