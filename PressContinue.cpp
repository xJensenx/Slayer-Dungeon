#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "PressContinue.h"
#include "Math.h"

SpriteComponent* _ContinueSC;
SpriteComponent* ChooseSC;

void PressContinue::Init()
{
	m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(400.0f, 40.0f, 0.0f);

	_ContinueSC = AddComponent<SpriteComponent>(GameObject::SecondPri);
	_ContinueSC->LoadInfo("Continue", "Unlit", D3DXVECTOR2(1.0f,1.0f));
	_ContinueSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f));

	m_Time = 0;
	
}

void PressContinue::Update()
{
	if (m_Disappear)
	{
		m_Time++;
		float T = m_Time / m_MaxTime;
		float Alpha;

		Alpha = Math::FloatLerp(1.0f, 0.0f, T);

		_ContinueSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, Alpha));

		if (m_Time >= m_MaxTime)
		{
			SetDestroy();
		}
		return;
	}

	if (m_isReady)
	{
		m_Time++;
		float T = m_Time / m_MaxTime;
		float Alpha;
		switch (m_State)
		{
		case 0:
			Alpha = Math::FloatLerp(1.0f, 0.2f, T);

			_ContinueSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, Alpha));

			if (m_Time >= m_MaxTime)
			{
				m_Time = 0;
				m_State = 1;
			}
			break;
		case 1:
			Alpha = Math::FloatLerp(0.2f, 1.0f, T);

			_ContinueSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, Alpha));

			if (m_Time >= m_MaxTime)
			{
				m_Time = 0;
				m_State = 0;
			}
			break;
		}
	}

	if (!m_isReady)
	{
		float _Alpha = _ContinueSC->GetColor().w;
		if (_Alpha < 1.0f)
		{
			_Alpha += 0.005f;
			_ContinueSC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, _Alpha));
		}
		else
		{
			m_isReady = true;
		}
	}

	GameObject::Update();
}

void PressContinue::Disappear()
{
	if (m_Disappear) return;

	m_Disappear = true;
	
	m_Time = 0;
	m_MaxTime = 0.25 * Manager::Time;
}
