#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PlayerDpBar.h"
#include "Player.h"

void PlayerDpBar::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(10.0f, SCREEN_HEIGHT - 130.0f, 0.0f);
	m_Size = D3DXVECTOR3(400.0f, 40.0f, 0.0f);

	// フルバーのスプライト
	m_FullSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_FullSprite->LoadInfo("PlayerFullDp", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	m_FullSprite->SetSpriteType(SpriteComponent::ProgressBar);
	m_FullSprite->SetNormalTexture("HpBarNoise");

	m_NoSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NoSprite->LoadInfo("PlayerNoDp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_NoSprite->SetSpriteType(SpriteComponent::ProgressBar);

	// ProgressBarを追加する
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

		// ProgressBarに自分のHpや最大Hpを更新する
		ProgressBar* _PB = GetComponent<ProgressBar>();

		float FullDpOffSetX = m_Size.x * (_PB->GetProgressValue() - 1.0f);

		m_FullSprite->SetSizeOffset(D3DXVECTOR3(FullDpOffSetX, 0.0f, 0.0f));

		// プレイヤーの最大Mp
		float FullDp = m_Character->GetMaxDp();
		// プレイヤーの現在Mp
		float CurDp = m_Character->GetCurDp();

		// ProgressBarを更新する
		_PB->SetMaxValue(FullDp);
		_PB->SetCurrentValue(CurDp);
	}

	GameObject::Update();
}
