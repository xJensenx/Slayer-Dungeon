#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "Sword.h"
#include "SwordStatus.h"
#include "Player.h"
#include "Math.h"
#include "PhysicsCast.h"
#include "Minion.h"
#include "Boss.h"
#include "Camera.h"
#include "MeshField.h"

void SwordIdle::Init()
{
	// �L�����N�^�[���擾
	m_Character = m_Sword->GetCharacter();

	// �������W��ݒu
	m_InitPos = m_Sword->GetPosition();
	// ���Ԃ�������
	m_CurShootTime = 0.0f;
}

void SwordIdle::Update()
{
	// �L�����N�^�[��NULL��������return
	if (m_Character == NULL) return;

	// ���Ԍo�ߒ����ƌ���u���ꏊ�܂ňړ�������
	if (m_CurShootTime < m_TotalIdleTime)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / m_TotalIdleTime;

		// �v���C���[�̍��W��Right
		D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
		PlayerPos.y += 1.0f;
		D3DXVECTOR3 PlayerRight = m_Character->GetRight();
		D3DXVECTOR3 PlayerRot = m_Character->GetRotation();
		// �u���ꏊ�̕ϐ�
		D3DXVECTOR3 PlacePos;
		// �v���C���[�Ƃǂ̂��炢����邩
		float DistanceBetween = 0.75f;
		// �ϐ��p��
		D3DXVECTOR2 PlaceValue;
		float Angle = 0.0f;
		float ValueXZ = 0.0f;
		float ValueY = 0.0f;

		// Lerp�p�ϐ�
		D3DXVECTOR3 LerpPos;	

		// ���̒u���Ă�ʒu
		Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

		// �u���Ă�ꏊ�ɂ���ăv���C���[�̎w�肵�����W�ɒu��
		switch (m_SwordPos)
		{
		case Sword::SwordPosition::First:
			PlaceValue = D3DXVECTOR2(0.5f, 0.3f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Second:
			PlaceValue = D3DXVECTOR2(0.3f, 0.5f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Third:
			PlaceValue = D3DXVECTOR2(0.0f, 0.5f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Fourth:
			PlaceValue = D3DXVECTOR2(-0.3f, 0.5f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		case Sword::SwordPosition::Fifth:
			PlaceValue = D3DXVECTOR2(-0.5f, 0.3f);
			Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
			break;
		}


		// ���̍��W���v�Z���Ēu���܂�
		ValueXZ = DistanceBetween * cosf(Angle);
		PlayerRight *= ValueXZ;
		ValueY = DistanceBetween * sinf(Angle);

		PlacePos.x = PlayerPos.x + PlayerRight.x;
		PlacePos.y = PlayerPos.y + ValueY;
		PlacePos.z = PlayerPos.z + PlayerRight.z;

		// �|�W�V������Lerp
		D3DXVec3Lerp(&LerpPos, &m_InitPos, &PlacePos, T);
		m_Sword->SetPosition(LerpPos);
	}
	else
	{
		// ���W�X�V
		{
			// �v���C���[�̍��W��Right
			D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
			PlayerPos.y += 1.0f;
			D3DXVECTOR3 PlayerRight = m_Character->GetRight();
			D3DXVECTOR3 PlayerRot = m_Character->GetRotation();
			// �u���ꏊ�̕ϐ�
			D3DXVECTOR3 PlacePos;
			// �v���C���[�Ƃǂ̂��炢����邩
			float DistanceBetween = 0.75f;
			// �ϐ��p��
			D3DXVECTOR2 PlaceValue;
			float Angle = 0.0f;
			float ValueXZ = 0.0f;
			float ValueY = 0.0f;
			D3DXVECTOR3 RotationValue;

			Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

			// �u���Ă�ꏊ�ɂ���ăv���C���[�̎w�肵�����W�ɒu��
			switch (m_SwordPos)
			{
			case Sword::SwordPosition::First:
				PlaceValue = D3DXVECTOR2(0.5f, 0.3f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);



				break;
			case Sword::SwordPosition::Second:
				PlaceValue = D3DXVECTOR2(0.3f, 0.5f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

				break;
			case Sword::SwordPosition::Third:
				PlaceValue = D3DXVECTOR2(0.0f, 0.5f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
				break;
			case Sword::SwordPosition::Fourth:
				PlaceValue = D3DXVECTOR2(-0.3f, 0.5f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);

				break;
			case Sword::SwordPosition::Fifth:
				PlaceValue = D3DXVECTOR2(-0.5f, 0.3f);
				Angle = Math::GetAngle(PlaceValue.y, PlaceValue.x);
				break;
			}

			switch (m_IdleState)
			{
			case 0:
				m_IdleAnimTime += 1.0f / Manager::Time;
				if (m_IdleAnimTime >= 1.0f)
				{
					m_IdleState = 1;
				}
				break;
			case 1:
				m_IdleAnimTime -= 1.0f / Manager::Time;
				if (m_IdleAnimTime <= 0.0f)
				{
					m_IdleState = 0;
				}
				break;
			}

			// �����Ă��銴����\���܂�
			float MoveAmt = Math::FloatLerp(0.0f, 0.2f, m_IdleAnimTime);

			// �\�[�h��Up���擾�iQuaternion���g���Ă���̂�Quaternion�p��Up�Ōv�Z���Ă��܂��j
			D3DXVECTOR3 Up = m_Sword->GetQuaternionUp() * MoveAmt;

			// ���W�v�Z
			ValueXZ = DistanceBetween * cosf(Angle);
			PlayerRight *= ValueXZ;
			ValueY = DistanceBetween * sinf(Angle);

			PlacePos.x = PlayerPos.x + PlayerRight.x;
			PlacePos.y = PlayerPos.y + ValueY;
			PlacePos.z = PlayerPos.z + PlayerRight.z;

			// ��]
			D3DXQUATERNION Q = Math::QuaternionLookAt(PlacePos, m_Character->GetPosition());
			m_Sword->SetQuaternion(Q);

			PlacePos.y += Up.y;
			PlacePos.x += Up.x;

			m_Sword->SetPosition(PlacePos);
		}
	}

}

void SwordShoot::Init()
{
	// �L�����N�^�[���擾
	m_Character = m_Sword->GetCharacter();

	// �ڕW�����݂��Ȃ��ƑO�Ɍ����܂�
	if (m_Sword->GetTargetObj() == NULL)
	{
		m_TargetPos = m_Sword->GetTargetPos();
	}
	else
	{
		// ���݂���ƖڕW�܂Ō����܂�
		m_TargetObj = m_Sword->GetTargetObj();
	}
	// ������
	m_CurShootTime = 0.0f;
	m_InitPos = m_Sword->GetPosition();
	m_InitUp = m_Sword->GetQuaternionUp();
}

void SwordShoot::Update()
{
	// �J�����擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// �ł��Ă鎞�Ԃ��������ԓ��ɖڕW�Ɠ�����Ȃ��Ə�����
	if (m_CurShootTime < m_TotalShootTime)
	{
		// ���ԑ���
		m_CurShootTime++;
		// 1.0�ȓ��̒��������
		float T = m_CurShootTime / m_TotalShootTime;

		// �G���~�[�g�Ȑ��ɑ������ϐ�
		D3DXVECTOR3 HermitePos;
		// �������W
		D3DXVECTOR3 InitPos = m_InitPos;
		// �ړI���W
		D3DXVECTOR3 TargetPos;
		if (m_TargetObj != NULL)
		{
			TargetPos = m_TargetObj->GetPosition();

			TargetPos.y += 1.5f;
		}
		else
		{
			TargetPos = m_TargetPos;
		}
		// Tangent1
		D3DXVECTOR3 Tangent1;
		// Tangent2
		D3DXVECTOR3 Tangent2;

		// Tangent�̒l�擾
		Tangent1 = m_InitUp * 25.0f;
		Tangent2 = -Tangent1;

		// �G���~�[�g�Ȑ��v�Z
		D3DXVec3Hermite(&HermitePos, &InitPos, &Tangent1, &TargetPos, &Tangent2, T);

		// ��]����
		// �������v�Z���܂�
		D3DXVECTOR3 Dir = HermitePos - m_Sword->GetPosition();
		//D3DXVec3Normalize(&Dir, &Dir);

		D3DXQUATERNION Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// �|�W�V�������X�V����
		m_Sword->SetPosition(HermitePos);

		// �G�t�F�N�g
		m_Sword->TrailEffect();
	}
	else
	{
		// �{�b�N�X�L���X�g�p�ϐ�
		std::vector<PhysicsCast*> _Phy;
		PhysicsCast* _PhyBoss;

		// �{�b�N�X�L���X�g
		_Phy = PhysicsCast::AllPhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
		// �������Ă���ƃG�t�F�N�g���o���Ĕj�󂷂�
		for (auto P : _Phy)
		{
			P->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		}
		// �{�b�N�X�L���X�g
		_PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
		// �������Ă���ƃG�t�F�N�g���o���Ĕj�󂷂�
		if (_PhyBoss != NULL)
		{
			_PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		}
		m_Sword->HitEffect(m_Sword->GetPosition());
		// �J�����V�F�[�N�f�o�b�O
		if (_Camera != NULL)
		{
			_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
		}
		// �I�u�W�F�N�g�������܂�
		m_Sword->SetDestroy();
		return;
	}


}

void SwordAttack::Init()
{
	// �L�����N�^�[���擾
	m_Character = m_Sword->GetCharacter();

	// ������
	m_Damaged = false;
	m_InitPos = m_Sword->GetPosition();
	m_InitUp = m_Sword->GetInitUp();
	m_EndPos = m_Sword->GetEndPos();
	m_EndTan = m_Sword->GetEndTan();
	m_CurShootTime = 0.0f;
	m_TotalAttackTime = m_Sword->GetTotalAtkTime();
}

void SwordAttack::Update()
{
	if (m_Character == NULL) return;

	// �U��
	if (m_CurShootTime < m_TotalAttackTime)
	{
		// ���ԑ���
		m_CurShootTime++;
		// 1.0�ȓ��̒��������
		float T = m_CurShootTime / m_TotalAttackTime;

		// �G���~�[�g�Ȑ��ɑ������ϐ�
		D3DXVECTOR3 HermitePos;
		// �������W
		D3DXVECTOR3 InitPos = m_InitPos;
		// �ړI���W
		D3DXVECTOR3 TargetPos = m_EndPos;
		// Tangent1
		D3DXVECTOR3 Tangent1 = m_InitUp;
		// Tangent2
		D3DXVECTOR3 Tangent2 = m_EndTan;

		// �G���~�[�g�Ȑ��v�Z
		D3DXVec3Hermite(&HermitePos, &InitPos, &Tangent1, &TargetPos, &Tangent2, T);

		// ��]����
		// �������v�Z���܂�
		D3DXVECTOR3 Dir = HermitePos - m_Sword->GetPosition();
		//D3DXVec3Normalize(&Dir, &Dir);

		D3DXQUATERNION Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// �|�W�V�������X�V����
		m_Sword->SetPosition(HermitePos);

		// �g���[���G�t�F�N�g
		m_Sword->TrailEffect();

		// �_���[�W�������ǂ���
		if (!m_Damaged)
		{
			// �{�b�N�X�L���X�g�p�ϐ�
			PhysicsCast* PhyBoss;
			PhysicsCast* PhyMinion;

			// Minion�̃{�b�N�X�L���X�g
			PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition() , D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyMinion != NULL)
			{
				Manager::PauseFor(0.1f);

				m_Character->AddMp(5.0f);
				PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
			// Boss�̃{�b�N�X�L���X�g
			PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyBoss != NULL)
			{
				Manager::PauseFor(0.1f);

				m_Character->AddMp(5.0f);
				PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
		}
	}
	else
	{
		// ���̋O�Ղ�������
		m_Sword->InitSwordTrail();
		// �ړI�n�܂ōs�����̂ŏ����܂�
		m_Sword->SetDestroy();
		return;
	}

}

void SwordBlock::Init()
{
	// �L�����N�^�[���擾
	m_Character = m_Sword->GetCharacter();
	// ������
	m_InitQua = m_Sword->GetQuaternion();
	m_InitPos = m_Sword->GetPosition();
	m_CurShootTime = 0.0f;
}

void SwordBlock::Update()
{
	// �L�����N�^�[��NULL����return
	if (m_Character == NULL) return;

	// �h��
	if (m_CurShootTime < m_TotalBlockTime)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / m_TotalBlockTime;
		// Lerp�p�ϐ�
		D3DXVECTOR3 LerpPos;
		// �v���C���[�̍��W
		D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
		// �v���C���[��Forward
		D3DXVECTOR3 PlayerFor = -m_Character->GetForward();
		// �v���C���[��Right
		D3DXVECTOR3 PlayerRig = -m_Character->GetRight();
		// ���̍��W
		D3DXVECTOR3 NextPos;
		// ���`��ԗp
		D3DXQUATERNION LerpQua;
		// ����Quaternion
		D3DXQUATERNION NextQua;
		// Quaternion�̏�����
		D3DXQuaternionIdentity(&NextQua);

		// ���̒u���ʒu���擾
		Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

		// �u���ʒu�ɂ���Ď��̍��W���X�V���܂�
		switch (m_SwordPos)
		{
		case Sword::SwordPosition::First:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos -= (PlayerRig * 0.5f);
			NextPos.y += 0.8f;
			break;
		case Sword::SwordPosition::Second:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos -= (PlayerRig * 0.25f);
			NextPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Third:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos.y += 1.0f;
			break;
		case Sword::SwordPosition::Fourth:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos += (PlayerRig * 0.25f);
			NextPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Fifth:
			NextPos = PlayerPos + (PlayerFor * 1.0f);
			NextPos += (PlayerRig * 0.5f);
			NextPos.y += 0.8f;
			break;
		}

		// ���`���
		D3DXVec3Lerp(&LerpPos, &m_InitPos, &NextPos, T);
		// ���W�ݒu
		m_Sword->SetPosition(LerpPos);
		// Quaternion��Slerp�i���`��ԁj
		D3DXQuaternionSlerp(&LerpQua, &m_InitQua, &NextQua, T);
		
	}
	else
	{
		// ���`��ԗp���W
		D3DXVECTOR3 LerpPos;
		// �v���C���[�̍��W
		D3DXVECTOR3 PlayerPos = m_Character->GetPosition();
		// �v���C���[��Forward
		D3DXVECTOR3 PlayerFor = -m_Character->GetForward();
		// �v���C���[��Right
		D3DXVECTOR3 PlayerRig = -m_Character->GetRight();

		// �\�[�h�̈ʒu
		Sword::SwordPosition m_SwordPos = m_Sword->GetSwordPos();

		// �\�[�h�̈ʒu�ɂ���č��W�ύX���܂�
		switch (m_SwordPos)
		{
		case Sword::SwordPosition::First:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos -= (PlayerRig * 0.5f);
			LerpPos.y += 0.8f;
			break;
		case Sword::SwordPosition::Second:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos -= (PlayerRig * 0.25f);
			LerpPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Third:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos.y += 1.0f;
			break;
		case Sword::SwordPosition::Fourth:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos += (PlayerRig * 0.25f);
			LerpPos.y += 0.9f;
			break;
		case Sword::SwordPosition::Fifth:
			LerpPos = PlayerPos + (PlayerFor * 1.0f);
			LerpPos += (PlayerRig * 0.5f);
			LerpPos.y += 0.8f;
			break;
		}

		// ���W�ݒu
		m_Sword->SetPosition(LerpPos);
	}

}

void SwordUlt::Init()
{
	m_Character = m_Sword->GetCharacter();

	m_isShake = false;
	m_ShakeStr = m_Sword->GetShakeStr();
	m_CurShootTime = 0.0f;
}

void SwordUlt::Update()
{
	Scene* _Scene = Manager::GetScene();
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// �������x
	D3DXVECTOR3 NextPos = D3DXVECTOR3(m_Sword->GetPosition().x, m_Sword->GetPosition().y - 0.6f, m_Sword->GetPosition().z);

	D3DXQUATERNION Q;
	D3DXVECTOR3 Axis = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXQuaternionRotationAxis(&Q, &Axis, Math::PI());
	m_Sword->SetQuaternion(Q);

	m_Sword->SetPosition(NextPos);
	
	D3DXVECTOR3 _Position = m_Sword->GetPosition();
	D3DXVECTOR3 _Scale = m_Sword->GetScale();

	if (_MeshField != NULL)
	{
		if (_Position.y <= _MeshField->GetHeight(_Position) + (_Scale.y * 1.5f))
		{
			m_Sword->SetPosition(D3DXVECTOR3(m_Sword->GetPosition().x, _MeshField->GetHeight(_Position) + (_Scale.y * 1.5f), m_Sword->GetPosition().z));
			// �G�t�F�N�g
			m_Sword->TrailEffect();

			if (!m_isShake)
			{
				_Camera->ShakeCam(D3DXVECTOR3(m_ShakeStr, m_ShakeStr, 0.0f), 0.33f);
				m_isShake = true;
			}

			m_CurShootTime++;

			// �_���[�W�������ǂ���
			if (!m_Damaged)
			{
				// �{�b�N�X�L���X�g�p�ϐ�
				PhysicsCast* PhyBoss;
				PhysicsCast* PhyMinion;

				// Minion�̃{�b�N�X�L���X�g
				PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(_Position, D3DXVECTOR3(5.0f, 5.0f, 5.0f));
				if (PhyMinion != NULL)
				{
					PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
					D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
					EffectPos.y += 1.0f;
					m_Sword->HitEffect(EffectPos);
					m_Damaged = true;
				}
				// Boss�̃{�b�N�X�L���X�g
				PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(_Position, D3DXVECTOR3(5.0f, 5.0f, 5.0f));
				if (PhyBoss != NULL)
				{
					PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
					D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
					EffectPos.y += 1.0f;
					m_Sword->HitEffect(EffectPos);
					m_Damaged = true;
				}
			}

			if (m_CurShootTime >= m_TotalShootTime)
			{
				// ���̋O�Ղ�������
				m_Sword->InitSwordTrail();

				m_Sword->DissolveEffect();
				m_Sword->SetDestroy();
				return;
			}
		}
	}

}

void SwordQTE::Init()
{
	m_Character = m_Sword->GetCharacter();

	m_InitPos = m_Sword->GetPosition();
	m_EndPos = m_Sword->GetEndPos();
	m_CurShootTime = 0.0f;
}

void SwordQTE::Update()
{
	// QTE�p
	if (m_CurShootTime < 3.0f * Manager::Time)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / (3.0f * Manager::Time);

		// ���`��ԗp�ϐ�
		D3DXVECTOR3 LerpPos;

		D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_EndPos, T);

		D3DXQUATERNION Q = Math::QuaternionLookAt(LerpPos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		m_Sword->SetPosition(LerpPos);

		if (m_CurShootTime >= 2.8f * Manager::Time)
		{
			m_Sword->HitEffect(m_Sword->GetPosition());
			m_Sword->SetDestroy();
			return;
		}
	}
	else
	{
		m_Sword->HitEffect(m_Sword->GetPosition());
		m_Sword->SetDestroy();
		return;
	}

}

void SwordShootStraight::Init()
{
	m_CurShootTime = 0.0f;
	m_InitPos = m_Sword->GetPosition();
	m_TargetPos = m_Sword->GetTargetPos();
	
}

void SwordShootStraight::Update()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	if (m_CurShootTime < m_TotalShootTime)
	{
		m_CurShootTime++;

		float T = m_CurShootTime / m_TotalShootTime;

		// �������W
		D3DXVECTOR3 InitPos = m_InitPos;
		// �ړI���W
		D3DXVECTOR3 TarPos = m_TargetPos;
		// Lerp�p
		D3DXVECTOR3 LerpPos;

		// ���`���
		D3DXVec3Lerp(&LerpPos, &InitPos, &TarPos, T);

		D3DXQUATERNION Q = Math::QuaternionLookAt(LerpPos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);
		// ���W�X�V
		m_Sword->SetPosition(LerpPos);
		// �G�t�F�N�g
		m_Sword->TrailEffect();

		// �_���[�W����
		PhysicsCast* _Boss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Boss != NULL)
		{
			// �J�����V�F�[�N�f�o�b�O
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}

			_Boss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
			m_Sword->SetDestroy();
			return;
		}
		// �_���[�W����
		PhysicsCast* _Minion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Minion != NULL)
		{
			// �J�����V�F�[�N�f�o�b�O
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}

			_Minion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
			m_Sword->SetDestroy();
			return;
		}

	}
	else
	{
		// �_���[�W����
		PhysicsCast* _Boss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Boss != NULL)
		{
			// �J�����V�F�[�N�f�o�b�O
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}


			_Boss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
		}
		// �_���[�W����
		PhysicsCast* _Minion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
		if (_Minion != NULL)
		{
			// �J�����V�F�[�N�f�o�b�O
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}


			_Minion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			m_Sword->HitEffect(m_Sword->GetPosition());
		}

		// ���̋O�Ղ�������
		m_Sword->InitSwordTrail();

		m_Sword->SetDestroy();
		return;
	}
}

void SwordChargeShoot::Init()
{
	// �L�����N�^�[�擾
	m_Character = m_Sword->GetCharacter();

	// Charge���������Ă����
	m_TargetPos = m_Character->GetPosition();
	m_TargetPos.y += 2.0f;
	// �������W
	switch (m_Sword->GetSwordPos())
	{
	case Sword::First:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.5f + m_Character->GetRight() * 3.0f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Second:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.75f + m_Character->GetRight() * 1.5f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Third:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 2.0f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Fourth:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.75f - m_Character->GetRight() * 1.5f;
		m_InitPos.y += 2.0f;
		break;
	case Sword::Fifth:
		m_InitPos = m_Character->GetPosition() - m_Character->GetForward() * 1.5f - m_Character->GetRight() * 3.0f;
		m_InitPos.y += 2.0f;
		break;
	}

	m_Direction = m_InitPos - m_TargetPos;

	// �`���[�W���ԏ�����
	m_ChargeTime = 0.0f;
	// �����ԏ�����
	m_CurShootTime = 0.0f;
	// �`���[�W�X�e�[�g
	m_ChargeState = 0;
}

void SwordChargeShoot::Update()
{
	switch (m_ChargeState)
	{
	case 0:
		if (m_ChargeTime < m_FullChargeTime)
		{
			m_ChargeTime++;
			float T = m_ChargeTime / m_FullChargeTime;
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_TargetPos, T);

			D3DXQUATERNION Q = Math::QuaternionLookAt(m_InitPos, m_TargetPos);
			m_Sword->SetQuaternion(Q);

			m_Sword->SetPosition(LerpPos);
		}
		else
		{
			m_ChargeState = 1;
		}
		break;
	case 1:
		if (m_CurShootTime < 3.0f * Manager::Time)
		{
			m_CurShootTime++;
			
			D3DXVECTOR3 MoveValue = m_Sword->GetPosition() + m_Direction * 0.1f;

			D3DXQUATERNION Q = Math::QuaternionLookAt(MoveValue, m_Sword->GetPosition());
			m_Sword->SetQuaternion(Q);

			m_Sword->SetPosition(MoveValue);
			// �G�t�F�N�g
			m_Sword->TrailEffect();

			PhysicsCast* PhyMinion;
			PhysicsCast* PhyBoss;
			// Minion�̃{�b�N�X�L���X�g
			PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
			if (PhyMinion != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Sword->SetDestroy();
				return;
			}
			// Boss�̃{�b�N�X�L���X�g
			PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
			if (PhyBoss != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Sword->SetDestroy();
				return;
			}
		}
		else
		{
			// ���̋O�Ղ�������
			m_Sword->InitSwordTrail();

			m_Sword->SetDestroy();
			return;
		}
		break;
	}
}

void SwordSkill05::Init()
{
	// �L�����N�^�[�擾
	m_Character = m_Sword->GetCharacter();

	// �p�x������
	m_Angle = 0.0f;

	// �_���[�W����bool��������
	m_Damaged = false;
}

void SwordSkill05::Update()
{
	// �v���C���[�̍��W
	D3DXVECTOR3 CharPos = m_Character->GetPosition();
	CharPos.y += 1.5f;
	// ������ݒu
	float Dist = 1.0f;
	// �u���p�x
	float _PlaceAngle;

	// ���̒u���ꏊ�ɂ���ĕς��
	switch (m_Sword->GetSwordPos())
	{
	case Sword::First:
		// �F�̕ύX
		m_Sword->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		_PlaceAngle = (72.0f * 1) + m_Angle;
		break;
	case Sword::Second:
		// �F�̕ύX
		m_Sword->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		_PlaceAngle = (72.0f * 2) + m_Angle;
		break;
	case Sword::Third:
		// �F�̕ύX
		m_Sword->ChangeTrailColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
		_PlaceAngle = (72.0f * 3) + m_Angle;
		break;
	case Sword::Fourth:
		// �F�̕ύX
		m_Sword->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f));
		_PlaceAngle = (72.0f * 4) + m_Angle;
		break;
	case Sword::Fifth:
		// �F�̕ύX
		m_Sword->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f));
		_PlaceAngle = (72.0f * 5) + m_Angle;
		break;
	}

	// ���W���v�Z����
	float RightValue = cosf(_PlaceAngle * Dist);
	float ForwardValue = sinf(_PlaceAngle * Dist);
	// �����Ă��������ݒu
	D3DXVECTOR3 PointTarget = CharPos;
	// ���W��ݒu
	CharPos += -m_Character->GetRight() * RightValue;
	CharPos += -m_Character->GetForward() * ForwardValue;
	m_Sword->SetPosition(CharPos);

	// ��]������
	D3DXQUATERNION Q = Math::QuaternionLookAt(CharPos, PointTarget);
	m_Sword->SetQuaternion(Q);

	// ���̋O�ՃG�t�F�N�g
	m_Sword->TrailEffect();

	// �p�x�𑫂�
	m_Angle += 0.2f;

	if (m_Damaged) return;

	// �J�����擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// �_���[�W����
	PhysicsCast* PhyMinion;
	PhysicsCast* PhyBoss;
	// Minion�̃{�b�N�X�L���X�g
	PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	if (PhyMinion != NULL)
	{
		// �J�����V�F�[�N�f�o�b�O
		if (_Camera != NULL)
		{
			_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
		}
		m_Damaged = true;
		PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
		EffectPos.y += 1.0f;
		m_Sword->HitEffect(EffectPos);
		return;
	}
	// Boss�̃{�b�N�X�L���X�g
	PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
	if (PhyBoss != NULL)
	{
		// �J�����V�F�[�N�f�o�b�O
		if (_Camera != NULL)
		{
			_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
		}
		m_Damaged = true;
		PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
		D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
		EffectPos.y += 1.0f;
		m_Sword->HitEffect(EffectPos);
		return;
	}
}

void SwordSkill06::Init()
{
	// �����ԏ�����
	m_CurShootTime = 0.0f;

	// �������W�L�^
	m_InitPos = m_Sword->GetPosition();

	// �ڕW�����݂��Ă��Ȃ���
	if (m_Sword->GetTargetObj() == NULL)
	{
		// �ڕW���W�i�O�Ɍ��j
		m_TargetPos = m_Sword->GetTargetPos();
	}
	else
	{
		// �ڕW���W�i�^�[�Q�b�g�Ɍ��j
		m_TargetObj = m_Sword->GetTargetObj();
	}

	// ����Tan
	m_InitUp = m_Sword->GetInitUp();

	// ���񐔂��L�^
	m_ShootCnt = m_Sword->GetShootCnt();

	// �T�C�Y��傫������
	m_Sword->SetScale(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
}

void SwordSkill06::Update()
{
	if (m_CurShootTime < m_TotalShootTime)
	{
		m_CurShootTime++;
		float T = m_CurShootTime / m_TotalShootTime;

		// �G���~�[�g�p
		D3DXVECTOR3 HermitePos;
		// �������W
		D3DXVECTOR3 InitPos = m_InitPos;
		// �I�_���W
		D3DXVECTOR3 TargetPos;
		if (m_TargetObj != NULL)
		{
			TargetPos = m_TargetObj->GetPosition();
			TargetPos.y += 1.5f;
		}
		else
		{
			TargetPos = m_TargetPos;
		}
		// ����Tangent
		D3DXVECTOR3 InitTan = m_InitUp * 25.0f;
		// �I�_Tangent
		D3DXVECTOR3 TargetTan = -m_InitUp * 25.0f;

		// �G���~�[�g
		D3DXVec3Hermite(&HermitePos, &InitPos, &InitTan, &TargetPos, &TargetTan, T);

		// ��]�v�Z
		D3DXQUATERNION Q;
		Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// ���W�ݒu
		m_Sword->SetPosition(HermitePos);

		// �G�t�F�N�g
		m_Sword->TrailEffect();
	}
	else
	{
		// �_���[�W�C�x���g
		// Minion�̃{�b�N�X�L���X�g
		PhysicsCast* PhyMinion;
		PhysicsCast* PhyBoss;
		// �V�[���擾
		Scene* _Scene = Manager::GetScene();
		// �J�����擾
		Camera* _Camera = _Scene->GetGameObject<Camera>();

		PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
		if (PhyMinion != NULL)
		{
			// �J�����V�F�[�N�f�o�b�O
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}
			PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
			EffectPos.y += 1.0f;
			m_Sword->HitEffect(EffectPos);
		}
		// Boss�̃{�b�N�X�L���X�g
		PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(5.0f, 5.0f, 5.0f));
		if (PhyBoss != NULL)
		{
			// �J�����V�F�[�N�f�o�b�O
			if (_Camera != NULL)
			{
				_Camera->ShakeCam(D3DXVECTOR3(0.0f, 0.01f, 0.0f), 0.25f);
			}
			PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
			D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
			EffectPos.y += 1.0f;
			m_Sword->HitEffect(EffectPos);
		}


		// ���񐔂����炷
		m_ShootCnt--;
		if (m_ShootCnt <= 0)
		{
			// ���̋O�Ղ�������
			m_Sword->InitSwordTrail();

			m_Sword->SetDestroy();
			return;
		}
		else
		{
			// ���񐔂��܂�����ꍇ�������s���܂�
			// ���ԏ�����
			m_CurShootTime = 0.0f;
			// ���ݍ��W���X�V���܂�
			m_InitPos = m_Sword->GetPosition();
			// ����Tangent�X�V
			m_InitUp = -m_Sword->GetQuaternionUp() * 2.0f;
		}
	}
}

void SwordAttack_ForSkill::Init()
{
	// �L�����N�^�[���擾
	m_Character = m_Sword->GetCharacter();

	// ������
	m_Damaged = false;
	m_InitPos = m_Sword->GetPosition();
	m_InitUp = m_Sword->GetInitUp();
	m_EndPos = m_Sword->GetEndPos();
	m_EndTan = m_Sword->GetEndTan();
	m_CurShootTime = 0.0f;
	m_TotalAttackTime = m_Sword->GetTotalAtkTime();

}

void SwordAttack_ForSkill::Update()
{
	if (m_Character == NULL) return;

	// �U��
	if (m_CurShootTime < m_TotalAttackTime)
	{
		// ���ԑ���
		m_CurShootTime++;
		// 1.0�ȓ��̒��������
		float T = m_CurShootTime / m_TotalAttackTime;

		// �G���~�[�g�Ȑ��ɑ������ϐ�
		D3DXVECTOR3 HermitePos;
		// �������W
		D3DXVECTOR3 InitPos = m_InitPos;
		// �ړI���W
		D3DXVECTOR3 TargetPos = m_EndPos;
		// Tangent1
		D3DXVECTOR3 Tangent1 = m_InitUp;
		// Tangent2
		D3DXVECTOR3 Tangent2 = m_EndTan;

		// �G���~�[�g�Ȑ��v�Z
		D3DXVec3Hermite(&HermitePos, &InitPos, &Tangent1, &TargetPos, &Tangent2, T);

		// ��]����
		// �������v�Z���܂�
		D3DXVECTOR3 Dir = HermitePos - m_Sword->GetPosition();
		//D3DXVec3Normalize(&Dir, &Dir);

		D3DXQUATERNION Q = Math::QuaternionLookAt(HermitePos, m_Sword->GetPosition());
		m_Sword->SetQuaternion(Q);

		// �|�W�V�������X�V����
		m_Sword->SetPosition(HermitePos);

		// �g���[���G�t�F�N�g
		m_Sword->TrailEffect();

		// �_���[�W�������ǂ���
		if (!m_Damaged)
		{
			// �{�b�N�X�L���X�g�p�ϐ�
			PhysicsCast* PhyBoss;
			PhysicsCast* PhyMinion;

			// Minion�̃{�b�N�X�L���X�g
			PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyMinion != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyMinion->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyMinion->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
			// Boss�̃{�b�N�X�L���X�g
			PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Sword->GetPosition(), D3DXVECTOR3(2.0f, 4.0f, 2.0f));
			if (PhyBoss != NULL)
			{
				Manager::PauseFor(0.1f);

				PhyBoss->GetColldeObj()->DealDamage(m_Sword->GetAtkDmg());
				D3DXVECTOR3 EffectPos = PhyBoss->GetColldeObj()->GetPosition();
				EffectPos.y += 1.0f;
				m_Sword->HitEffect(EffectPos);
				m_Damaged = true;
			}
		}
	}
	else
	{
		// ���̋O�Ղ�������
		m_Sword->InitSwordTrail();
		// �ړI�n�܂ōs�����̂ŏ����܂�
		m_Sword->SetDestroy();
		return;
	}

}
