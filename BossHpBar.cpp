#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "Boss.h"
#include "BossHpBar.h"

SpriteComponent* g_BossFullHpBar;

void BossHpBar::Init()
{
	m_Position = D3DXVECTOR3(200.0f, 20.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(1200.0f,50.0f, 0.0f);

	// スプライトコンポーネント
	SpriteComponent* NoHpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	NoHpBar->SetSpriteType(SpriteComponent::ProgressBar);
	NoHpBar->LoadInfo("BossNoHp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	g_BossFullHpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	g_BossFullHpBar->SetSpriteType(SpriteComponent::ProgressBar);
	g_BossFullHpBar->LoadInfo("BossFullHp", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	g_BossFullHpBar->SetNormalTexture("HpBarNoise");
	g_BossFullHpBar->SetSizeOffset(D3DXVECTOR3(-20.0f, -20.0f, 0.0f));
	g_BossFullHpBar->SetOffSet(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	// ProgressBarを追加する
	ProgressBar* _PB = AddComponent<ProgressBar>(GameObject::ThirdPri);
	_PB->SetProgressBar(NoHpBar, g_BossFullHpBar);

}

void BossHpBar::Update()
{
	if (m_Character != NULL)
	{
		// ProgressBarに自分のHpや最大Hpを更新する
		ProgressBar* _PB = GetComponent<ProgressBar>();

		float FullHpOffSetX = m_Size.x * (_PB->GetProgressValue() - 1.0f) - 20.0f;

		g_BossFullHpBar->SetSizeOffset(D3DXVECTOR3(FullHpOffSetX, -20.0f, 0.0f));

		// Minionの最大Hp
		float FullHp = m_Character->GetMaxHp();
		// Minionの現在Hp
		float CurHp = m_Character->GetCurHp();

		// ProgressBarを更新する
		_PB->SetMaxValue(FullHp);
		_PB->SetCurrentValue(CurHp);
	}
	else
	{
		SetDestroy();
		return;
	}


	GameObject::Update();
}
