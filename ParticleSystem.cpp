#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "ParticleObj.h"
#include "ParticleSystem.h"

void ParticleSystem::Init()
{
	// 初期化する
	m_ParticleNum = 100;

	m_ParticleSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_ParticleColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	m_ParticleAmbient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_ParticleEmission = D3DXCOLOR(0.0f, 0.0f, 100.0f, 1.0f);

	m_ParticleAccRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ParticleCol = false;

	m_UseMaterial = true;

	m_TitleEffect = false;

	m_Particle2D = false;

	m_ShaderType = ModelRenderer::LitType;

	m_ParticleName = "None";
}

void ParticleSystem::Uninit()
{
}

void ParticleSystem::Update()
{
}

void ParticleSystem::Draw()
{
}

void ParticleSystem::SpawnEmitter(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, D3DXVECTOR3 Acc, float Dur)
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// パーティクルを生成する
	ParticleObj* P = _Scene->AddGameObject<ParticleObj>(Scene::Layer_ObjectLayer);
	// 座標設置
	P->SetPosition(Pos);
	// 存在する時間設置
	P->SetDuration(Dur);
	// サイズを調整する
	P->SetScale(m_ParticleSize);
	// 当たり判定を設置する
	P->SetCollision(m_ParticleCol);
	// 回転の加速度の設置
	P->SetAccRotation(m_ParticleAccRot);
	// タイトルエフェクトを付けるかどうか
	if (m_TitleEffect) P->SetTitleEffect();

	if (!m_Particle2D)
	{
		// 色の設定
		P->SetColor(m_ParticleColor, m_ParticleAmbient, m_ParticleEmission);
		// マテリアルの使用
		P->SetMaterial(m_UseMaterial);
		// シェーダーの設置
		P->SetShader(m_ShaderType);
	}
	else
	{
		P->Set2DParticle();
	}
	if (m_ParticleName != "None")
	{
		P->SetParticleName(m_ParticleName);
	}
	
	// 物理のコンポーネントを取得する
	RigidBody* _RG = P->GetComponent<RigidBody>();

	// 速度調整
	_RG->SetVelocity(Vel);
	// 加速度調整
	_RG->SetAccelerate(Acc);
}
