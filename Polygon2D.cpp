#include "main.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "Polygon2D.h"

void Polygon2D::Init()
{
	AddComponent<SpriteRenderer>(GameObject::FirstPri)->SetInfo("Polygon2D", SpriteRenderer::UnlitType, SpriteRenderer::Double,
		SpriteRenderer::NoEffect,
		D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Polygon2D::Uninit()
{
	GameObject::Uninit();
}

void Polygon2D::Update()
{
	GameObject::Update();
}

void Polygon2D::Draw()
{
	GameObject::Draw();
}

