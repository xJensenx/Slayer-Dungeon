#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "TitleSkillUIEvent.h"
#include "TitleSkillUI.h"
#include "input.h"

void TitleSkillUIEvent::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
	
	// スプライト追加
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("UISkillChoose", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
}

void TitleSkillUIEvent::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	std::vector<TitleSkillUI*> _SkillUI = _Scene->GetGameObjects<TitleSkillUI>();

	TitleSkillUI* _ChooseSkillUI = NULL;
	bool GetChoose = false;
	D3DXVECTOR3 AdjustPos;

	for (auto S : _SkillUI)
	{
		if (S->GetChosen())
		{
			GetChoose = true;
			AdjustPos = S->GetPosition();
			_ChooseSkillUI = S;
			break;
		}
	}

	if (GetChoose)
	{
		m_Sprite->SetVisibility(true);
		m_Position = AdjustPos;
		if (Input::GetKeyTrigger(VK_LBUTTON))
		{
			if(_ChooseSkillUI != NULL) _ChooseSkillUI->ClickSkillEvent();
		}
	}
	else
	{
		m_Sprite->SetVisibility(false);
	}
}
