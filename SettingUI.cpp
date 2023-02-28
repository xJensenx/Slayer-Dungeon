#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "SettingUI.h"

void SettingUI::Init()
{
	// èâä˙âª
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(500.0f, 150.0f, 0.0f);

	m_Appear = false;
	m_MoveTime = 1.0f * Manager::Time;
}

void SettingUI::Uninit()
{
	if (m_UIType != NULL)
	{
		delete m_UIType;
		m_UIType = NULL;
	}

	GameObject::Uninit();
}

void SettingUI::Update()
{
	if (m_Appear)
	{
		if (m_MoveTime < 0.5f * Manager::Time)
		{
			m_MoveTime++;
			float T = m_MoveTime / (0.5f * Manager::Time);
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
		if (m_MoveTime < 0.5f * Manager::Time)
		{
			m_MoveTime++;
			float T = m_MoveTime / (0.5f * Manager::Time);
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_ScreenPos, &m_HidePos, T);

			m_Position = LerpPos;
		}
		else
		{
			m_Position = m_HidePos;
		}
	}

	m_UIType->Update();

	GameObject::Update();
}
