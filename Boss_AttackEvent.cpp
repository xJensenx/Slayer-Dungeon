#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "PhysicsCast.h"

#include "Boss_AttackEvent.h"
#include "MeshField.h"
#include "Boss.h"
#include "Player.h"
#include "Camera.h"

void Boss_Attack_HeavyAtk::DamageEvent()
{	
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �{�X�̑O�ɒu��
	m_Origin = m_Character->GetPosition() + (m_Character->GetForward() * -2.5f);
	// Y��0�ɂ���
	m_Origin.y = 2.5f;
	// �T�C�Y�𒲐�
	m_Size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	// �{�b�N�X�L���X�g
	m_Phy = PhysicsCast::PhysicBoxCast<Player>(m_Origin, m_Size);
	if (m_Phy != NULL)
	{
		// �_���[�W��^����
		m_Phy->GetColldeObj()->DealDamage(1.0f);
	}
}

void Boss_Attack_JumpAtk::DamageEvent()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// ���b�V���t�B�[���h�̍���
	MeshField* _MF = _Scene->GetGameObject<MeshField>();
	float MeshHeight = _MF->GetHeight(m_Character->GetPosition());

	// �{�X�̑O�ɒu��
	m_Origin = m_Character->GetPosition();
	// Y��0�ɂ���
	m_Origin.y = MeshHeight;
	// �T�C�Y�𒲐�
	m_SphereSize = 7.5f;

	// �U���̃G�t�F�N�g
	m_Character->JumpAtkEffect();

	// �ۃL���X�g
	m_Phy = PhysicsCast::PhysicsSphereCast<Player>(m_Origin, m_SphereSize);

	if (m_Phy != NULL)
	{		
		// �J�����V�F�[�N
		_Scene->GetGameObject<Camera>()->ShakeCam(D3DXVECTOR3(0.025f, 0.025f, 0.0f), 0.7f);

		// �������Q�b�g
		D3DXVECTOR3 DirOfTarget = m_Phy->GetColldeObj()->GetPosition() - m_Character->GetPosition();

		// �\�����Ă����Ԃ��ǂ���
		if (m_Character->GetBossPhase() == Boss::RagePhase)
		{
			// �\�����Ă���ƕ��ʂ̃_���[�W��^����i�\���̃W�����v�U���͂Q�i�U�����邽�߃m�b�N�o�b�N���܂���j
			m_Phy->GetColldeObj()->DealDamage(2.0f);
		}
		else
		{
			// �\���ł͂Ȃ��ƃm�b�N�o�b�N�_���[�W��^����
			m_Phy->GetColldeObj()->KnockBackDamage(2.0f, DirOfTarget);
		}
	}
	

}

void Boss_Attack_JumpAtkSec::DamageEvent()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// ���b�V���t�B�[���h�̍���
	MeshField* _MF = _Scene->GetGameObject<MeshField>();
	float MeshHeight = _MF->GetHeight(m_Character->GetPosition());

	// �{�X�̑O�ɒu��
	m_Origin = m_Character->GetPosition();
	// Y��0�ɂ���
	m_Origin.y = MeshHeight;
	// �T�C�Y�𒲐�
	m_SphereSize = 7.5f;

	// �U���̃G�t�F�N�g
	m_Character->JumpAtkEffect();

	// �ۃL���X�g
	m_Phy = PhysicsCast::PhysicsSphereCast<Player>(m_Origin, m_SphereSize);

	if (m_Phy != NULL)
	{
		// �J�����V�F�[�N
		_Scene->GetGameObject<Camera>()->ShakeCam(D3DXVECTOR3(0.025f, 0.025f, 0.0f), 0.7f);

		// �������Q�b�g
		D3DXVECTOR3 DirOfTarget = m_Phy->GetColldeObj()->GetPosition() - m_Character->GetPosition();

		// �m�b�N�o�b�N�_���[�W��^����
		m_Phy->GetColldeObj()->KnockBackDamage(2.0f, DirOfTarget);
	}

}

void Boss_Attack_KnockBack::DamageEvent()
{	
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �{�X�̑O�ɒu��
	m_Origin = m_Character->GetPosition() + (m_Character->GetForward() * -2.5f);
	// Y��0�ɂ���
	m_Origin.y = 2.5f;
	// �T�C�Y�𒲐�
	m_Size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	// �{�b�N�X�L���X�g
	m_Phy = PhysicsCast::PhysicBoxCast<Player>(m_Origin, m_Size);

	// �U���̃G�t�F�N�g
	m_Character->JumpAtkEffect();

	if (m_Phy != NULL)
	{
		// �J�����V�F�[�N
		_Scene->GetGameObject<Camera>()->ShakeCam(D3DXVECTOR3(0.025f, 0.025f, 0.0f), 0.7f);

		// �������Q�b�g
		D3DXVECTOR3 DirOfTarget = m_Phy->GetColldeObj()->GetPosition() - m_Character->GetPosition();

		// �m�b�N�o�b�N�_���[�W��^����
		m_Phy->GetColldeObj()->KnockBackDamage(2.0f, DirOfTarget);
	}
}
