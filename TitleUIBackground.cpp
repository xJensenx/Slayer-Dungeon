#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "TitleUIBackground.h"

// �w��̖ړI���W
D3DXVECTOR3 g_TargetPos = D3DXVECTOR3(SCREEN_WIDTH / 4 - 75.0f, SCREEN_HEIGHT / 2, 0.0f);

// �������W
D3DXVECTOR3 g_CurPos;

// �ړ������ǂ���
bool g_Moving = false;
// ���`��ԗp���ݎ���
float g_Time;
// ���`��ԗp�ړI�Ɏ���܂ł̎���
float g_MaxTime = 0.5f * Manager::Time;

void TitleUIBackground::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2 + 125.0f, SCREEN_HEIGHT + 100.0f, 0.0f);

	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("UIBackground", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_SC->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.75f));

	// ������
	m_isReady = false;
	g_Moving = false;
	g_Time = 0.0f;
	g_MaxTime = 0.5f * Manager::Time;
}

void TitleUIBackground::Update()
{
	// �ړI�n�܂ňړ�������
	if (!g_Moving)
	{
		g_Moving = true;
		g_CurPos = m_Position;
	}

	if (g_Time < g_MaxTime)
	{
		g_Time++;
		D3DXVECTOR3 LerpPos;
		float T = g_Time / g_MaxTime;
		D3DXVec3Lerp(&LerpPos, &g_CurPos, &g_TargetPos, T);

		m_Position = LerpPos;
	}
	else
	{
		m_isReady = true;
	}

	GameObject::Update();
}
