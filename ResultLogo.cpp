#include "main.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "ResultLogo.h"

void ResultLogo::Init()
{

	m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("ToBeContinued", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

}

void ResultLogo::Uninit()
{
	GameObject::Uninit();
}

void ResultLogo::Update()
{
	GameObject::Update();
}

void ResultLogo::Draw()
{
	GameObject::Draw();
}
