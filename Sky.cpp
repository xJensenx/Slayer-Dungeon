#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "Scene.h"
#include "Camera.h"
#include "model.h"

#include "ComponentInclude.h"

#include "Sky.h"

#include "Title.h"

void Sky::Init()
{
	AddComponent<ModelRenderer>(GameObject::FirstPri)->SetModel("Sky", ModelRenderer::LitType);
	m_Position = D3DXVECTOR3(0.0f, 0.0f, -15.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(200.0f, 200.0f, 200.0f);
	//D3DXQuaternionIdentity(&m_Quaternion);

}

void Sky::Uninit()
{
	GameObject::Uninit();
}

void Sky::Update()
{
	Scene* _Scene = Manager::GetScene();
	if (!Manager::CheckScene<Title>())
	{
		Camera* _Camera = _Scene->GetGameObject<Camera>();

		m_Position = _Camera->GetPosition();
		m_Position.y = -15.0f;
	}
	GameObject::Update();
}

void Sky::Draw()
{	
	GameObject::Draw();
}
