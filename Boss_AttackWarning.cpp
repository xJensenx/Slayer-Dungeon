#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Boss_AttackWarning.h"
#include "MeshField.h"

void Boss_AttackWarning::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// 最初のサイズは全部0.0f
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// スプライト追加
	SpriteComponent* _SR = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SR->SetSpriteType(SpriteComponent::WarningBilBoard);
	_SR->LoadInfo("BossAtkWarning", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void Boss_AttackWarning::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// メッシュフィールドを取得
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

	// 高さは常にメッシュフィールドの上にいる
	if (_MeshField != NULL)
	{
		m_Position.y = _MeshField->GetHeight(m_Position) + 0.5f;
	}

	GameObject::Update();
}
