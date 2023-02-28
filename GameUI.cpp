#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "GameUI.h"

void GameUI::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(400.0f, 200.0f, 0.0f);

	m_SpriteComponent = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_WaitTime = 2.0f * Manager::Time;

	SetIgnorePause(true);
}

void GameUI::Update()
{
	if (m_Appear)
	{
		if (m_WaitTime < 2.0f * Manager::Time)
		{
			m_WaitTime++;
			float T = m_WaitTime / (2.0f * Manager::Time);
			
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_HidePos, &m_ShowPos, T);

			m_Position = LerpPos;
		}
		else
		{
			m_Position = m_ShowPos;
		}
	}
	else
	{
		if (m_WaitTime < 2.0f * Manager::Time)
		{
			m_WaitTime++;
			float T = m_WaitTime / (2.0f * Manager::Time);

			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_ShowPos, &m_HidePos, T);

			m_Position = LerpPos;
		}
		else
		{
			m_Position = m_HidePos;
		}
	}

	GameObject::Update();
}

void GameUI::LoadInfo(UIType Type)
{
	// UIの種類をセットする
	m_UIType = Type;

	// 種類によってテクスチャも違う
	switch (Type)
	{
	case TutorialPic:
		m_SpriteComponent->LoadInfo("TutorialPic", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case CharacterTutorial:
		m_SpriteComponent->LoadInfo("CharacterTutorialPic", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		break;
	case MoveOrAttack:
		m_SpriteComponent->LoadInfo("MoveOrAttack", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Size = D3DXVECTOR3(400.0f, 50.0f, 0.0f);
		break;
	}

}
