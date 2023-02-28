#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "TutorialUI.h"

void TutorialUI::Init()
{
	// ‰Šú‰»
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TutorialUI::Update()
{
	// Ží—Þ‚ÌXV
	m_UIType->Update();

	GameObject::Update();
}
