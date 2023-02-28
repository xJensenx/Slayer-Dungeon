#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PauseMenuUI.h"
#include "PhysicsCast.h"
#include "input.h"

void PauseMenuUI::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(500.0f, 100.0f, 0.0f);

	// スプライト追加
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NSSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);

	m_Chosen = false;
}

void PauseMenuUI::Update()
{
	// 選ばれている状態
	if (m_Chosen)
	{
		m_Sprite->SetVisibility(true);
		m_NSSprite->SetVisibility(false);

		// 左クリックすれば
		if (Input::GetKeyTrigger(VK_LBUTTON))
		{
			// 種類によって処理が変わる
			m_UIType->Press();
		}
	}
	else
	{
		m_Sprite->SetVisibility(false);
		m_NSSprite->SetVisibility(true);
	}

	GameObject::Update();
}
