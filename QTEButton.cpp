#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "QTEButton.h"
#include "Math.h"

void QTEButton::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	m_State = 0;
	m_CurTime = 0.0f;

	// スプライト追加
	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("PlayerQTEButton", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void QTEButton::Update()
{

	// アニメーション
	switch (m_State)
	{
	case 0:
		if (m_CurTime < 0.2f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			m_State = 1;
		}
		break;
	case 1:
		if (m_CurTime > 0.0f)
		{
			m_CurTime--;
		}
		else
		{
			m_State = 0;
		}
		break;
	}

	float T = m_CurTime / (0.2f * Manager::Time);

	float ChgAmt = 50.0f;

	m_Size.x = 200.0f + Math::FloatLerp(0.0f, ChgAmt, T);
	m_Size.y = 200.0f + Math::FloatLerp(0.0f, ChgAmt, T);

	GameObject::Update();
}
