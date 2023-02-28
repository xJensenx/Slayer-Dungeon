#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "AttackMeteor.h"

#include "Player.h"
#include "MeshField.h"
#include "Boss_AttackWarning.h"
#include "PhysicsCast.h"
#include "Effect.h"
#include "AudioManager.h"

void AttackMeteor::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// モデル追加
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("Meteor", ModelRenderer::RimType);

	// サイズ取得
	m_Size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// 警告追加
	m_Warning = _Scene->AddGameObject<Boss_AttackWarning>(Scene::Layer_ObjectLayer);
	m_Warning->SetSize(m_Size);
}

void AttackMeteor::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// メッシュフィールド取得
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

	// 警告座標を更新する
	m_Warning->SetPosition(D3DXVECTOR3(m_Position.x, m_Warning->GetPosition().y, m_Position.z));

	// 落下する
	m_Position.y -= 0.3f;

	// 近くのプレイヤーにダメージを与える
	PhysicsCast* _Phy = PhysicsCast::PhysicsSphereCast<Player>(m_Position, m_Size.x);
	if (_Phy != NULL)
	{
		// エフェクトを出す
		Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
		_Effect->SetPosition(m_Position);
		_Effect->SetSize(D3DXVECTOR3(14.0f, 14.0f, 0.0f));
		_Effect->SetEffectType<EffectType_BossMeteor>();

		// 爆発音を鳴らす
		AudioManager::PlaySE("SEMeteorExplode");

		// ダメージを与える
		_Phy->GetColldeObj()->DealDamage(1.0f);
		// 警告を消す
		m_Warning->SetDestroy();
		// 自分を破壊する
		SetDestroy();
		return;
	}

	// メッシュフィールドに当たるとダメージを近くに与える
	if (_MeshField != NULL)
	{
		if (m_Position.y <= _MeshField->GetHeight(m_Position))
		{
			// 爆発音を鳴らす
			AudioManager::PlaySE("SEMeteorExplode");

			// 警告を消す
			m_Warning->SetDestroy();
			// エフェクトを出す
			Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
			_Effect->SetPosition(m_Position);
			_Effect->SetSize(D3DXVECTOR3(14.0f, 14.0f, 0.0f));
			_Effect->SetEffectType<EffectType_BossMeteor>();
			// 自分を破壊する
			SetDestroy();
			return;
		}
	}


	GameObject::Update();
}
