#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "PlayerStatusWarning.h"
#include "Math.h"

void PlayerStatusWarning::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// スプライト追加
	m_DmgTakenSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_DmgTakenSprite->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f));
	m_DmgTakenSprite->LoadInfo("PlayerDmgTaken", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_DmgTakenSprite->SetVisibility(false);

	m_BlockSprite = AddComponent<SpriteComponent>(GameObject::SecondPri);
	m_BlockSprite->LoadInfo("PlayerBlockSuccess", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_BlockSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f));
	m_BlockSprite->SetVisibility(false);

	// 初期化
	m_DmgTime = 0.0f;
	m_isDmg = false;
	m_DmgState = 0;
}

void PlayerStatusWarning::Update()
{

	// ダメージ受けた時の処理
	if (m_isDmg)
	{
		switch (m_DmgState)
		{
		case 0:
			if (m_DmgTime < (0.2f * Manager::Time))
			{
				m_DmgTime++;
				
				float T = m_DmgTime / (0.2f * Manager::Time);

				float Alpha = Math::FloatLerp(0.0f, 0.4f, T);
				m_DmgTakenSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, Alpha));
			}
			else
			{
				m_DmgState = 1;
				m_DmgTime = 0.0f;
			}
			break;
		case 1:
			if (m_DmgTime < (2.0f * Manager::Time))
			{
				m_DmgTime++;

				float T = m_DmgTime / (2.0f * Manager::Time);

				float Alpha = Math::FloatLerp(0.4f, 0.0f, T);
				m_DmgTakenSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, Alpha));
			}
			else
			{
				m_DmgState = 0;
				m_DmgTime = 0.0f;
				m_isDmg = false;
				m_DmgTakenSprite->SetVisibility(false);
			}
			break;
		}
	}

	GameObject::Update();
}

void PlayerStatusWarning::DmgTaken()
{
	m_DmgTime = 0.0f;
	m_isDmg = true;

	m_DmgState = 0;
	m_DmgTakenSprite->SetVisibility(true);
	m_DmgTakenSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f));
}
