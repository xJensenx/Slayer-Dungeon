#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "MouseCursor.h"
#include "input.h"

bool MouseCursor::m_Visibility = false;

void MouseCursor::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(35.0f, 35.0f, 1.0f);

	// スプライトコンポーネント追加
	m_MouseCursor = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_MouseCursor->LoadInfo("MouseCursor", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

	m_ClickCursor = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClickCursor->LoadInfo("MouseCursorClick", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClickCursor->SetVisibility(false);

}

void MouseCursor::Update()
{
	if (!m_Visibility)
	{
		m_ClickCursor->SetVisibility(false);
		m_MouseCursor->SetVisibility(false);
		return;
	}

	// マウスの座標を更新する
	m_Position.x = Input::GetWindowMousePos().x + 12.5f;
	m_Position.y = Input::GetWindowMousePos().y - 12.5f;

	// 押している間は押しているテクスチャを表示する
	if (Input::GetKeyPress(VK_LBUTTON))
	{
		m_ClickCursor->SetVisibility(true);
		m_MouseCursor->SetVisibility(false);
	}
	else
	{
		m_ClickCursor->SetVisibility(false);
		m_MouseCursor->SetVisibility(true);
	}

	GameObject::Update();
}
