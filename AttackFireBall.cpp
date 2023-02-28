#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "AttackFireBall.h"

void AttackFireBall::Init()
{
	// ‰Šú‰»
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// ƒ‚ƒfƒ‹’Ç‰Á
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("FireBall", ModelRenderer::FireBallType);
}

void AttackFireBall::Update()
{
	// XVˆ—
	if (m_FireBallType != NULL)
	{
		m_FireBallType->Update();
	}
	
	GameObject::Update();
}
