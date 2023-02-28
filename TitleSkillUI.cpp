#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "TitleSkillUI.h"
#include "TitleSkillUIType.h"

void TitleSkillUI::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(100.0f, 50.0f, 0.0f);

	// スプライト追加
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->SetSpriteType(SpriteComponent::None);
	m_SpriteNS = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_SpriteNS->SetSpriteType(SpriteComponent::None);

	m_Chosen = false;
	m_JustForShow = false;
	m_Hiding = false;
}

void TitleSkillUI::Update()
{
	if (m_Hiding)
	{
		m_Sprite->SetVisibility(false);
		m_SpriteNS->SetVisibility(false);
		return;
	}

	if (!m_JustForShow)
	{
		m_SkillType->Update();
	}

	GameObject::Update();
}

void TitleSkillUI::ClickSkillEvent()
{
	m_SkillType->Activate();
}
