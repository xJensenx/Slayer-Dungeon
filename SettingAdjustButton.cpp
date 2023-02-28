#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "SettingUI.h"
#include "SettingAdjustButton.h"
#include "PhysicsCast.h"
#include "input.h"
#include "Math.h"

void SettingAdjustButton::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(20.0f, 50.0f, 0.0f);

	// スプライト追加
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("UIAdjustButton", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_NSSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NSSprite->LoadInfo("UIAdjustButtonNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

	// 値の初期化
	m_Value = 0.0f;
}

void SettingAdjustButton::Update()
{
	// 選択されているとテクスチャが変わる
	if (m_Chosen)
	{
		m_Sprite->SetVisibility(true);
		m_NSSprite->SetVisibility(false);
	}
	else
	{
		if (m_isClick)
		{
			m_Sprite->SetVisibility(true);
			m_NSSprite->SetVisibility(false);
		}
		else
		{
			m_Sprite->SetVisibility(false);
			m_NSSprite->SetVisibility(true);
		}
	}

	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		if (m_Chosen)
		{
			m_isClick = true;
		}
	}

	if (Input::GetKeyRelease(VK_LBUTTON))
	{
		m_isClick = false;
	}

	// 移動処理
	if (m_isClick)
	{
		// マウスのXを取得
		float MousePosX = Input::GetWindowMousePos().x;
		// 値を求める
		m_Value = Math::GetLerpTime(m_InitPos.x, m_TarPos.x, MousePosX);
	}

	// ０以上や１以下を制限する
	if (m_Value < 0.0f)
	{
		m_Value = 0.0f;
	}
	if (m_Value > 1.0f)
	{
		m_Value = 1.0f;
	}

	// 線形補間用
	D3DXVECTOR3 LerpPos;
	// 線形補間
	D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_TarPos, m_Value);
	// 座標設置
	m_Position = LerpPos;

	GameObject::Update();
}
