#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PlayerSkillUI.h"
#include "PlayerSkillUIType.h"
#include "Player.h"
#include "Number.h"

void PlayerSkillUI::Init()
{
	m_Position = D3DXVECTOR3(-500.0f, -500.0f, 0.0f);
	m_Size = D3DXVECTOR3(75.0f, 75.0f, 0.0f);

	// スプライト追加
	m_FullSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NoSprite = AddComponent<SpriteComponent>(GameObject::SecondPri);

	ProgressBar* _PB = AddComponent<ProgressBar>(GameObject::ThirdPri);
	_PB->SetProgressBar(m_FullSprite, m_NoSprite);
	_PB->SetProgressType(ProgressBar::DownToTop);
}

void PlayerSkillUI::Update()
{
	if (m_Character != NULL)
	{
		if (m_Character->GetDestroy())
		{
			SetDestroy();
			return;
		}

		// Mpが自分の使うMp量より少ない場合
		if (m_Character->GetCurMp() < m_UseMp)
		{
			m_FullSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f));
			m_NoSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f));
		}
		else
		{
			m_FullSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			m_NoSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// ProgressBarに自分のHpや最大Hpを更新する
		ProgressBar* _PB = GetComponent<ProgressBar>();

		float OffSetY = m_Size.y * (_PB->GetProgressValue() - 1.0f);

		m_NoSprite->SetSizeOffset(D3DXVECTOR3(0.0f,OffSetY, 0.0f));

		// プレイヤーの最大CD
		float MaxCD = m_Character->GetMaxCooldown(m_Slot);
		// プレイヤーの現在CD
		float CurCD = m_Character->GetCurCooldown(m_Slot);

		// ProgressBarを更新する
		_PB->SetMaxValue(MaxCD);
		_PB->SetCurrentValue(CurCD);
	}



	GameObject::Update();
}

void PlayerSkillUI::SetSlot(int Slot)
{

	m_Slot = Slot;

	Number* _Num = AddChild<Number>();

	_Num->SetLocalPos(D3DXVECTOR3(10.0f, 80.0f, 0.0f));
	_Num->SetNumber(m_Slot + 1);
}
