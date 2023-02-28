#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "PlayerHpBar.h"
#include "Player.h"

SpriteComponent* g_PlayerFullHpBar;

void PlayerHpBar::Init()
{
	// ������
	m_Position = D3DXVECTOR3(10.0f, SCREEN_HEIGHT - 90.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(400.0f, 40.0f, 0.0f);

	// �X�v���C�g�R���|�[�l���g
	SpriteComponent* NoHpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	NoHpBar->SetSpriteType(SpriteComponent::ProgressBar);
	NoHpBar->LoadInfo("PlayerNoHp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	g_PlayerFullHpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	g_PlayerFullHpBar->SetSpriteType(SpriteComponent::ProgressBar);
	g_PlayerFullHpBar->LoadInfo("PlayerFullHp", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	g_PlayerFullHpBar->SetNormalTexture("HpBarNoise");

	// ProgressBar��ǉ�����
	ProgressBar* _PB = AddComponent<ProgressBar>(GameObject::ThirdPri);
	_PB->SetProgressBar(NoHpBar, g_PlayerFullHpBar);
}

void PlayerHpBar::Update()
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

		float FullHpOffSetX = m_Size.x * (_PB->GetProgressValue() - 1.0f);

		g_PlayerFullHpBar->SetSizeOffset(D3DXVECTOR3(FullHpOffSetX, 0.0f, 0.0f));

		// �v���C���[�̍ő�Hp
		float FullHp = m_Character->GetMaxHp();
		// �v���C���[�̌���Hp
		float CurHp = m_Character->GetCurHp();

		// ProgressBar���X�V����
		_PB->SetMaxValue(FullHp);
		_PB->SetCurrentValue(CurHp);
	}

	GameObject::Update();
}
