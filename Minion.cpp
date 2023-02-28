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
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_isAttacking = false;
	m_CurHp = m_MaxHp;
	m_isDead = false;

	// �A�j���[�V�����R���|�[�l���g�ǉ�
	AnimModelManager* _AMM = AddComponent<AnimModelManager>(GameObject::FirstPri);
	_AMM->SetModel("Minion", AnimModelManager::LitType);
	m_Size = _AMM->GetAnimModelSize();

	m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);

	m_WaitTime = 5.0f * Manager::Time;

	// HpBar��ǉ�����
	Scene* _Scene = Manager::GetScene();
	m_HpBar = _Scene->AddGameObject<MinionHpBar>(Scene::Layer_ObjectLayer);
	m_HpBar->SetCharacter(this);

	// �A�j���[�V�����}�l�[�W���[�̒ǉ�
	m_Animation = AddAnimationManager<MinionAnimation>();
	m_Animation->SetCharacter(this);

	// �����蔻���ǉ�����
	AddComponent<CollisionOBB>(GameObject::ThirdPri);

	ChangeBehavior<MinionBehaviorTree_Chase>();
}

void Minion::Update()
{
	if (m_Pause) return;

	// �V�[�����擾
	Scene* _Scene = Manager::GetScene();
	// ���b�V���t�B�[���h���擾
	MeshField* _MF = _Scene->GetGameObject<MeshField>();

	// �U���N�[���_�E������
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

	// �r�w�C�r�A�c���[����
	m_Behavior->Update();

	GameObject::Update();

	if (!m_isDead)
	{
		// ���b�V���t�B�[���h������ꍇ�͍����𐧌�����
		if (_MF != NULL)
		{
			m_Position.y = _MF->GetHeight(m_Position);
		}
	}
}

void Minion::AttackEvent()
{
	Scene* _Scene = Manager::GetScene();
	// �{�b�N�X�L���X�g�̒u�����W
	D3DXVECTOR3 _Origin;
	// �{�b�N�X�L���X�g�̃T�C�Y
	D3DXVECTOR3 _Size;
	// �{�b�N�X�L���X�g�ϐ�
	PhysicsCast* _Phy;

	// �{�X�̑O�ɒu��
	_Origin = m_Position + (GetForward() * -2.5f);
	// Y��0�ɂ���
	_Origin.y = m_Position.y;
	// �T�C�Y�𒲐�
	_Size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	// �{�b�N�X�L���X�g
	_Phy = PhysicsCast::PhysicBoxCast<Player>(_Origin, _Size);
	if (_Phy != NULL)
	{
		_Phy->GetColldeObj()->DealDamage(1);
	}
}

void Minion::DealDamage(float Damage)
{
	if (m_isDead) return;

	// �`���[�g���A���̏ꍇ�̓`���[�g���A���̃_���[�W�󂯂��p�r�w�C�r�A�ɕς��
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
		// �_���[�W�󂯂�r�w�C�r�A�ɕς��
		ChangeBehavior<MinionBehaviorTree_BeenHit>();
	}

}
