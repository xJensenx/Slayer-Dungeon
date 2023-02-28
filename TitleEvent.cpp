#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "TitleUI.h"

#include "TitleEvent.h"
#include "input.h"
#include "Title.h"

#include "Fade.h"

#include "AudioManager.h"

// 選んでるかどうか
bool g_isChoosing = false;
// 一回だけボタン押せる
bool g_Push = false;

void TitleEvent::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(1400.0f, 200.0f, 0.0f);

	m_ChooseSC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ChooseSC->LoadInfo("Choose", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ChooseSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	m_LockSC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_LockSC->LoadInfo("LockChoose", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_LockSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	m_LockSC->SetVisibility(false);

	// 初期化
	g_isChoosing = false;
	g_Push = false;
}

void TitleEvent::Update()
{
	// シーン情報取得
	Scene* _Scene = Manager::GetScene();
	// タイトルUIの情報を取得
	std::vector<TitleUI*> _TUIList = _Scene->GetGameObjects<TitleUI>();
	// 選んでるUIの種類
	TitleUI::UIType _UIType;
	Title* _T = Manager::GetSceneType<Title>();

	g_isChoosing = false;

	for (auto UI : _TUIList)
	{
		if (UI->GetChosen())
		{
			m_Position = UI->GetPosition();
			m_Size = UI->GetSize();
			m_Size.x *= 2.3f;
			_UIType = UI->GetType();
			g_isChoosing = true;

			if (UI->GetisLock())
			{
				m_LockSC->SetVisibility(true);
				m_ChooseSC->SetVisibility(false);
			}
			else 
			{
				m_LockSC->SetVisibility(false);
				m_ChooseSC->SetVisibility(true);
			}
		}
	}

	if (g_isChoosing && !g_Push)
	{
		if (Input::GetKeyTrigger(VK_LBUTTON) || Input::GetKeyTrigger(VK_RETURN))
		{
			//// SEを鳴らす
			//AudioManager::Play("SEClick", false);

			switch (_UIType)
			{
			case TitleUI::StartGame:
				g_Push = true;
				m_WaitTime = 0.5f * Manager::Time;
				_T->SetNextState(4);
				break;
			case TitleUI::Setting:
				g_Push = true;
				m_WaitTime = 0.5f * Manager::Time;
				_T->SetNextState(5);
				break;
			case TitleUI::QuitGame:
				g_Push = true;
				m_WaitTime = 0.5f * Manager::Time;
				Fade::SetFade<FadeSceneType_Quit>();
				break;
			case TitleUI::BackButton:
				g_Push = true;
				m_WaitTime = 0.5f * Manager::Time;
				_T->SetNextState(3);
				break;
			case TitleUI::StageButton:
				g_Push = true;
				m_WaitTime = 0.5f * Manager::Time;
				_T->SetNextState(4);
				break;
			case TitleUI::TutorialStage:
				g_Push = true;
				m_WaitTime = 5.0f * Manager::Time;
				_T->SetNextState(4);
				break;
			case TitleUI::Stage01:
				g_Push = true;
				m_WaitTime = 5.0f * Manager::Time;
				_T->SetNextState(6);
				break;
			case TitleUI::SkillButton:
				g_Push = true;
				m_WaitTime = 0.5f * Manager::Time;
				_T->SetNextState(5);
				break;
			case TitleUI::Skill01:
				_T->SetNextState(4);
				break;
			case TitleUI::Skill02:
				_T->SetNextState(5);
				break;
			case TitleUI::Skill03:
				_T->SetNextState(6);
				break;
			}
		}
	}
	else
	{
		m_Position = D3DXVECTOR3(-700.0f, m_Position.y, 0.0f);
	}
	

	if (m_WaitTime > 0.0f)
	{
		m_WaitTime--;
	}
	else
	{
		g_Push = false;
	}

	GameObject::Update();
}
