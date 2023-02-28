#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "ParticleObj.h"
#include "ParticleSystem.h"

void ParticleSystem::Init()
{
	// ����������
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
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �p�[�e�B�N���𐶐�����
	ParticleObj* P = _Scene->AddGameObject<ParticleObj>(Scene::Layer_ObjectLayer);
	// ���W�ݒu
	P->SetPosition(Pos);
	// ���݂��鎞�Ԑݒu
	P->SetDuration(Dur);
	// �T�C�Y�𒲐�����
	P->SetScale(m_ParticleSize);
	// �����蔻���ݒu����
	P->SetCollision(m_ParticleCol);
	// ��]�̉����x�̐ݒu
	P->SetAccRotation(m_ParticleAccRot);
	// �^�C�g���G�t�F�N�g��t���邩�ǂ���
	if (m_TitleEffect) P->SetTitleEffect();

	if (!m_Particle2D)
	{
		// �F�̐ݒ�
		P->SetColor(m_ParticleColor, m_ParticleAmbient, m_ParticleEmission);
		// �}�e���A���̎g�p
		P->SetMaterial(m_UseMaterial);
		// �V�F�[�_�[�̐ݒu
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
	
	// �����̃R���|�[�l���g���擾����
	RigidBody* _RG = P->GetComponent<RigidBody>();

	// ���x����
	_RG->SetVelocity(Vel);
	// �����x����
	_RG->SetAccelerate(Acc);
}
