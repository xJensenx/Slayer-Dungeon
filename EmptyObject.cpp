#include "main.h"
#include "manager.h"
#include "EmptyObject.h"
#include "ComponentInclude.h"

void EmptyObject::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("ColliderBox", ModelRenderer::UnlitType);
	m_Size = _MR->GetModelSize("ColliderBox");

	m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);

	AddComponent<CollisionOBB>(GameObject::ThirdPri);

}

void EmptyObject::Uninit()
{
	GameObject::Uninit();
}

void EmptyObject::Update()
{
	GameObject::Update();
}

void EmptyObject::Draw()
{
	GameObject::Draw();
}
