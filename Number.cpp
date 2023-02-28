#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Number.h"

void Number::Init()
{
	// èâä˙âª
	m_Position = D3DXVECTOR3(-500.0f, -500.0f, 0.0f);
	m_Size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	

	m_Cnt = 0;
	m_OldCnt = -1;
}

void Number::Update()
{
	if (m_Numeric <= 1)
	{
		float x = m_Cnt % 5 * (1.0f / 5);
		float y = m_Cnt / 5 * (1.0f / 2);
		m_Number[0]->SetTexCoord(D3DXVECTOR2(x, y));
	}
	else
	{
		int Cnt = m_Cnt;

		for (int i = 0; i < m_Numeric; i++)
		{
			int n = Cnt / 10;

			float x = Cnt % 5 * (1.0f / 5);
			float y = Cnt / 5 * (1.0f / 2);
			m_Number[i]->SetTexCoord(D3DXVECTOR2(x, y));
			D3DXVECTOR3 FirstOffSet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			FirstOffSet.x += m_Size.x / 2 * (float)(m_Numeric - i - 1);

			m_Number[i]->SetOffSet(FirstOffSet);

			Cnt /= 10;
		}	
	}
	
	GameObject::Update();
}

void Number::LoadNumber()
{
	if (m_OldCnt == m_Cnt) return;

	m_OldCnt = m_Cnt;

	int Numeric = 1;
	bool isFinish = false;
	while (!isFinish)
	{
		if ((m_Cnt / (int)powf(10, Numeric)) == 0)
		{
			isFinish = true;
			break;
		}
		Numeric++;
	}
	
	SetNumeric(Numeric);

	for (auto N : m_Number)
	{
		N->Uninit();
		delete N;
		N = NULL;
	}
	m_Number.clear();

	// forï∂Ç≈âÒÇ∑
	for (int i = 0; i < m_Numeric; i++)
	{
		SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
		_SC->LoadInfo("Number", "Unlit", D3DXVECTOR2(0.2f, 0.5f));
		_SC->SetSpriteType(SpriteComponent::ProgressBar);

		m_Number.push_back(_SC);
	}
}
