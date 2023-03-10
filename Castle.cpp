#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Castle.h"

void Castle::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// モデル
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("Castle", ModelRenderer::RimType);
}
