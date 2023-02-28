#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "ParticleObj.h"
#include "MeshField.h"

void ParticleObj::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_Duration = 5.0f * Manager::Time;
	m_Collision = false;
	m_TitleState = 0;
	m_SinValue = 0.0f;
	m_AccRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// パーティクルのオブジェクトを追加する
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("Particle", ModelRenderer::LitType);
	_MR->SetDiffuse(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	_MR->SetAmbient(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	_MR->SetEmission(D3DXCOLOR(0.0f, 0.0f, 100.0f, 1.0f));
	_MR->SetUseMaterial(true);
	m_Size = _MR->GetModelSize("Particle");

	// 物理挙動を追加する
	AddComponent<RigidBody>(GameObject::ThirdPri);

	m_Particle2D = false;
}

void ParticleObj::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// メッシュフィールド取得
	MeshField* _MF = _Scene->GetGameObject<MeshField>();

	// 回転の加速度
	m_Rotation += m_AccRotation;

	if (m_Duration > 0.0f)
	{
		m_Duration--;
	}
	else
	{
		SetDestroy();
		return;
	}

	// 特別な動き
	TitleEffectMovement();

	GameObject::Update();

	// 当たり判定がある場合は
	if (m_Collision)
	{
		if (_MF != NULL)
		{
			if (m_Position.y <= _MF->GetHeight(m_Position))
			{
				m_Position.y = _MF->GetHeight(m_Position);

				RigidBody* _RG = GetComponent<RigidBody>();
				_RG->SetVelocity(D3DXVECTOR3(_RG->GetVelocity().x, -_RG->GetVelocity().y, _RG->GetVelocity().z));
			}
		}
	}
}

void ParticleObj::SetShader(ModelRenderer::LightningType ShaderType)
{
	ModelRenderer* _MR = GetComponent<ModelRenderer>();
	_MR->SetModel("Particle", ShaderType);

	switch (ShaderType)
	{
	case ModelRenderer::ParticleEnvType:
		_MR->SetTexture("Env");
		break;
	case ModelRenderer::RimType:
		_MR->SetModel("Particle02", ShaderType);
		break;
	}
}

void ParticleObj::SetMaterial(bool On)
{
	ModelRenderer* _MR = GetComponent<ModelRenderer>();
	_MR->SetUseMaterial(On);
}

void ParticleObj::SetColor(D3DXCOLOR Color, D3DXCOLOR Ambient, D3DXCOLOR Emission)
{
	// ModelRenderer取得して色を調整する
	ModelRenderer* _MR = GetComponent<ModelRenderer>();
	_MR->SetDiffuse(Color);
	_MR->SetAmbient(Ambient);
	_MR->SetEmission(Emission);
}

void ParticleObj::Set2DParticle()
{
	m_Particle2D = true;

	ModelRenderer* _MR = GetComponent<ModelRenderer>();
	_MR->SetVisibility(false);

	SpriteComponent* _SR = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SR->LoadInfo("Particle", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_SR->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SR->SetColor(D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.8f));
}

void ParticleObj::SetParticleName(std::string Name)
{
	if (m_Particle2D)
	{
		SpriteComponent* _SR = GetComponent<SpriteComponent>();
		_SR->LoadInfo(Name, "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		_SR->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
		m_Size = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	}
	else
	{
		ModelRenderer* _MR = GetComponent<ModelRenderer>();
		_MR->SetModel(Name, ModelRenderer::LitType);
	}
}

void ParticleObj::TitleEffectMovement()
{
	// タイトルエフェクトが付けていないとreturnする
	if (!m_Title) return;

	m_SinValue += 0.01f;

	m_Position.y = m_TitlePos.y + (sinf(m_SinValue) * 0.5f);
}
