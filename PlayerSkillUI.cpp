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

	// �X�v���C�g�ǉ�
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

		// Mp�������̎g��Mp�ʂ�菭�Ȃ��ꍇ
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

		// ProgressBar�Ɏ�����Hp��ő�Hp���X�V����
		ProgressBar* _PB = GetComponent<ProgressBar>();

		float OffSetY = m_Size.y * (_PB->GetProgressValue() - 1.0f);

		m_NoSprite->SetSizeOffset(D3DXVECTOR3(0.0f,OffSetY, 0.0f));

		// �v���C���[�̍ő�CD
		float MaxCD = m_Character->GetMaxCooldown(m_Slot);
		// �v���C���[�̌���CD
		float CurCD = m_Character->GetCurCooldown(m_Slot);

		// ProgressBar���X�V����
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
