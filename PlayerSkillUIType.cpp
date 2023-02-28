#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PlayerSkillUI.h"
#include "PlayerSkillUIType.h"

void PlayerSkill01UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill01GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill01GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);
}

void PlayerSkill02UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill02GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill02GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}

void PlayerSkill03UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill03GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill03GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}

void PlayerSkill04UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill04GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill04GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}

void PlayerSkill05UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill05GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill05GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);


}

void PlayerSkill06UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill06GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill06GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}

void PlayerSkill07UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill07GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill07GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}

void PlayerSkill08UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill08GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill08GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}

void PlayerSkill09UI::Init()
{
	SpriteComponent* _Full = m_Skill->GetFullSprite();
	SpriteComponent* _No = m_Skill->GetNoSprite();

	_Full->LoadInfo("PlayerSkill09GameUI", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	_Full->SetSpriteType(SpriteComponent::ProgressBar);
	_Full->SetNormalTexture("HpBarNoise");

	_No->LoadInfo("PlayerSkill09GameUIEmpty", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_No->SetSpriteType(SpriteComponent::ProgressBar);

}
