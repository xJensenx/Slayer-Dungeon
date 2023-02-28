#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "TitleIsland.h"
#include "Sea.h"

void TitleIsland::Init()
{
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	//_MR->SetTexture("TitleGrass");
	_MR->SetModel("Island", ModelRenderer::UnlitType);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
}

void TitleIsland::Update()
{
	//// ƒV[ƒ“‚Ìî•ñŽæ“¾
	//Scene* _Scene = Manager::GetScene();
	//// ŠC‚Ìî•ñŽæ“¾
	//Sea* _Sea = _Scene->GetGameObject<Sea>();

	//// ŠC‚Ì”g‚Ì‚‚³‚ÅÀ•WXV
	//if (_Sea != NULL)
	//{
	//	m_Position.y = _Sea->GetHeight(m_Position) - 1.5f;
	//}
	

	GameObject::Update();
}
