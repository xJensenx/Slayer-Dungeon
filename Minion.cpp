#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "Minion.h"
#include "MinionAnimation.h"
#include "Player.h"

#include "MeshField.h"
#include "Math.h"
#include "PhysicsCast.h"
#include "MinionHpBar.h"
#include "Game.h"
#include "Tutorial.h"
#include "AudioManager.h"

void Minion::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_isAttacking = false;
	m_CurHp = m_MaxHp;
	m_isDead = false;

	// アニメーションコンポーネント追加
	AnimModelManager* _AMM = AddComponent<AnimModelManager>(GameObject::FirstPri);
	_AMM->SetModel("Minion", AnimModelManager::LitType);
	m_Size = _AMM->GetAnimModelSize();

	m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);

	m_WaitTime = 5.0f * Manager::Time;

	// HpBarを追加する
	Scene* _Scene = Manager::GetScene();
	m_HpBar = _Scene->AddGameObject<MinionHpBar>(Scene::Layer_ObjectLayer);
	m_HpBar->SetCharacter(this);

	// アニメーションマネージャーの追加
	m_Animation = AddAnimationManager<MinionAnimation>();
	m_Animation->SetCharacter(this);

	// 当たり判定を追加する
	AddComponent<CollisionOBB>(GameObject::ThirdPri);

	ChangeBehavior<MinionBehaviorTree_Chase>();
}

void Minion::Update()
{
	if (m_Pause) return;

	// シーンを取得
	Scene* _Scene = Manager::GetScene();
	// メッシュフィールドを取得
	MeshField* _MF = _Scene->GetGameObject<MeshField>();

	// 攻撃クールダウン処理
	if (!m_isAttacking)
	{
		if (m_AttackCD > 0.0f)
		{
			m_AttackCD--;
		}
	}

	//if (m_Cinematic)
	//{
	//	if (m_WaitTime > 0.0f)
	//	{
	//		m_WaitTime--;
	//	}
	//	else
	//	{
	//		m_Cinematic = false;
	//		ChangeBehavior<MinionBehaviorTree_Idle>();
	//	}
	//}

	// ビヘイビアツリー処理
	m_Behavior->Update();

	GameObject::Update();

	if (!m_isDead)
	{
		// メッシュフィールドがある場合は高さを制限する
		if (_MF != NULL)
		{
			m_Position.y = _MF->GetHeight(m_Position);
		}
	}
}

void Minion::AttackEvent()
{
	Scene* _Scene = Manager::GetScene();
	// ボックスキャストの置く座標
	D3DXVECTOR3 _Origin;
	// ボックスキャストのサイズ
	D3DXVECTOR3 _Size;
	// ボックスキャスト変数
	PhysicsCast* _Phy;

	// ボスの前に置く
	_Origin = m_Position + (GetForward() * -2.5f);
	// Yを0にする
	_Origin.y = m_Position.y;
	// サイズを調整
	_Size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	// ボックスキャスト
	_Phy = PhysicsCast::PhysicBoxCast<Player>(_Origin, _Size);
	if (_Phy != NULL)
	{
		_Phy->GetColldeObj()->DealDamage(1);
	}
}

void Minion::DealDamage(float Damage)
{
	if (m_isDead) return;

	// チュートリアルの場合はチュートリアルのダメージ受ける専用ビヘイビアに変わる
	Scene* _Scene = Manager::GetScene();
	AudioManager::PlaySE("SEHitEnemy");
	
	if (Manager::CheckScene<Tutorial>())
	{
		Tutorial* _Tutorial = (Tutorial*)_Scene;
		if (!_Tutorial->GetTutorialFinish())
		{
			if (_Tutorial->GetTutorialState<TutorialState_Mission04>())
			{
				ChangeBehavior<MinionBehaviorTree_BeenHit>();
				return;
			}
			else
			{
				ChangeBehavior<MinionBehaviorTree_TutorialBeenHit>();
				return;
			}
		}
	}

	m_CurHp -= Damage;

	if (m_CurHp <= 0.0f)
	{
		m_isDead = true;
		ChangeBehavior<MinionBehaviorTree_Dead>();
		m_HpBar->SetDestroy();

	}
	else
	{
		// ダメージ受けるビヘイビアに変わる
		ChangeBehavior<MinionBehaviorTree_BeenHit>();
	}

}
