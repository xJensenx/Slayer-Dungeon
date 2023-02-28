#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PlayerDpBar.h"
#include "Player.h"

void PlayerDpBar::Init()
{
	// ������
	m_Position = D3DXVECTOR3(10.0f, SCREEN_HEIGHT - 130.0f, 0.0f);
	m_Size = D3DXVECTOR3(400.0f, 40.0f, 0.0f);

	// �t���o�[�̃X�v���C�g
	m_FullSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_FullSprite->LoadInfo("PlayerFullDp", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	m_FullSprite->SetSpriteType(SpriteComponent::ProgressBar);
	m_FullSprite->SetNormalTexture("HpBarNoise");

	m_NoSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NoSprite->LoadInfo("PlayerNoDp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_NoSprite->SetSpriteType(SpriteComponent::ProgressBar);

	// ProgressBar��ǉ�����
	ProgressBar* _PB = AddComponent<ProgressBar>(GameObject::ThirdPri);
	_PB->SetProgressBar(m_NoSprite, m_FullSprite);
}

void PlayerDpBar::Update()
{
	if (m_Character != NULL)
	{
		if (m_Character->GetDestroy())
		{
			SetDestroy();
			return;
		}

		// ProgressBar�Ɏ�����Hp��ő�Hp���X�V����
		ProgressBar* _PB = GetComponent<ProgressBar>();

		float FullDpOffSetX = m_Size.x * (_PB->GetProgressValue() - 1.0f);

		m_FullSprite->SetSizeOffset(D3DXVECTOR3(FullDpOffSetX, 0.0f, 0.0f));

		// �v���C���[�̍ő�Mp
		float FullDp = m_Character->GetMaxDp();
		// �v���C���[�̌���Mp
		float CurDp = m_Character->GetCurDp();

		// ProgressBar���X�V����
		_PB->SetMaxValue(FullDp);
		_PB->SetCurrentValue(CurDp);
	}

	GameObject::Update();
}
