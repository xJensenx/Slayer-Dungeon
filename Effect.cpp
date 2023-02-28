#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Effect.h"
#include "EffectType.h"

void Effect::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(3.0f, 3.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Effect::Update()
{
	// エフェクトの更新
	m_EffectType->Update();

	GameObject::Update();
}
