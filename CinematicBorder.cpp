#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "CinematicBorder.h"

void CinematicBorder::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 16, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 8, 0.0f);
	m_CurTime = 0.0f;

	// ボーダーのテクスチャ設定
	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("CinematicBorder", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

}

void CinematicBorder::Update()
{
	// カットシーン中
	if (m_Cinematic)
	{
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;
			float T = m_CurTime / m_TotalTime;
			D3DXVECTOR3 LerpPos;
			switch (m_PosType)
			{
			case Top:
				D3DXVec3Lerp(&LerpPos, &m_TopHidePos, &m_TopPosition, T);
				m_Position = LerpPos;
				break;
			case Bot:
				D3DXVec3Lerp(&LerpPos, &m_BotHidePos, &m_BotPosition, T);
				m_Position = LerpPos;
				break;
			}
		}
	}
	else
	{
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;
			float T = m_CurTime / m_TotalTime;
			D3DXVECTOR3 LerpPos;
			switch (m_PosType)
			{
			case Top:
				D3DXVec3Lerp(&LerpPos, &m_TopPosition, &m_TopHidePos, T);
				m_Position = LerpPos;
				break;
			case Bot:
				D3DXVec3Lerp(&LerpPos, &m_BotPosition, &m_BotHidePos, T);
				m_Position = LerpPos;
				break;
			}
		}
	}

	GameObject::Update();
}

void CinematicBorder::SetPosType(PositionType PT)
{
	m_PosType = PT;
	
	// スクリーン外に置く
	switch (m_PosType)
	{
	case Top:
		m_Position = m_TopHidePos;
		break;
	case Bot:
		m_Position = m_BotHidePos;
		break;
	}

}
