#include "main.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "AttackFireBall.h"
#include "AttackFireBall_Type.h"
#include "PhysicsCast.h"
#include "Player.h"
#include "Camera.h"
#include "Effect.h"

void AttackFireBall_Type_ShootTowardsTarget::Init()
{
	// �i�s�����ԏ�����
	m_CurTime = 0.0f;
	// �ڕW�܂ł̎���
	m_TotalTime = 1.0f * Manager::Time;
	// �������W
	m_InitPos = m_FireBall->GetPosition();
}

void AttackFireBall_Type_ShootTowardsTarget::Update()
{
	// �ڕW
	if (m_TargetObj == NULL) return;

	if (m_CurTime < m_TotalTime)
	{
		m_CurTime++;
		float T = m_CurTime / m_TotalTime;

		// ���`��ԗp���W
		D3DXVECTOR3 LerpPos;
		D3DXVECTOR3 TargetPos = m_TargetObj->GetPosition();
		
		// ���`���
		D3DXVec3Lerp(&LerpPos, &m_InitPos, &TargetPos, T);

		// ���W�ݒu
		m_FireBall->SetPosition(LerpPos);

		// �_���[�W����
		DamageEvent();
	}
	else
	{
		// �ړI�n�ɓ��B������j�󂷂�
		m_FireBall->SetDestroy();
		return;
	}
}

void AttackFireBall_Type_HermiteShoot::Init()
{
	// �i�s�����ԏ�����
	m_CurTime = 0.0f;
	// �ڕW�܂ł̎���
	m_TotalTime = 0.75f * Manager::Time;
	// �������W
	m_InitPos = m_FireBall->GetPosition();

}

void AttackFireBall_Type_HermiteShoot::Update()
{
	// �^�[�Q�b�g�����݂��Ȃ���return���܂�
	if (m_TargetObj == NULL) return;

	if (m_CurTime < m_TotalTime)
	{
		m_CurTime++;
		float T = m_CurTime / m_TotalTime;

		// �G���~�[�g�p
		D3DXVECTOR3 HermitePos;

		// Tan1
		D3DXVECTOR3 ShootTan = m_FireBall->GetHermiteTan();

		// Tan2
		D3DXVECTOR3 TargetTan = m_TargetObj->GetForward();

		// �^�[�Q�b�g�̖ڕW
		D3DXVECTOR3 TargetPos = m_TargetObj->GetPosition();

		// �G���~�[�g
		D3DXVec3Hermite(&HermitePos, &m_InitPos, &ShootTan, &TargetPos, &TargetTan, T);

		m_FireBall->SetPosition(HermitePos);

		DamageEvent();
	}
	else
	{
		// �ړI�n�ɓ��B������j�󂷂�
		m_FireBall->SetDestroy();
		return;
	}
}

void AttackFireBall_Type::DamageEvent()
{
	// �����̃|�W�V����
	D3DXVECTOR3 _Pos = m_FireBall->GetPosition();

	// �T�C�Y�擾
	float _Size = m_FireBall->GetScale().x - 0.1f;

	// PhysicsCast����
	PhysicsCast* _Phy = PhysicsCast::PhysicsSphereCast<Player>(_Pos, _Size);

	// �v���C���[�ɓ�����Ȃ���return����
	if (_Phy == NULL) return;

	// �_���[�W��^����
	_Phy->GetColldeObj()->DealDamage(1.0f);
	// �J�����擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// �J�����h���
	_Camera->ShakeCam(D3DXVECTOR3(0.01f, 0.01f, 0.0f), 0.5f);
	EffectEvent();

	m_FireBall->SetDestroy();
	return;
	
}

void AttackFireBall_Type::EffectEvent()
{
	// �G�t�F�N�g����
	Scene* _Scene = Manager::GetScene();
	Effect* _Effect = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);

	_Effect->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	// ��ސݒu
	_Effect->SetEffectType<EffectType_BossMeteor>();
	_Effect->SetPosition(m_FireBall->GetPosition());
}

void AttackFireBall_Type_ChargeShoot::Init()
{
	// �i�s�����ԏ�����
	m_CurTime = 0.0f;
	// �ڕW�܂ł̎���
	m_TotalTime = 1.0f * Manager::Time;
	// �������W
	m_InitPos = m_FireBall->GetPosition();
	// �X�e�[�g�̏�����
	m_State = 0;
	// �����̏�����
	m_Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void AttackFireBall_Type_ChargeShoot::Update()
{
	// �^�[�Q�b�g�����݂��Ȃ���return���܂�
	if (m_TargetObj == NULL) return;

	switch (m_State)
	{
	case 0:
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;
			
			// �p�x����
			float Angle = m_FireBall->GetInitAngle();
			Angle += 0.1f;
			m_FireBall->SetInitAngle(Angle);
			
			// �����ݒu
			float Dist = 2.0f;

			// ���W�v�Z
			D3DXVECTOR3 NextPos = m_TargetObj->GetPosition();
			NextPos.x += cosf(Angle) * Dist;
			NextPos.z += sinf(Angle) * Dist;
			NextPos.y += 1.5f;

			// ���W�ݒu
			m_FireBall->SetPosition(NextPos);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���v���ԍX�V
			m_TotalTime = 0.5f * Manager::Time;

			// ���̃X�e�[�g�ɐi��
			m_State = 1;

			// �����v�Z
			m_Direction = m_FireBall->GetPosition() - m_TargetObj->GetPosition();
			m_Direction.y = 0.0f;
			D3DXVec3Normalize(&m_Direction, &m_Direction);

			m_Direction = m_FireBall->GetPosition() + (m_Direction * 2.0f);

			// �������W�ݒu
			m_InitPos = m_FireBall->GetPosition();
		}
		break;
	case 1:
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;

			float T = m_CurTime / m_TotalTime;

			// ���`��ԗp
			D3DXVECTOR3 LerpPos;

			// ���`���
			D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_Direction, T);

			// ���W�ݒu
			m_FireBall->SetPosition(LerpPos);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���v���ԍX�V
			m_TotalTime = 0.5f * Manager::Time;

			// �������W�X�V
			m_InitPos = m_FireBall->GetPosition();

			// �ڕW���W�ݒu
			m_Direction = m_TargetObj->GetPosition();
			m_Direction.y += 1.5f;

			// �X�e�[�g�X�V
			m_State = 2;
		}
		break;
	case 2:
		if (m_CurTime < m_TotalTime)
		{
			m_CurTime++;
			float T = m_CurTime / m_TotalTime;

			// ���`��ԗp
			D3DXVECTOR3 LerpPos;

			// ���`���
			D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_Direction, T);

			// ���W�ݒu
			m_FireBall->SetPosition(LerpPos);

			// �_���[�W����
			DamageEvent();
		}
		else
		{
			// �_���[�W����
			DamageEvent();

			// �G�t�F�N�g�o��
			EffectEvent();

			// ������j�󂷂�
			m_FireBall->SetDestroy();
			return;
		}
		break;

	}
}
