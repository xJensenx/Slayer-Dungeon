#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "LoadingLogo.h"

void LoadingLogo::Init()
{
	m_Size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	m_Position = D3DXVECTOR3(SCREEN_WIDTH - 50.0f, SCREEN_HEIGHT - 50.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("LoadingLogo", "Unlit", D3DXVECTOR2(0.2f, 0.1666666666666667f));
	
	m_Cnt = 0;
}

void LoadingLogo::Update()
{
	SpriteComponent* _SC = GetComponent<SpriteComponent>();

	m_Cnt++;
	if (m_Cnt > 5 * 6)
	{
		m_Cnt = 0;
	}
	// テキスチャー座標算出
	float x = m_Cnt % 5 * (1.0f / 5);
	float y = m_Cnt / 6 * (1.0f / 6);
	_SC->SetTexCoord(D3DXVECTOR2(x, y));

	GameObject::Update();
}
