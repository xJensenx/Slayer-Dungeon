#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "Sword.h"
#include "Math.h"

#include "Player.h"
#include "Minion.h"
#include "PhysicsCast.h"
#include "Boss.h"
#include "Camera.h"
#include "MeshField.h"
#include "Effect.h"
#include "SwordTrail.h"

void Sword::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);
	m_IdleAnimTime = 0.0f;
	m_IdleState = 0;
	m_AtkDmg = 1.0f;
	m_isShake = false;
	// 色の初期化
	m_SwordTrailColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	// モデルを追加する
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetTexture("Env");
	_MR->SetModel("Sword", ModelRenderer::EnvType);
	m_Size = _MR->GetModelSize("Sword");
	_MR->SetEmission(D3DXCOLOR(1000.0f, 0.0f, 0.0f, 1.0f));
	_MR->SetQuaternion(true);

	// Quaternion初期化
	D3DXQuaternionIdentity(&m_Quaternion);

	// 初期化
	m_CurShootTime = m_TotalIdleTime;

	// サイズ調整
	//m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);

	// パーティクルシステム追加する
	AddComponent<ParticleSystem>(GameObject::ThirdPri);

	// 当たり判定を追加する
	AddComponent<CollisionOBB>(GameObject::ThirdPri);

}

void Sword::Uninit()
{
	// 剣の軌跡を消します
	InitSwordTrail();

	// 剣の状態のメモリ解放
	if (m_SwordStatus != NULL)
	{
		delete m_SwordStatus;
		m_SwordStatus = NULL;
	}

	GameObject::Uninit();
}

void Sword::Update()
{
	if (m_Pause && !m_IgnorePause) return;

	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// カメラ取得
	Camera* _Camera = _Scene->GetGameObject<Camera>();
	// メッシュフィールド取得
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

	m_SwordStatus->Update();

	// 剣の当たり判定はPhysicsCastで判定しています
	//// 当たり判定
	//CollisionOBB* _OBB = GetComponent<CollisionOBB>();
	//if (_OBB->isCollisionWith<Minion>())
	//{
	//	HitEffect();
	//}

	GameObject::Update();
}

void Sword::InitSwordTrail()
{
	if (m_SwordTrail != NULL)
	{
		m_SwordTrail->SetDestroy();
		m_SwordTrail = NULL;
	}
}

void Sword::SetCharacter(Player* P, SwordPosition SP)
{
	m_Character = P;
	m_SwordPos = SP;

	// プレイヤーの座標やRight
	D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
	PlayerPos.y += 2.0f;
	D3DXVECTOR3 PlayerRight = -m_Character->GetRight();
	// 置く場所の変数
	D3DXVECTOR3 PlacePos;
	// プレイヤーとどのぐらい離れるか
	float DistanceBetween = 2.0f;
	// 変数用意
	D3DXVECTOR2 PlaceValue;
	float Angle = 0.0f;
	float ValueXZ = 0.0f;
	float ValueY = 0.0f;

	switch (m_SwordPos)
	{
	case First:
		PlaceValue = D3DXVECTOR2(0.5f, 0.3f);
		Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

		m_Rotation.x = PlayerRight.z * (Angle * 2);
		m_Rotation.z = -PlayerRight.x * (Angle * 2);

		m_IdleAnimTime = 0.0f;
		break;
	case Second:
		PlaceValue = D3DXVECTOR2(0.3f, 0.5f);
		Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

		m_Rotation.x = PlayerRight.z * (Angle / 2);
		m_Rotation.z = -PlayerRight.x * (Angle / 2);
		
		m_IdleAnimTime = 0.3f;
		break;
	case Third:
		PlaceValue = D3DXVECTOR2(0.0f, 0.5f);
		Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
		m_IdleAnimTime = 0.0f;

		break;
	case Fourth:
		PlaceValue = D3DXVECTOR2(-0.3f, 0.5f);
		Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

		m_Rotation.x = -PlayerRight.z * (Angle / 3);
		m_Rotation.z = PlayerRight.x * (Angle / 3);

		m_IdleAnimTime = 0.3f;
		break;
	case Fifth:
		PlaceValue = D3DXVECTOR2(-0.5f, 0.3f);
		Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
		m_Rotation.x = -PlayerRight.z * (Angle / 2);
		m_Rotation.z = PlayerRight.x * (Angle / 2);

		m_IdleAnimTime = 0.0f;
		break;
	}

	ValueXZ = DistanceBetween * cosf(Angle);
	PlayerRight *= ValueXZ;
	ValueY = DistanceBetween * sinf(Angle);

	PlacePos.x = PlayerPos.x + PlayerRight.x;
	PlacePos.y = PlayerPos.y + ValueY;
	PlacePos.z = PlayerPos.z + PlayerRight.z;

	m_Position = D3DXVECTOR3(PlacePos.x, PlacePos.y, PlacePos.z);
}

// 剣の軌跡
void Sword::TrailEffect()
{
	// 先頭の座標
	D3DXVECTOR3 HeadPos = m_Position + GetQuaternionUp() * 2.0f;
	// 末尾の座標
	D3DXVECTOR3 TailPos = m_Position;

	// SwordTrailがNULLだと新しいやつを作ります
	if (m_SwordTrail == NULL)
	{
		// シーン取得
		Scene* _Scene = Manager::GetScene();

		// ソード軌跡追加
		m_SwordTrail = _Scene->AddGameObject<SwordTrail>(Scene::Layer_ObjectLayer);

		// 色を調整
		m_SwordTrail->ChangeColor(m_SwordTrailColor);
		// 座標記録します
		m_SwordTrail->SaveTrailPos(HeadPos, TailPos);
		return;
	}

	// 色を調整
	m_SwordTrail->ChangeColor(m_SwordTrailColor);
	// 既にSwordTrailが作られていると直接座標記録
	m_SwordTrail->SaveTrailPos(HeadPos, TailPos);

	// 描画されたら新しいやつ作ります
	if (m_SwordTrail->GetTrailDraw())
	{
		// 剣の軌跡をNULLにします
		m_SwordTrail = NULL;
		// 新しい軌跡を作ります
		Scene* _Scene = Manager::GetScene();

		m_SwordTrail = _Scene->AddGameObject<SwordTrail>(Scene::Layer_ObjectLayer);

		// 色を調整
		m_SwordTrail->ChangeColor(m_SwordTrailColor);
		m_SwordTrail->SaveTrailPos(HeadPos, TailPos);
	}

	//// Blur

	//// ParticleSystemを取得する
	//ParticleSystem* _PS = GetComponent<ParticleSystem>();
	//// 数を調整する
	//_PS->SetParticleNum(1);
	//_PS->SetParticleSize(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	//for (int i = 0; i < _PS->GetParticleNum(); i++)
	//{
	//	// パーティクル生成
	//	_PS->SpawnEmitter(m_Position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f);
	//}
}

void Sword::HitEffect(D3DXVECTOR3 HitPos)
{
	Scene* _Scene = Manager::GetScene();

	Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
	_Effect->SetPosition(HitPos);
	_Effect->SetEffectType<EffectType_AttackHit>();

	ParticleSystem* _PS = GetComponent<ParticleSystem>();
	// 数調整
	_PS->SetParticleNum(10);
	_PS->SetParticleSize(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
	_PS->SetParticle2D(true);
	_PS->SetParticleName("HitStarParticleEffect");

	// for分で繰り返す
	for (int j = 0; j < _PS->GetParticleNum(); j++)
	{
		// パーティクルを生成するする（座標、速度、加速度、ライフ）
		_PS->SpawnEmitter(HitPos,
			D3DXVECTOR3(Math::FloatRandBetween(-0.025f, 0.025f), Math::FloatRandBetween(0.1f, 0.2f) , Math::FloatRandBetween(-0.025f, 0.025f)),
			D3DXVECTOR3(0.0f, -0.0025f, 0.0f), 2.0f);
	}
}

void Sword::DissolveEffect()
{
	// ModelRenderer取得
	ModelRenderer* _MR = GetComponent<ModelRenderer>();

	// 頂点座標取得
	std::vector<D3DXVECTOR3> VertexPos = _MR->GetVertexPosition();

	ParticleSystem* _PS = GetComponent<ParticleSystem>();

	// 数調整
	int Num = VertexPos.size();
	_PS->SetParticleNum(Num / 10);
	_PS->SetParticleSize(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	_PS->SetParticleCol(true);
	_PS->SetParticle2D(true);
	_PS->SetParticleEmission(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	_PS->SetParticleName("HitStarParticleEffect");

	// for分で繰り返す
	for (int j = 0; j < _PS->GetParticleNum(); j++)
	{
		// パーティクルを生成するする（座標、速度、加速度、ライフ）
		_PS->SpawnEmitter(m_Position + VertexPos[j * 5],
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, -0.0005f, 0.0f), 1.0f);
	}
}
