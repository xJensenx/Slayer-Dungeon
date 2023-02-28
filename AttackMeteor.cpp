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
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ���f���ǉ�
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("Meteor", ModelRenderer::RimType);

	// �T�C�Y�擾
	m_Size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �x���ǉ�
	m_Warning = _Scene->AddGameObject<Boss_AttackWarning>(Scene::Layer_ObjectLayer);
	m_Warning->SetSize(m_Size);
}

void AttackMeteor::Update()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// ���b�V���t�B�[���h�擾
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

	// �x�����W���X�V����
	m_Warning->SetPosition(D3DXVECTOR3(m_Position.x, m_Warning->GetPosition().y, m_Position.z));

	// ��������
	m_Position.y -= 0.3f;

	// �߂��̃v���C���[�Ƀ_���[�W��^����
	PhysicsCast* _Phy = PhysicsCast::PhysicsSphereCast<Player>(m_Position, m_Size.x);
	if (_Phy != NULL)
	{
		// �G�t�F�N�g���o��
		Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
		_Effect->SetPosition(m_Position);
		_Effect->SetSize(D3DXVECTOR3(14.0f, 14.0f, 0.0f));
		_Effect->SetEffectType<EffectType_BossMeteor>();

		// ��������炷
		AudioManager::PlaySE("SEMeteorExplode");

		// �_���[�W��^����
		_Phy->GetColldeObj()->DealDamage(1.0f);
		// �x��������
		m_Warning->SetDestroy();
		// ������j�󂷂�
		SetDestroy();
		return;
	}

	// ���b�V���t�B�[���h�ɓ�����ƃ_���[�W���߂��ɗ^����
	if (_MeshField != NULL)
	{
		if (m_Position.y <= _MeshField->GetHeight(m_Position))
		{
			// ��������炷
			AudioManager::PlaySE("SEMeteorExplode");

			// �x��������
			m_Warning->SetDestroy();
			// �G�t�F�N�g���o��
			Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
			_Effect->SetPosition(m_Position);
			_Effect->SetSize(D3DXVECTOR3(14.0f, 14.0f, 0.0f));
			_Effect->SetEffectType<EffectType_BossMeteor>();
			// ������j�󂷂�
			SetDestroy();
			return;
		}
	}


	GameObject::Update();
}
