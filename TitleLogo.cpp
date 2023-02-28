#include "main.h"
#include "renderer.h"
#include "ComponentInclude.h"
#include "TitleLogo.h"
#include "Math.h"

void TitleLogo::Init()
{
	// スプライトコンポーネント追加
	AddComponent<SpriteRenderer>(GameObject::FirstPri)->SetInfo("TitleWord", SpriteRenderer::UnlitType, SpriteRenderer::Kinematic, SpriteRenderer::NoEffect,
		D3DXVECTOR3(3.0f, 0.8f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TitleEffect = true;

	// パーティクルエフェクト追加
	AddComponent<ParticleSystem>(GameObject::ThirdPri)->SetTitleEffect();
}

void TitleLogo::Uninit()
{
	GameObject::Uninit();
}

void TitleLogo::Update()
{
	TitleEffect();

	GameObject::Update();
}

void TitleLogo::Draw()
{
	GameObject::Draw();
}

void TitleLogo::TitleEffect()
{
	if (!m_TitleEffect) return;

	m_TitleEffectTime++;
	if (m_TitleEffectTime >= 0.6f * Manager::Time)
	{
		m_TitleEffectTime = 0.0f;

		for (int i = 0; i < 3; i++)
		{
			// パーティクルエフェクト取得
			ParticleSystem* _PS = GetComponent<ParticleSystem>();

			_PS->SetParticleSize(D3DXVECTOR3(0.3f, 0.3f, 0.3f));

			_PS->SetParticle2D(true);

			//_PS->SetParticleMaterial(true);

			//_PS->SetParticleShader(ModelRenderer::RimType);

			//_PS->SetParticleColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.01f));

			//_PS->SetParticleEmission(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f));

			D3DXVECTOR3 SpawnPos;
			SpawnPos.x = m_Position.x - 5.0f;
			SpawnPos.y = m_Position.y + Math::FloatRandBetween(-0.5f,0.5f) + 1.0f;
			SpawnPos.z = m_Position.z + 1.0f;

			D3DXVECTOR3 SpawnVel;
			SpawnVel.x = Math::FloatRandBetween(0.001f, 0.002f);
			SpawnVel.y = Math::FloatRandBetween(-0.001f, 0.001f);
			SpawnVel.z = 0.0f;

			_PS->SpawnEmitter(SpawnPos, SpawnVel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f);

			SpawnPos.x = m_Position.x + 5.0f;
			SpawnVel.x = Math::FloatRandBetween(-0.001f, -0.002f);

			_PS->SpawnEmitter(SpawnPos, SpawnVel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f);

		}
	}

}
