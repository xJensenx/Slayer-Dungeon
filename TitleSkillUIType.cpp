#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "TitleSkillUI.h"
#include "TitleSkillUIType.h"
#include "Title.h"

void TitleSkillUISkill01::Init()
{
	m_Sprite->LoadInfo("UISkill01Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill01CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill01::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill01);
}

void TitleSkillUISkill02::Init()
{
	m_Sprite->LoadInfo("UISkill02Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill02CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill02::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill02);
}

void TitleSkillUISkill03::Init()
{
	m_Sprite->LoadInfo("UISkill03Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill03CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill03::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill03);
}

void TitleSkillUIType::Update()
{
	bool _Chosen = m_SkillUI->GetChosen();

	if (_Chosen)
	{
		m_Sprite->SetVisibility(true);
		m_SpriteNS->SetVisibility(false);
	}
	else
	{
		m_Sprite->SetVisibility(false);
		m_SpriteNS->SetVisibility(true);
	}
}

void TitleSkillUISkill04::Init()
{
	m_Sprite->LoadInfo("UISkill04Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill04CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

}

void TitleSkillUISkill04::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill04);

}

void TitleSkillUISkill05::Init()
{
	m_Sprite->LoadInfo("UISkill05Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill05CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill05::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill05);
}

void TitleSkillUISkill06::Init()
{
	m_Sprite->LoadInfo("UISkill06Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill06CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill06::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill06);
}

void TitleSkillUISkill07::Init()
{
	m_Sprite->LoadInfo("UISkill07Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill07CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill07::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill07);
}

void TitleSkillUISkill08::Init()
{
	m_Sprite->LoadInfo("UISkill08Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill08CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill08::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill08);
}

void TitleSkillUISkill09::Init()
{
	m_Sprite->LoadInfo("UISkill09Custom", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_SpriteNS->LoadInfo("UISkill09CustomNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TitleSkillUISkill09::Activate()
{
	Title* _T = Manager::GetSceneType<Title>();

	int Num = _T->GetSkillSlotNumber();

	Manager::SetSkillType(Num, Manager::Skill09);
}
