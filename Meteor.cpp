#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "Meteor.h"
#include "Math.h"

void Meteor::Init()
{
	// èâä˙âª
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	m_Idle = false;
	m_State = 0;
	m_CurTime = 0.0f;

	// ÉÇÉfÉãí«â¡
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetTexture("Meteor");
	_MR->SetModel("Meteor", ModelRenderer::RimType);

	m_Size = _MR->GetModelSize("Meteor");
}

void Meteor::Update()
{
	IdleAnimation();

	ThrowAnimation();

	GameObject::Update();
}

void Meteor::IdleAnimation()
{
	// ë“ã@èÛë‘Ç≈ÇÕÇ»Ç¢éûreturnÇ∑ÇÈ
	if (!m_Idle) return;

	float MoveAmt = 3.0f;

	switch (m_State)
	{
	case 0:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			m_State = 1;
		}
		break;
	case 1:
		if (m_CurTime > 0.0f)
		{
			m_CurTime--;
		}
		else
		{
			m_State = 0;
		}
		break;
	}

	float T = m_CurTime / (1.0f * Manager::Time);

	m_Position.y = m_InitPos.y + Math::FloatLerp(0.0f, MoveAmt, T);
}

void Meteor::ThrowAnimation()
{
	if (m_Idle) return;

	m_Rotation.x += 0.1f;
}
