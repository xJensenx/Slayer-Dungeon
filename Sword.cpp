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
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);
	m_IdleAnimTime = 0.0f;
	m_IdleState = 0;
	m_AtkDmg = 1.0f;
	m_isShake = false;
	// �F�̏�����
	m_SwordTrailColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	// ���f����ǉ�����
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetTexture("Env");
	_MR->SetModel("Sword", ModelRenderer::EnvType);
	m_Size = _MR->GetModelSize("Sword");
	_MR->SetEmission(D3DXCOLOR(1000.0f, 0.0f, 0.0f, 1.0f));
	_MR->SetQuaternion(true);

	// Quaternion������
	D3DXQuaternionIdentity(&m_Quaternion);

	// ������
	m_CurShootTime = m_TotalIdleTime;

	// �T�C�Y����
	//m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);

	// �p�[�e�B�N���V�X�e���ǉ�����
	AddComponent<ParticleSystem>(GameObject::ThirdPri);

	// �����蔻���ǉ�����
	AddComponent<CollisionOBB>(GameObject::ThirdPri);

}

void Sword::Uninit()
{
	// ���̋O�Ղ������܂�
	InitSwordTrail();

	// ���̏�Ԃ̃��������
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

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �J�����擾
	Camera* _Camera = _Scene->GetGameObject<Camera>();
	// ���b�V���t�B�[���h�擾
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

	m_SwordStatus->Update();

	// ���̓����蔻���PhysicsCast�Ŕ��肵�Ă��܂�
	//// �����蔻��
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

	// �v���C���[�̍��W��Right
	D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
	PlayerPos.y += 2.0f;
	D3DXVECTOR3 PlayerRight = -m_Character->GetRight();
	// �u���ꏊ�̕ϐ�
	D3DXVECTOR3 PlacePos;
	// �v���C���[�Ƃǂ̂��炢����邩
	float DistanceBetween = 2.0f;
	// �ϐ��p��
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

// ���̋O��
void Sword::TrailEffect()
{
	// �擪�̍��W
	D3DXVECTOR3 HeadPos = m_Position + GetQuaternionUp() * 2.0f;
	// �����̍��W
	D3DXVECTOR3 TailPos = m_Position;

	// SwordTrail��NULL���ƐV����������܂�
	if (m_SwordTrail == NULL)
	{
		// �V�[���擾
		Scene* _Scene = Manager::GetScene();

		// �\�[�h�O�Ւǉ�
		m_SwordTrail = _Scene->AddGameObject<SwordTrail>(Scene::Layer_ObjectLayer);

		// �F�𒲐�
		m_SwordTrail->ChangeColor(m_SwordTrailColor);
		// ���W�L�^���܂�
		m_SwordTrail->SaveTrailPos(HeadPos, TailPos);
		return;
	}

	// �F�𒲐�
	m_SwordTrail->ChangeColor(m_SwordTrailColor);
	// ����SwordTrail������Ă���ƒ��ڍ��W�L�^
	m_SwordTrail->SaveTrailPos(HeadPos, TailPos);

	// �`�悳�ꂽ��V��������܂�
	if (m_SwordTrail->GetTrailDraw())
	{
		// ���̋O�Ղ�NULL�ɂ��܂�
		m_SwordTrail = NULL;
		// �V�����O�Ղ����܂�
		Scene* _Scene = Manager::GetScene();

		m_SwordTrail = _Scene->AddGameObject<SwordTrail>(Scene::Layer_ObjectLayer);

		// �F�𒲐�
		m_SwordTrail->ChangeColor(m_SwordTrailColor);
		m_SwordTrail->SaveTrailPos(HeadPos, TailPos);
	}

	//// Blur

	//// ParticleSystem���擾����
	//ParticleSystem* _PS = GetComponent<ParticleSystem>();
	//// ���𒲐�����
	//_PS->SetParticleNum(1);
	//_PS->SetParticleSize(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	//for (int i = 0; i < _PS->GetParticleNum(); i++)
	//{
	//	// �p�[�e�B�N������
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
	// ������
	_PS->SetParticleNum(10);
	_PS->SetParticleSize(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
	_PS->SetParticle2D(true);
	_PS->SetParticleName("HitStarParticleEffect");

	// for���ŌJ��Ԃ�
	for (int j = 0; j < _PS->GetParticleNum(); j++)
	{
		// �p�[�e�B�N���𐶐����邷��i���W�A���x�A�����x�A���C�t�j
		_PS->SpawnEmitter(HitPos,
			D3DXVECTOR3(Math::FloatRandBetween(-0.025f, 0.025f), Math::FloatRandBetween(0.1f, 0.2f) , Math::FloatRandBetween(-0.025f, 0.025f)),
			D3DXVECTOR3(0.0f, -0.0025f, 0.0f), 2.0f);
	}
}

void Sword::DissolveEffect()
{
	// ModelRenderer�擾
	ModelRenderer* _MR = GetComponent<ModelRenderer>();

	// ���_���W�擾
	std::vector<D3DXVECTOR3> VertexPos = _MR->GetVertexPosition();

	ParticleSystem* _PS = GetComponent<ParticleSystem>();

	// ������
	int Num = VertexPos.size();
	_PS->SetParticleNum(Num / 10);
	_PS->SetParticleSize(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	_PS->SetParticleCol(true);
	_PS->SetParticle2D(true);
	_PS->SetParticleEmission(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	_PS->SetParticleName("HitStarParticleEffect");

	// for���ŌJ��Ԃ�
	for (int j = 0; j < _PS->GetParticleNum(); j++)
	{
		// �p�[�e�B�N���𐶐����邷��i���W�A���x�A�����x�A���C�t�j
		_PS->SpawnEmitter(m_Position + VertexPos[j * 5],
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, -0.0005f, 0.0f), 1.0f);
	}
}
