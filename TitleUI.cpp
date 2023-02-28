#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "TitleUI.h"
#include "TitleSkillUI.h"
#include "TitleSkillUIType.h"
#include "Number.h"

void TitleUI::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(600.0f, 200.0f, 0.0f);
	m_MoveTime = 1.5f * Manager::Time;
	m_CantChoose = false;
}

void TitleUI::Update()
{
	if (m_Appear)
	{
		// 選択されていると選択されているのテクスチャだけ表示
		// 選択されていないと選択されていないのテクスチャだけ表示
		if (m_Chosen)
		{
			m_NSSprite->SetVisibility(false);
			m_Sprite->SetVisibility(true);
		}
		else
		{
			m_NSSprite->SetVisibility(true);
			m_Sprite->SetVisibility(false);
		}

		if (m_MoveTime < m_TotalMoveTime)
		{
			m_MoveTime++;
			float T = m_MoveTime / (m_TotalMoveTime);
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_HidePos, &m_ScreenPos, T);

			m_Position = LerpPos;
		}
		else
		{
			m_Position = m_ScreenPos;
		}
	}
	else
	{
		if (m_MoveTime < m_TotalMoveTime)
		{
			m_MoveTime++;
			float T = m_MoveTime / (m_TotalMoveTime);
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_ScreenPos, &m_HidePos, T);

			m_Position = LerpPos;
		}
		else
		{
			m_Position = m_HidePos;
		}
	}

	if (m_ShowSkill != NULL)
	{
		int SkillNum;

		switch (m_UIType)
		{
		case Skill01:
			SkillNum = (int)Manager::GetSkillType(0);
			break;
		case Skill02:
			SkillNum = (int)Manager::GetSkillType(1);
			break;
		case Skill03:
			SkillNum = (int)Manager::GetSkillType(2);
			break;
		}

		if (m_SkillNumber != SkillNum)
		{
			switch (SkillNum)
			{
			case 1:
				m_ShowSkill->SetSkillType<TitleSkillUISkill01>();
				break;
			case 2:
				m_ShowSkill->SetSkillType<TitleSkillUISkill02>();
				break;
			case 3:
				m_ShowSkill->SetSkillType<TitleSkillUISkill03>();
				break;
			case 4:
				m_ShowSkill->SetSkillType<TitleSkillUISkill04>();
				break;
			case 5:
				m_ShowSkill->SetSkillType<TitleSkillUISkill05>();
				break;
			case 6:
				m_ShowSkill->SetSkillType<TitleSkillUISkill06>();
				break;
			case 7:
				m_ShowSkill->SetSkillType<TitleSkillUISkill07>();
				break;
			case 8:
				m_ShowSkill->SetSkillType<TitleSkillUISkill08>();
				break;
			case 9:
				m_ShowSkill->SetSkillType<TitleSkillUISkill09>();
				break;
			}

			m_SkillNumber = SkillNum;
		}
	}


	GameObject::Update();
}

void TitleUI::LoadInfo(UIType UIType)
{
	m_UIType = UIType;

	m_NSSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->SetVisibility(false);
	
	switch (m_UIType)
	{
	case StartGame:
		m_NSSprite->LoadInfo("StartGameNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("StartGame", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case Setting:
		m_NSSprite->LoadInfo("SettingNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("Setting", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case QuitGame:
		m_NSSprite->LoadInfo("QuitGameNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("QuitGame", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case StageButton:
		m_NSSprite->LoadInfo("UIStageNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("UIStage", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case StatusButton:
		m_NSSprite->LoadInfo("UIStatusNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("UIStatus", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_isLock = true;
		break;
	case SkillButton:
		m_NSSprite->LoadInfo("UISkillsNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("UISkills", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case TutorialStage:
		m_NSSprite->LoadInfo("UITutorialStageNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("UITutorialStage", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Size = D3DXVECTOR3(500.0f, 150.0f, 0.0f);
		break;
	case Stage01:
		m_NSSprite->LoadInfo("UIStage01NS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("UIStage01", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Size = D3DXVECTOR3(500.0f, 150.0f, 0.0f);
		break;
	case LockStage:
		m_NSSprite->LoadInfo("UILockStageNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->LoadInfo("UILockStage", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_isLock = true;
		m_Size = D3DXVECTOR3(500.0f, 150.0f, 0.0f);
		break;
	case ChooseFile:
		m_Sprite->LoadInfo("UIChooseFile", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UIChooseFile", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		m_Size = D3DXVECTOR3(350.0f, 125.0f, 0.0f);
		m_CantChoose = true;
		break;
	case ModeSelect:
		m_Sprite->LoadInfo("UIModeSelect", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UIModeSelect", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		m_Size = D3DXVECTOR3(350.0f, 125.0f, 0.0f);
		m_CantChoose = true;
		break;
	case StageSelect:
		m_Sprite->LoadInfo("UIStageSelect", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UIStageSelect", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		m_Size = D3DXVECTOR3(350.0f, 125.0f, 0.0f);
		m_CantChoose = true;
		break;
	case BackButton:
		m_Sprite->LoadInfo("UIBackButton", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UIBackButton", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		m_Size = D3DXVECTOR3(150.0f, 75.0f, 0.0f);
		break;
	case Skill01:
		m_Sprite->LoadInfo("UISkill01", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UISkill01NS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		// 装備しているスキルを表示する
		m_SkillNumber = 1;
		m_ShowSkill = AddChild<TitleSkillUI>();
		m_ShowSkill->SetLocalPos(D3DXVECTOR3(250.0f, 0.0f, 0.0f));
		m_ShowSkill->SetSkillType<TitleSkillUISkill01>();

		break;
	case Skill02:
		m_Sprite->LoadInfo("UISkill02", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UISkill02NS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		// 装備しているスキルを表示する
		m_SkillNumber = 2;
		m_ShowSkill = AddChild<TitleSkillUI>();
		m_ShowSkill->SetLocalPos(D3DXVECTOR3(250.0f, 0.0f, 0.0f));
		m_ShowSkill->SetSkillType<TitleSkillUISkill02>();
		break;
	case Skill03:
		m_Sprite->LoadInfo("UISkill03", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->LoadInfo("UISkill03NS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_NSSprite->SetVisibility(false);
		// 装備しているスキルを表示する
		m_SkillNumber = 3;
		m_ShowSkill = AddChild<TitleSkillUI>();
		m_ShowSkill->SetLocalPos(D3DXVECTOR3(250.0f, 0.0f, 0.0f));
		m_ShowSkill->SetSkillType<TitleSkillUISkill03>();

		break;
	}
}

D3DXVECTOR3 TitleUI::GetWorldPosition()
{
	D3DXVECTOR3 WorldPos;

	WorldPos = D3DXVECTOR3(-SCREEN_WIDTH / 2 + m_Position.x, -SCREEN_HEIGHT / 2 + m_Position.y, 0.0f);

	return WorldPos;
}

void TitleUI::SetSkillPointNum(int Num)
{
	if (m_SkillPoint == NULL) return;

	m_SkillPoint->SetNumber(Num);
}
