#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "AudioManager.h"
#include "CollisionOBB.h"
#include "ComponentInclude.h"
#include "input.h"
#include "Scene.h"
#include "Player.h"
#include "EmptyObject.h"
#include "PhysicsCast.h"
#include "Camera.h"
#include "Math.h"
#include "Sea.h"
#include "Sword.h"
#include "MeshField.h"
#include "Minion.h"
#include "PlayerAnimation.h"
#include "LockTarget.h"
#include "Boss.h"
#include "DebugColliderBox.h"
#include "PlayerHpBar.h"
#include "PlayerMpBar.h"
#include "PlayerDpBar.h"
#include "PlayerCommand.h"
#include "Fade.h"
#include "PlayerStatusWarning.h"
#include "PlayerSkill.h"
#include "SwordStatus.h"
#include "PlayerSkillUI.h"
#include "PlayerSkillUIType.h"
#include "LimitWall.h"
#include "Effect.h"
#include "Tutorial.h"

// ���O���[�o���ϐ���
// RigidBody�̕ϐ�
RigidBody* g_RigidBody;

// ������
void Player::Init()
{
	// �V�[�����擾
	Scene* scene = Manager::GetScene();

	// ����������
	m_Position = D3DXVECTOR3(0.0f, 1.0f, -2.0f);
	m_Rotation = D3DXVECTOR3(0.0f, Math::PI(), 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_isAttacking = false;
	m_MovementSpd = 0.01f;
	m_NextAtk = true;
	m_AttackType = NotAttacking;
	m_Cinematic = false;
	m_RecoverTime = 5.0f * Manager::Time;
	m_CurrentNo = 0;
	m_isDead = false;
	// Hp�̏�����
	m_MaxHp = 20.0f;
	m_CurHp = m_MaxHp;
	// Mp�̏�����
	m_MaxMp = 100.0f;
	m_CurMp = m_MaxMp;
	// Dp�̏�����
	m_MaxDp = 50.0f;
	m_CurDp = m_MaxDp;

	m_UltState = 0;
	m_isUlt = false;
	m_UltWaitTime = 0.0f;
	m_AttackSpd = 1.0f;

	m_Dodge = false;
	m_isBlock = false;
	m_Invulnerable = false;
	m_InvulTime = 0.0f;
	m_BlockSuccess = false;

	for (int i = 0; i < 4; i++)
	{
		m_Swords[i] = NULL;
	}

	// �A�j���[�V�������f���ǉ�
	AnimModelManager* _AMM = AddComponent<AnimModelManager>(GameObject::ThirdPri);
	_AMM->SetModel("SwordMaster", AnimModelManager::PlayerType);
	_AMM->SetPlayerColor(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

	// ����ǉ�����
	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] == NULL)
		{
			Sword* newSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			newSword->SetCharacter(this, (Sword::SwordPosition)i);
			newSword->BackToIdle();

			m_Swords[i] = newSword;
		}
	}

	// �T�C�Y�擾
	//m_Size = _AMM->GetAnimModelSize();
	//m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);
	m_Size = D3DXVECTOR3(1.75f, 1.75f, 1.75f);

	// �����̃R���|�[�l���g��ǉ�����
	g_RigidBody = AddComponent<RigidBody>(GameObject::SecondPri);
	g_RigidBody->SetMass(D3DXVECTOR3(0.1f, 0.01f, 0.1f));
	g_RigidBody->SetGravity(0.01f);	

	// HpBar�̒ǉ�
	scene->AddGameObject<PlayerHpBar>(Scene::Layer_UILayer)->SetCharacter(this);
	// MpBar�̒ǉ�
	m_MpBar = scene->AddGameObject<PlayerMpBar>(Scene::Layer_UILayer);
	m_MpBar->SetCharacter(this);
	// DpBar�̒ǉ�
	m_DpBar = scene->AddGameObject<PlayerDpBar>(Scene::Layer_UILayer);
	m_DpBar->SetCharacter(this);

	// �v���C���[�R�}���h�̒ǉ�
	m_Slot = 1;
	m_LastSlot = m_Slot;
	for (int i = 0; i < 3; i++)
	{
		m_CommandSlot[i] = scene->AddGameObject<PlayerCommand>(Scene::Layer_UILayer);
		m_CommandSlot[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 260.0f + (i * 40.0f), 0.0f));
	}
	// �X���b�g�ɂ���ăR�}���h��ݒu����
	m_CommandSlot[0]->SetCommandType(PlayerCommand::Command_Logo);
	m_CommandSlot[1]->SetCommandType(PlayerCommand::Command_Attack);
	m_CommandSlot[2]->SetCommandType(PlayerCommand::Command_Ult);
	m_CommandSlot[2]->SetUseDp(m_MaxDp);

	
	// �v���C���[�A�j���[�V�����}�l�[�W���[��ǉ�����i�K���Ō�ɒǉ�����j
	m_PlayerAnimation = AddAnimationManager<PlayerAnimation>();
	m_PlayerAnimation->SetCharacter(this);	// �v���C���[�����擾

	// �e������
	m_ShadowDepth = true;

	// �X�e�[�^�X��\������
	m_PlayerStatus = scene->AddGameObject<PlayerStatusWarning>(Scene::Layer_UILayer);

	for (int i = 0; i < 3; i++)
	{
		m_CurCoolDown[i] = 0.0f;
		m_SkillUI[i] = scene->AddGameObject<PlayerSkillUI>(Scene::Layer_UILayer);
		m_SkillUI[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH - 225.0f + (75.0f * i), SCREEN_HEIGHT - 130.0f, 0.0f));
		m_SkillUI[i]->SetCharacter(this);
		m_SkillUI[i]->SetSlot(i);
	}

	CollisionOBB* _Col = AddComponent<CollisionOBB>(GameObject::ThirdPri);

	SetInitSkill();
}

// �X�V����
void Player::Update()
{
	if (m_Pause && !m_IgnorePause) return;

	// �Q�[�W�̒���
	AdjustGauge();

	// �V�[�����擾
	Scene* scene = Manager::GetScene();
	// ���x�擾
	D3DXVECTOR3 _Velocity = g_RigidBody->GetVelocity();
	// �J�����擾
	Camera* MainCam = scene->GetGameObject<Camera>();
	// ���b�V���t�B�[���h�擾
	MeshField* _MeshField = scene->GetGameObject<MeshField>();
	// �v���C���[�A�j���[�V�����}�l�[�W���[�擾
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (!m_isDead)
	{
		UltCommand();

		if (!m_Cinematic)
		{
			// ���M��Forward��Right��Up���擾
			D3DXVECTOR3 forward = GetForward();
			D3DXVECTOR3 right = GetRight();
			D3DXVECTOR3 up = GetUp();

			// �J������Forward��Right�擾
			D3DXVECTOR3 CamForward = MainCam->GetForward();
			D3DXVECTOR3 CamRight = MainCam->GetRight();

			// �J������Right��Forward��Y���O�ɂ���i�c�ړ����Ȃ��悤�Ɂj
			CamForward.y = 0.0f;
			CamRight.y = 0.0f;

			// �U�����ꂽ���̃A�j���[�V�����͓����Ȃ�
			if (_PA->GetPrevAniStatus() && _PA->GetPrevAnimationState<PlayerAnimation_Hit>())
			{
				m_isDamaged = false;
			}

			// �U�����ꂽ���̃A�j���[�V�����͓����Ȃ�
			if (_PA->GetPrevAniStatus() && _PA->GetPrevAnimationState<PlayerAnimation_GetUp>())
			{
				m_isDamaged = false;
			}

			// �_���[�W����Ă��Ȃ����͓�����
			if (!m_isDamaged)
			{
				// �U�����Ă���ƈړ������s��Ȃ�
				if (!m_isAttacking)
				{
					// �ړ�����
					MoveEvent();
				}

				if (Input::GetKeyTrigger(VK_SPACE))
				{
					DodgeEvent();
				}

				// �R�}���h�̏���
				CommandEvent();
			}

			// �R�}���h����
			{
				// �X���b�g���ړ�������
				if (Input::GetKeyTrigger('Q'))
				{
					// �O�̃X���b�g���X�V����
					m_LastSlot = m_Slot;

					// ��ړ�
					m_Slot--;

					if (m_Slot <= 0)
					{
						m_Slot = 2;
					}

				}
				if (Input::GetKeyTrigger('E'))
				{
					// �O�̃X���b�g���X�V����
					m_LastSlot = m_Slot;

					// ���ړ�
					m_Slot++;

					if (m_Slot >= 3)
					{
						m_Slot = 1;
					}
				}

				// �I�񂾃R�}���h���`�F�b�N����
				CommandCheck();
			}
		}

		if (m_ReadyToMove)
		{
			if (m_ReadyTime > 0.0f)
			{
				m_ReadyTime--;
			}
			else
			{
				m_ReadyToMove = false;
				m_Cinematic = false;
				MainCam->SetCinematicMode(false);
			}
		}

		if (m_InvulTime > 0.0f)
		{
			m_InvulTime--;
			m_Invulnerable = true;
			m_AttackSpd = 1.5f;
		}
		else
		{
			m_AttackSpd = 1.0f;
			m_Dodge = false;
			m_Invulnerable = false;
		}
	}

	StatusChangeColor();

	// �N�[���_�E���̃C�x���g
	CoolDownEvent();

	// �R���|�[�l���g�Ȃǂ̍X�V
	GameObject::Update();

	// ���b�V���t�B�[���h�̓����蔻�菈��
	if (!m_isDead)
	{
		if (_MeshField != NULL)
		{
			// ���b�V���t�B�[���h��艺�ɂ��鎞�n�ʂɖ߂�
			if (m_Position.y <= _MeshField->GetHeight(m_Position))
			{
				m_Position.y = _MeshField->GetHeight(m_Position);
				g_RigidBody->SetVelocity(D3DXVECTOR3(g_RigidBody->GetVelocity().x, 0.0f, g_RigidBody->GetVelocity().z));
			}
		}
	}
}

// �`�揈��
void Player::Draw()
{
	GameObject::Draw();
}

// �_���[�W�󂯂����̏���
void Player::DealDamage(float Damage)
{
	if (m_isDead) return;

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	// �h�䐬��
	if (m_isBlock)
	{
		// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
		if (Manager::CheckScene<Tutorial>())
		{
			Scene* _Scene = Manager::GetScene();
			Tutorial* _Tutorial = (Tutorial*)_Scene;
			if (_Tutorial->GetTutorialState<TutorialState_Mission04>())
			{
				_Tutorial->SetTutorialFinish();
			}
		}

		AddDp(4.0f);

		// �F��ύX����
		ChangeBackColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);

		// �h��̃G�t�F�N�g
		Effect* _BCE = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
		// �G�t�F�N�g�̍��W����
		D3DXVECTOR3 EffectPos = m_Position - GetForward() * 0.6f;
		EffectPos.y += 1.0f;
		_BCE->SetPosition(EffectPos);
		_BCE->SetEffectType<EffectType_Block>();

		// �h�䐬���̃Z�b�g
		m_BlockSuccess = true;
		// �����U���ł���i�����ōU������Ƃ�����Ɩ��G���Ԃɓ���j
		ReadyToAtk();
		AttackCombo(NotAttacking);
		// �A�j���[�V������ς���
		_PA->ChangeState<PlayerAnimation_BlockCounter>();
		return;
	}

	// �h��Ȃ����ǖ��G����return����
	if (m_Invulnerable) return;

	// �_���[�W�󂯂�
	m_PlayerStatus->DmgTaken();
	// Hp�����
	m_CurHp -= Damage;

	// Hp���O�ȉ��ɂȂ�ƏI���
	if (m_CurHp <= 0.0f)
	{
		// �������bool����true�ɂ���
		m_isDead = true;

		// 
		g_RigidBody->SetMass(D3DXVECTOR3(0.0f, 0.0f, 0.1f));
		g_RigidBody->SetGravity(0.0f);

		// ������A�j���[�V���������
		_PA->ChangeState<PlayerAnimation_Dead>();
		return;
	}

	// Ult��ԂŃ_���[�W�󂯂Ă��A�j���[�V�����͕ς��Ȃ�
	if (m_isUlt) return;

	// �_���[�W���ꂽ
	m_isDamaged = true;

	// �O�̂��߂Ɍ����[����
	RecoverSword();

	// �����U���ł����Ȋ���
	AttackCombo(NotAttacking);
	if (!m_NextAtk)
	{
		m_NextAtk = true;
	}

	// �ł���Ă���̃A�j���[�V����
	_PA->ChangeState<PlayerAnimation_Hit>();
}

// �v���C���[�̍U������
void Player::AttackCombo(AttackType AT)
{
	PlayerAnimation* _PA = m_PlayerAnimation;

	// ���̍U�����X�V
	m_AttackType = AT;

	// �U���̎�ނɂ���čs���������Ⴄ
	switch (AT)
	{
	case NotAttacking:
		m_NextAtk = true;
		m_isAttacking = false;
		RecoverSword();
		break;
	case Attack01:
		m_isBlock = false;

		if (m_BlockSuccess)
		{
			ChangeBackColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f), 1.0f);

			m_InvulTime = 1.0f * Manager::Time;
			SwordBlock(false);
			m_BlockSuccess = false;
		}
		m_NextAtk = false;
		m_isAttacking = true;
		_PA->ChangeState<PlayerAnimation_Attack01>();
		break;
	case Attack02:
		m_isBlock = false;
		
		if (m_BlockSuccess)
		{
			ChangeBackColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f), 1.0f);
			m_InvulTime = 1.0f * Manager::Time;
			SwordBlock(false);
			m_BlockSuccess = false;
		}
		m_NextAtk = false;
		m_isAttacking = true;
		_PA->ChangeState<PlayerAnimation_Attack02>();
		break;
	case Attack03:
		m_isBlock = false;
		
		if (m_BlockSuccess)
		{
			ChangeBackColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f), 1.0f);
			m_InvulTime = 1.0f * Manager::Time;
			SwordBlock(false);
			m_BlockSuccess = false;
		}
		m_NextAtk = false;
		m_isAttacking = true;
		_PA->ChangeState<PlayerAnimation_Attack03>();
		break;
	case Attack04:
		m_isBlock = false;
		
		if (m_BlockSuccess)
		{
			ChangeBackColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f), 1.0f);
			m_InvulTime = 1.0f * Manager::Time;
			SwordBlock(false);
			m_BlockSuccess = false;
		}
		m_NextAtk = false;
		m_isAttacking = true;
		_PA->ChangeState<PlayerAnimation_Attack04>();
		break;
	case Attack05:
		m_isBlock = false;
		
		if (m_BlockSuccess)
		{
			ChangeBackColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f), 1.0f);
			m_InvulTime = 1.0f * Manager::Time;
			SwordBlock(false);
			m_BlockSuccess = false;
		}
		m_NextAtk = false;
		m_isAttacking = true;
		_PA->ChangeState<PlayerAnimation_Attack05>();
		break;
	case Block:
		m_NextAtk = false;
		m_isAttacking = true;
		_PA->ChangeState<PlayerAnimation_Block>();
		m_isBlock = true;
		m_BlockSuccess = false;
		SwordBlock(true);
		break;
	}
}

// �U������
void Player::AttackEvent()
{
	switch (m_AttackType)
	{
	case Attack01:
		{
			// ���̏������W
			D3DXVECTOR3 InitPos = m_Swords[4]->GetPosition() - (GetRight() * 1.2f);
			InitPos.y += 1.0f;
			// �����Ă��������Tangent
			D3DXVECTOR3 InitTan = -GetForward() * 10.0f;
			// �ړI���W
			D3DXVECTOR3 TargetPos = m_Swords[4]->GetPosition() - (GetRight() * -2.0f);
			TargetPos.y -= 0.3f;
			// �ړITangent
			D3DXVECTOR3 TargetTan = -InitTan;

			// �F�̒���
			m_Swords[4]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));

			// ����炷
			AudioManager::PlaySE("SEAttack01");

			// �����U������
			m_Swords[4]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.3f);

			m_Swords[4] = NULL;
		}
		break;
	case Attack02:
		{
			// ���̏������W
			D3DXVECTOR3 InitPos = m_Swords[3]->GetPosition();
			// �����Ă��������Tangent
			D3DXVECTOR3 InitTan = m_Swords[3]->GetQuaternionUp() * -7.0f;
			// �ړI���W
			D3DXVECTOR3 TargetPos = m_Position + (-GetForward() * 2.0f);
			TargetPos.y += 4.0f;
			// �ړITangent
			D3DXVECTOR3 TargetTan = GetUp() * 10.0f;

			// �F�̒���
			m_Swords[3]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));

			// ����炷
			AudioManager::PlaySE("SEAttack01");

			// �����U������
			m_Swords[3]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.4f);

			m_Swords[3] = NULL;
		}
		break;
	case Attack03:
		{
			// ���̏������W
			D3DXVECTOR3 InitPos = m_Swords[2]->GetPosition();
			// �����Ă��������Tangent
			D3DXVECTOR3 InitTan = -GetRight() * 15.0f;
			// �ړI���W
			D3DXVECTOR3 TargetPos = m_Position + (GetRight() * 2.0f);
			TargetPos.y += 1.0f;
			// �ړITangent
			D3DXVECTOR3 TargetTan = GetForward() * 10.0f;

			// �F�̒���
			m_Swords[2]->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));

			// ����炷
			AudioManager::PlaySE("SEAttack02");

			// �����U������
			m_Swords[2]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.4f);

			m_Swords[2] = NULL;
		}
		break;
	case Attack04:
		{
			// ���̏������W
			D3DXVECTOR3 InitPos = m_Swords[1]->GetPosition();
			// �����Ă��������Tangent
			D3DXVECTOR3 InitTan = m_Swords[1]->GetQuaternionUp() * 10.0f;
			InitTan += GetRight() * 5.0f;
			// �ړI���W
			D3DXVECTOR3 TargetPos = m_Position - (GetRight() * 1.5f);
			TargetPos.y += 0.5f;
			// �ړITangent
			D3DXVECTOR3 TargetTan = GetForward() * 10.0f;

			// �F�̒���
			m_Swords[1]->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));

			// ����炷
			AudioManager::PlaySE("SEAttack02");

			// �����U������
			m_Swords[1]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.4f);

			m_Swords[1] = NULL;
		}
		break;
	case Attack05:
		{
			// ���̏������W
			D3DXVECTOR3 InitPos = m_Swords[0]->GetPosition();
			// �����Ă��������Tangent
			D3DXVECTOR3 InitTan = m_Swords[0]->GetQuaternionUp() * 10.0f;
			// �ړI���W
			D3DXVECTOR3 TargetPos = m_Position + (-GetForward() * 2.0f);
			// �ړITangent
			D3DXVECTOR3 TargetTan = GetForward() * 10.0f;
			// �F�̒���
			m_Swords[0]->ChangeTrailColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));

			// ����炷
			AudioManager::PlaySE("SEAttack03");

			// �����U������
			m_Swords[0]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.2f);

			m_Swords[0] = NULL;

			// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
			if (Manager::CheckScene<Tutorial>())
			{
				Scene* _Scene = Manager::GetScene();
				Tutorial* _Tutorial = (Tutorial*)_Scene;
				if (_Tutorial->GetTutorialState<TutorialState_Mission03>())
				{
					_Tutorial->SetTutorialFinish();
				}
			}
		}
		break;
	}

}

// �R�}���h����
void Player::CommandEvent()
{
	if (m_Dodge) return;

	SkillShortCut();

	// �U���{�^����������U���������s��
	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		// �R�}���h�̎�ނɂ���ď������ς��܂�
		switch (m_CommandSlot[m_Slot]->GetCommandType())
		{
		case PlayerCommand::Command_Attack:
			if (m_NextAtk)
			{
				switch (m_AttackType)
				{
				case NotAttacking:
					RotateEvent();
					AttackCombo(Attack01);
					break;
				case Attack01:
					RotateEvent();
					AttackCombo(Attack02);
					break;
				case Attack02:
					RotateEvent();
					AttackCombo(Attack03);
					break;
				case Attack03:
					RotateEvent();
					AttackCombo(Attack04);
					break;
				case Attack04:
					RotateEvent();
					AttackCombo(Attack05);
					break;
				}
			}
			break;
		case PlayerCommand::Command_Ult:
			if (m_NextAtk && !m_isUlt)
			{
				ActivateUlt();
			}
			break;
		}
	}

	if (Input::GetKeyTrigger(VK_RBUTTON))
	{
		if (m_NextAtk && !m_isUlt)
		{
			RotateEvent();
			AttackCombo(Block);
		}
	}

}

void Player::KnockBackDamage(float Damage, D3DXVECTOR3 Dir)
{
	if (m_isDead) return;

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (m_isBlock)
	{
		AddDp(8.0f);

		ChangeBackColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);

		// �h��̃G�t�F�N�g
		Effect* _BCE = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
		// �G�t�F�N�g�̍��W����
		D3DXVECTOR3 EffectPos = m_Position - GetForward() * 0.6f;
		EffectPos.y += 1.0f;
		_BCE->SetPosition(EffectPos);
		_BCE->SetEffectType<EffectType_Block>();

		m_BlockSuccess = true;
		ReadyToAtk();
		AttackCombo(NotAttacking);
		_PA->ChangeState<PlayerAnimation_BlockCounter>();
		return;
	}

	if (m_Invulnerable) return;
	m_PlayerStatus->DmgTaken();

	m_CurHp -= Damage;
	if (m_CurHp <= 0.0f)
	{
		m_isDead = true;

		g_RigidBody->SetMass(D3DXVECTOR3(0.0f, 0.0f, 0.1f));
		g_RigidBody->SetGravity(0.0f);
		_PA->ChangeState<PlayerAnimation_Dead>();
		return;
	}

	if (m_isUlt) return;

	m_isDamaged = true;

	// �O�̂��߂Ɍ����[����
	RecoverSword();

	AttackCombo(NotAttacking);
	if (!m_NextAtk)
	{
		m_NextAtk = true;
	}

	D3DXVec3Normalize(&Dir, &Dir);

	// �_���[�W�̕����Ɍ����܂�
	m_Rotation.y = Math::RotateTowards(m_Position + Dir, m_Position);

	GetComponent<RigidBody>()->AddForce(Dir);

	_PA->ChangeState<PlayerAnimation_KnockedDown>();
}

// ����ł��鏈��
void Player::DeadEvent()
{
	SetDestroy();
	Fade::SetFade<FadeSceneType_Title>();
	return;
}

void Player::PrepareNewSwords()
{
	// �����폜���A�V��������܂�
	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] != NULL)
		{
			m_Swords[i]->SetDestroy();
			m_Swords[i] = NULL;
		}
	}

	RecoverSword();
}

// �R�}���h���ǂ��I��ł��邩���`�F�b�N����
void Player::CommandCheck()
{
	// �R�}���h���I�΂ꂽ��return
	if (m_CommandSlot[m_Slot]->GetChosen())
	{
		return;
	}

	// �O�̃R�}���h��false�ɂ���
	m_CommandSlot[m_LastSlot]->SetChosen(false);

	// �R�}���h��I�΂�Ă���ɐݒu����
	m_CommandSlot[m_Slot]->SetChosen(true);

}

// �����񕜂���
void Player::RecoverSword()
{
	Scene* scene = Manager::GetScene();

	for (int i = 0; i < 5; i++)
	{
		// ���̏ꏊ��NULL�Ȃ��Ă���ƌ����[����̏������܂�
		if (m_Swords[i] == NULL)
		{
			// �V�������𐶐����č��W�������Ă���
			Sword* newSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			newSword->SetCharacter(this, (Sword::SwordPosition)i);
			newSword->BackToIdle();

			// �z��̒��ɓ���܂�
			m_Swords[i] = newSword;
		}
	}

}

void Player::SetInitSkill()
{
	for (int i = 0; i < 3; i++)
	{
		switch (Manager::GetSkillType(i))
		{
		case 1:
			SetSkill<PlayerShootAllSword>(i);
			m_MaxCoolDown[i] = 5.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill01UI>();
			m_SkillUI[i]->SetUseMp(20.0f);
			break;
		case 2:
			SetSkill<PlayerShootFromSky>(i);
			m_MaxCoolDown[i] = 7.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill02UI>();
			m_SkillUI[i]->SetUseMp(30.0f);
			break;
		case 3:
			SetSkill<PlayerChargeShoot>(i);
			m_MaxCoolDown[i] = 4.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill03UI>();
			m_SkillUI[i]->SetUseMp(25.0f);
			break;
		case 4:
			SetSkill<PlayerSwordMachineGun>(i);
			m_MaxCoolDown[i] = 10.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill04UI>();
			m_SkillUI[i]->SetUseMp(50.0f);
			break;
		case 5:
			SetSkill<PlayerRushSword>(i);
			m_MaxCoolDown[i] = 5.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill05UI>();
			m_SkillUI[i]->SetUseMp(20.0f);
			break;
		case 6:
			SetSkill<PlayerShootMultipleTimeSword>(i);
			m_MaxCoolDown[i] = 10.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill06UI>();
			m_SkillUI[i]->SetUseMp(50.0f);
			break;
		case 7:
			SetSkill<PlayerSkillAttackCombo>(i);
			m_MaxCoolDown[i] = 10.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill07UI>();
			m_SkillUI[i]->SetUseMp(50.0f);
			break;
		case 8:
			SetSkill<PlayerSkillShootAtOnce>(i);
			m_MaxCoolDown[i] = 8.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill08UI>();
			m_SkillUI[i]->SetUseMp(40.0f);
			break;
		case 9:
			SetSkill<PlayerSummonBigSword>(i);
			m_MaxCoolDown[i] = 8.0f * Manager::Time;
			m_SkillUI[i]->SetSkillType<PlayerSkill09UI>();
			m_SkillUI[i]->SetUseMp(30.0f);
			break;
		}

	}

}

void Player::SkillShortCut()
{
	if (Input::GetKeyTrigger('1'))
	{
		ActivateSkill(0);
	}
	
	if (Input::GetKeyTrigger('2'))
	{
		ActivateSkill(1);
	}
	
	if (Input::GetKeyTrigger('3'))
	{
		ActivateSkill(2);
	}
}

void Player::TimeToDodge()
{	
	// ���x�ɂ���ĕ��������߂�
	RigidBody* _RG = GetComponent<RigidBody>();

	D3DXVECTOR3 DodgeSpd;
	DodgeSpd.y = 0.0f;

	if (m_KeyValue.x == 0.0f && m_KeyValue.y == 0.0f)
	{
		DodgeSpd = -GetForward();
	}
	else
	{
		D3DXVECTOR3 Vel = _RG->GetVelocity();
		D3DXVec3Normalize(&DodgeSpd, &Vel);
	}
	DodgeSpd *= 0.5f;

	_RG->AddForce(DodgeSpd);

	// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
	if (Manager::CheckScene<Tutorial>())
	{
		Scene* _Scene = Manager::GetScene();
		Tutorial* _Tutorial = (Tutorial*)_Scene;
		if (_Tutorial->GetTutorialState<TutorialState_Mission02>())
		{
			_Tutorial->SetTutorialFinish();
		}
	}

}

// ���
void Player::DodgeEvent()
{
	if (m_isDamaged) return;
	if (m_isUlt) return;
	if (m_Dodge) return;
	
	if (m_isAttacking)
	{
		AttackCombo(NotAttacking);
		if (!m_NextAtk)
		{
			m_NextAtk = true;
		}
	}

	// ������Ă�����
	m_Dodge = true;

	m_InvulTime = 49.0f;

	// ����A�j���[�V�����ɐ؂�ւ���
	GetAnimationManager<PlayerAnimation>()->ChangeState<PlayerAnimation_Dodge>();
}

// Ult�̏���
void Player::UltCommand()
{
	// Ult�����s���ł͂Ȃ��ꍇ��return����
	if (!m_isUlt) return;

	// �V�[���擾
	Scene* scene = Manager::GetScene();

	// �J�����擾
	Camera* MainCam = scene->GetGameObject<Camera>();

	// �v���C���[�A�j���[�V�������擾����
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	// Ult�̃X�e�[�g�ɂ���ď������s���܂�
	switch (m_UltState)
	{
	case 0:
		{
			// Ult�̑҂����Ԃ�����������
			m_UltWaitTime = 0.0f;
			// �J������CinematicMode���I���ɂ���
			MainCam->SetCinematicMode(true);
			// �u�����h��̍��W
			D3DXVECTOR3 Pos = m_Position + (-GetForward() * 2.0f);
			Pos.y += 1.8f;
			// �u�����h��̃^�[�Q�b�g���W
			D3DXVECTOR3 Tar = m_Position;
			Tar.y += 1.8f;

			MainCam->BlendTo(Pos, Tar, 0.5f);
			m_UltState = 1;
		}
		break;
	case 1:
		// �J�����ړ��̃X�e�[�g
		if (m_UltWaitTime <= (1.0f * Manager::Time))
		{
			m_UltWaitTime++;
		}
		else
		{
			m_UltWaitTime = 0.0f;
			m_UltState = 2;
		}
		break;
	case 2:
		{
			// �u�����h��̍��W
			D3DXVECTOR3 Pos = m_Position + (-GetForward() * 5.0f);
			Pos.y += 4.0f;
			Pos += (-GetRight() * 5.0f);
			// �u�����h��̃^�[�Q�b�g���W
			D3DXVECTOR3 Tar = m_Position + (-GetForward() * 5.0f);
			Tar.y += 1.5f;

			MainCam->BlendTo(Pos, Tar, 0.8f);
			m_UltState = 3;
			m_UltWaitTime = 0.0f;
		}
		break;
	case 3:
		// �J�����ړ��̃X�e�[�g
		if (m_UltWaitTime <= (0.6f * Manager::Time))
		{
			m_UltWaitTime++;
		}
		else
		{
			m_UltWaitTime = 0.0f;
			_PA->ChangeState<PlayerAnimation_Ult01>();
			m_UltState = 4;
		}
		break;
	case 4:
		// �A�j���[�V�����}�l�[�W���[����ʒm�҂��̂�
		// �������Ȃ�
		break;
	case 5:
		{
			// �J�������u�����h����
			D3DXVECTOR3 Pos = m_Position + (GetForward() * 4.0f);
			Pos.y += 4.0f;
			D3DXVECTOR3 Tar = m_Position + (-GetForward() * 7.0f);
			Pos.y += 0.5f;
			D3DXVECTOR3 Tan1 = MainCam->GetRight() * 20.0f;
			D3DXVECTOR3 Tan2 = -Tan1;

			MainCam->HermiteBlendTo(Pos, Tar, Tan1, Tan2, 3.0f);
			m_UltState = 6;
		}

		break;
	case 6:
		// ���b�Ԍ�����������
		m_UltWaitTime++;
		if (m_UltWaitTime >= (0.15f * Manager::Time))
		{
			m_UltWaitTime = 0.0f;
			// ������������
			Sword* SummonSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			// ���W�ݒ�
			D3DXVECTOR3 SummonPos = m_Position + (-GetForward() * 7.0f);
			SummonPos.x += Math::FloatRandBetween(-0.75f, 0.75f);
			SummonPos.z += Math::FloatRandBetween(-0.75f, 0.75f);
			SummonPos.y += 20.0f;
			SummonSword->SetInformation(SummonPos, D3DXVECTOR3(Math::PI(), 0.0f, 0.0f), D3DXVECTOR3(0.75f, 0.75f, 0.75f));
			SummonSword->SetShakeStr(0.025f);
			SummonSword->UltSword();

		}


		break;
	case 7:
		{
			// �傫��������������
			Sword* SummonSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			// ���W�ݒ�
			D3DXVECTOR3 SummonPos = m_Position + (-GetForward() * 7.0f);
			SummonPos.y += 20.0f;
			SummonSword->SetInformation(SummonPos, D3DXVECTOR3(Math::PI(), 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
			SummonSword->SetAtkDmg(5.0f);
			SummonSword->UltSword();
			SummonSword->SetShakeStr(0.15f);
			AudioManager::PlaySE("SEUltLastAtk");

			m_UltWaitTime = 0.0f;
			m_UltState = 8;
		}

		break;
	case 8:
		if (m_UltWaitTime <= (1.0f * Manager::Time))
		{
			m_UltWaitTime++;
		}
		else
		{
			m_UltWaitTime = 0.0f;
			MainCam->BlendBack(1.0f);
			m_UltState = 9;
		}
		break;
	case 9:
		if (m_UltWaitTime <= (1.0f * Manager::Time))
		{
			m_UltWaitTime++;
		}
		else
		{
			// �`���[�g���A�����ƃX�e�[�g���E���g�̃`���[�g���A�����Ɗ����m�F����
			if (Manager::CheckScene<Tutorial>())
			{
				Scene* _Scene = Manager::GetScene();
				Tutorial* _Tutorial = (Tutorial*)_Scene;
				if (_Tutorial->GetTutorialState<TutorialState_Mission06>())
				{
					_Tutorial->SetTutorialFinish();
				}
			}

			m_UltWaitTime = 0.0f;
			MainCam->SetCinematicMode(false);
			m_Cinematic = false;
			m_UltState = 0;
			m_isUlt = false;

			AttackCombo(NotAttacking);

			SwordBlock(false);

			// �G�Ȃǂ��|�[�Y������Ult�����s����
			m_IgnorePause = false;

			Scene* _Scene = Manager::GetScene();
			_Scene->GetGameObject<Camera>()->SetIgnorePause(false);

			for (int i = 0; i < 5; i++)
			{
				m_Swords[i]->SetIgnorePause(false);
			}

			Manager::PauseGame(false);
		}
		break;
	}
}

// �ړ�����
void Player::MoveEvent()
{
	if (m_Dodge) return;

	if (m_BlockSuccess) return;

	// �A�j���[�V�����}�l�[�W���[���擾
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �J�����擾
	Camera* _MainCam = _Scene->GetGameObject<Camera>();

	// �J������Right,Forward
	D3DXVECTOR3 CamRight = _MainCam->GetRight();
	D3DXVECTOR3 CamForward = _MainCam->GetForward();

	// �ړ��l����邽��
	D3DXVECTOR2 WalkValue = D3DXVECTOR2(0.0f, 0.0f);


	// �ړ��L�[
	// ���ړ�
	if (Input::GetKeyPress('A'))
	{
		WalkValue.x -= 1.0f;
		if (WalkValue.x < -1.0f) WalkValue.x = -1.0f;
	}
	// �O�Ɉړ�
	if (Input::GetKeyPress('W'))
	{
		WalkValue.y += 1.0f;
		if (WalkValue.y > 1.0f) WalkValue.y = 1.0f;
	}
	// ���ړ�
	if (Input::GetKeyPress('S'))
	{
		WalkValue.y -= 1.0f;
		if (WalkValue.y < -1.0f) WalkValue.y = -1.0f;
	}
	// �E�ړ�
	if (Input::GetKeyPress('D'))
	{
		WalkValue.x += 1.0f;
		if (WalkValue.x > 1.0f) WalkValue.y = 1.0f;
	}
	// WalkValue�̒l�������O�̏ꍇ�̓L�[������Ă��Ȃ�
	if (WalkValue.x == 0.0f && WalkValue.y == 0.0f)
	{
		// �����Ă��Ȃ����߂��������Ă����ԂȂ�ҋ@��Ԃɖ߂�
		if (_PA->GetCurAnimationState<PlayerAnimation_Run>())
		{
			_PA->ChangeState<PlayerAnimation_Idle>();
		}
	}
	else
	{
		// �ړ������̒l���v�Z����
		D3DXVECTOR3 RightValue = CamRight * WalkValue.x;
		D3DXVECTOR3 ForwardValue = CamForward * WalkValue.y;

		// �����̑��x�ǉ�����
		g_RigidBody->AddForce((RightValue + ForwardValue) * m_MovementSpd);

		// �v���C���[�̃A�j���[�V������ύX
		if (!_PA->GetCurAnimationState<PlayerAnimation_Run>())
		{
			_PA->ChangeState<PlayerAnimation_Run>();
		}

		// ���݂̑��x�����擾���ăv���C���[���������Ă�������ɉ�]�����܂�
		{
			D3DXVECTOR3 NorVel;
			D3DXVECTOR3 _Vel = g_RigidBody->GetVelocity();
			_Vel.y = 0.0f;
			D3DXVec3Normalize(&NorVel, &_Vel);
			float RotateAngle = atan2f(NorVel.x, NorVel.z);
			m_Rotation.y = RotateAngle + (D3DX_PI);
		}
	}
	m_KeyValue = WalkValue;

}

// Ult�𔭓�����
void Player::ActivateUlt()
{
	if (m_isUlt) return;

	if (m_CurDp < m_MaxDp)
	{

		return;
	}

	RotateEvent();

	BlockFinish();

	// �v���C���[�A�j���[�V�������擾����
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (!_PA->GetCurAnimationState<PlayerAnimation_Idle>())
	{
		_PA->ChangeState<PlayerAnimation_Idle>();
	}
	g_RigidBody->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_isUlt = true;
	m_UltState = 0;
	m_Cinematic = true;

	// �G�Ȃǂ��|�[�Y������Ult�����s����
	m_IgnorePause = true;

	Scene* _Scene = Manager::GetScene();
	_Scene->GetGameObject<Camera>()->SetIgnorePause(true);

	RecoverSword();

	for (int i = 0; i < 5; i++)
	{
		m_Swords[i]->SetIgnorePause(true);
	}

	m_CurDp = 0.0f;

	Manager::PauseGame(true);
}

void Player::RotateEvent()
{
	// �~�j�I�����߂��ɂ��邩�ǂ���
	PhysicsCast* _PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Position, D3DXVECTOR3(20.0f, 20.0f, 20.0f));

	// ������Minion�̕����Ɍ����܂�
	if (_PhyMinion != NULL)
	{
		m_Rotation.y = Math::RotateTowards(_PhyMinion->GetColldeObj()->GetPosition(), m_Position) + Math::PI();
		return;
	}
	
	// �{�X���߂����邩�ǂ���
	PhysicsCast* _PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Position, D3DXVECTOR3(20.0f, 20.0f, 20.0f));

	// ������{�X�̕����Ɍ����܂�
	if (_PhyBoss != NULL)
	{
		m_Rotation.y = Math::RotateTowards(_PhyBoss->GetColldeObj()->GetPosition(), m_Position) + Math::PI();
		return;
	}

	// �G�����Ȃ��ƃJ�����̑O�Ɍ����܂�
	// �J�����擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();
	// �J������Forward���擾�i�O���擾�j
	D3DXVECTOR3 CamForward = _Camera->GetForward();

	m_Rotation.y = Math::RotateTowards(m_Position + CamForward, m_Position) + Math::PI();

}

void Player::BackToIdle()
{
	SwordBlock(false);

	AttackCombo(NotAttacking);

	BlockFinish();

	// �A�j���[�V�����擾
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (!_PA->GetCurAnimationState<PlayerAnimation_Idle>())
	{
		_PA->ChangeState<PlayerAnimation_Idle>();
	}
}

// ���Ŗh�䂷�邩�ǂ���
void Player::SwordBlock(bool isBlock)
{
	if (isBlock)
	{
		AudioManager::PlaySE("SEBlock");

		for (int i = 0; i < 5; i++)
		{
			if (m_Swords[i] != NULL)
			{
				m_Swords[i]->DefenseSword(m_Swords[i]->GetPosition(), m_Swords[i]->GetRotation());
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (m_Swords[i] != NULL)
			{
				m_Swords[i]->BackToIdle();
			}
		}
	}
}

void Player::ShootAllSword()
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	// Minion���{�X�����邩�ǂ������`�F�b�N
	Scene* _Scene = Manager::GetScene();
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		// �S���̌�������
		for (int i = 0; i < 5; i++)
		{
			if (m_Swords[i] != NULL)
			{
				m_Swords[i]->ShootSword(_Boss);
				m_Swords[i] = NULL;
			}
		}
		return;
	}

	Minion* _Minion = _Scene->GetGameObject<Minion>();
	if (_Minion != NULL)
	{
		// �S���̌�������
		for (int i = 0; i < 5; i++)
		{
			if (m_Swords[i] != NULL)
			{
				m_Swords[i]->ShootSword(_Minion);
				m_Swords[i] = NULL;
			}
		}
		return;
	}

	D3DXVECTOR3 ForwardPos = -GetForward() * 5.0f;
	// �S���̌�������
	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] != NULL)
		{
			m_Swords[i]->ShootSword(ForwardPos);
			m_Swords[i] = NULL;
		}
	}
	
	
}

bool Player::InitSkill()
{
	if (!m_NextAtk) return false;

	// Minion���{�X�����邩�ǂ������`�F�b�N
	Scene* _Scene = Manager::GetScene();
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		m_Rotation.y = Math::RotateTowards(_Boss->GetPosition(), m_Position) + Math::PI();
	}
	else
	{
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		if (_Minion != NULL)
		{
			m_Rotation.y = Math::RotateTowards(_Minion->GetPosition(), m_Position) + Math::PI();
		}
	}
	
	m_isBlock = false;
	m_SwordRainTime = 0.0f;

	if (m_BlockSuccess)
	{
		m_InvulTime = 1.0f * Manager::Time;
		SwordBlock(false);
		m_BlockSuccess = false;
	}
	m_NextAtk = false;
	m_isAttacking = true;
	// �܂��S���̌����[����
	RecoverSword();

	return true;
}

void Player::AdjustGauge()
{
	// �ő�l�𒴂����ꍇ�͍ő�l�ɐݒ肵�܂�

	if (m_CurHp > m_MaxHp) m_CurHp = m_MaxHp;

	if (m_CurMp > m_MaxMp) m_CurMp = m_MaxMp;

	if (m_CurDp > m_MaxDp) m_CurDp = m_MaxDp;

	// �ŏ��l��菬�����ꍇ�͂O�ɖ߂��܂�
	if (m_CurHp < 0.0f) m_CurHp = 0.0f;

	if (m_CurMp < 0.0f) m_CurMp = 0.0f;

	if (m_CurDp < 0.0f) m_CurDp = 0.0f;
}

void Player::RainSword()
{
	// ���ԑ�����
	m_SwordRainTime++;

	// 
	if (m_SwordRainTime > 4.0f)
	{	
		// ����炷
		AudioManager::PlaySE("SEShootSword");

		m_SwordRainTime = 0.0f;
		
		// �V�[���擾���A�{�X��Minion���擾
		Scene* _Scene = Manager::GetScene();
		Boss* _Boss = _Scene->GetGameObject<Boss>();
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		// ���̍��W
		D3DXVECTOR3 SummonPos;
		D3DXVECTOR3 TargetPos;

		// �{�X��������
		if (_Boss != NULL)
		{
			SummonPos = _Boss->GetPosition();
		}
		else if(_Minion != NULL)
		{
			SummonPos = _Minion->GetPosition();
		}
		else
		{
			SummonPos = m_Position - GetForward() * 5.0f;
		}

		TargetPos = SummonPos;
		// ����ǉ�����
		Sword* _Sword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
		SummonPos.y += 30.0f;
		SummonPos.x += Math::FloatRandBetween(-1.0f, 1.0f);
		SummonPos.z += Math::FloatRandBetween(-1.0f, 1.0f);
		_Sword->SetPosition(SummonPos);
		_Sword->SetScale(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
		_Sword->ShootStraightSword(TargetPos);
		return;
	}
}

void Player::StatusChangeColor()
{
	if (!m_StatusColor) return;

	if (m_StatusTime > 0.0f)
	{
		m_StatusTime--;

		float T = m_StatusTime / m_StatusInitTime;

		D3DXVECTOR4 NormalColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		D3DXVECTOR4 LerpColor;
		D3DXVec4Lerp(&LerpColor, &NormalColor, &m_StatusInitColor, T);

		AnimModelManager* _AMM = GetComponent<AnimModelManager>();
		_AMM->SetPlayerColor(LerpColor);
	}
	else
	{
		AnimModelManager* _AMM = GetComponent<AnimModelManager>();
		_AMM->SetPlayerColor(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

		m_StatusColor = false;
		return;
	}
}

void Player::ChargeSword()
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] != NULL)
		{
			m_Swords[i]->SetSwordStatus<SwordChargeShoot>();
			m_Swords[i] = NULL;
		}
	}
}

void Player::SwordMachineGun()
{
	m_SwordRainTime++;

	if (m_SwordRainTime > 5.0f)
	{
		// ����炷
		AudioManager::PlaySE("SEShootSword");

		// �V�[���擾
		Scene* _Scene = Manager::GetScene();
		// �{�X��Minion�擾
		Boss* _Boss = _Scene->GetGameObject<Boss>();
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		// �ړI���W
		D3DXVECTOR3 TargetPos;
		if (_Boss == NULL && _Minion == NULL)
		{
			TargetPos = m_Position - GetForward() * 10.0f;
		}


		m_SwordRainTime = 0.0f;

		// ���������ꏊ
		D3DXVECTOR3 SummonPos[4];

		SummonPos[0] = m_Position + (GetRight() * 3.0f) + (GetUp() * 3.0f);
		SummonPos[1] = m_Position - (GetRight() * 3.0f) + (GetUp() * 3.0f);
		SummonPos[2] = m_Position + (GetRight() * 3.0f) - (GetUp() * 3.0f);
		SummonPos[3] = m_Position - (GetRight() * 3.0f) - (GetUp() * 3.0f);

		for (int i = 0; i < 4; i++)
		{
			Sword* _Sword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			_Sword->SetPosition(SummonPos[i]);
			if (_Boss != NULL)
			{
				_Sword->ShootSword(_Boss);
			}
			else if(_Minion != NULL)
			{
				_Sword->ShootSword(_Minion);
			}
			else
			{
				_Sword->ShootSword(TargetPos);
			}
		}
	}
}

void Player::CoolDownEvent()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_CurCoolDown[i] > 0.0f)
		{
			m_CurCoolDown[i]--;
		}
	}
}

bool Player::InitRotCamSkill()
{
	if (!m_NextAtk) return false;

	m_isBlock = false;
	m_SwordRainTime = 0.0f;

	if (m_BlockSuccess)
	{
		m_InvulTime = 1.0f * Manager::Time;
		SwordBlock(false);
		m_BlockSuccess = false;
	}
	m_NextAtk = false;
	m_isAttacking = true;
	// �܂��S���̌����[����
	RecoverSword();

	// �J�����̕����Ɍ���
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();
	
	D3DXVECTOR3 CamForward = _Camera->GetForward();
	D3DXVECTOR3 Pos = m_Position;
	Pos.y = _Camera->GetPosition().y;
	
	D3DXVECTOR3 TargetPos = _Camera->GetPosition() + CamForward;
	m_Rotation.y = Math::RotateTowards(TargetPos, Pos);
	

	return true;
}
void Player::ShootSwordSkill06()
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	// ��������
	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] != NULL)
		{
			// ���񐔐ݒ�
			int ShootCnt = 2;

			// �V�[���擾
			Scene* _Scene = Manager::GetScene();
			// �{�X�擾
			Boss* _Boss = _Scene->GetGameObject<Boss>();
			if (_Boss != NULL)
			{
				m_Swords[i]->ShootSwordSkill06(_Boss, ShootCnt);
				m_Swords[i] = NULL;
				continue;
			}
			// Minion�擾
			Minion* _Minion = _Scene->GetGameObject<Minion>();
			if (_Minion != NULL)
			{
				m_Swords[i]->ShootSwordSkill06(_Minion, ShootCnt);
				m_Swords[i] = NULL;
				continue;
			}

			D3DXVECTOR3 FrontPos = m_Position - GetForward() * 10.0f;
			m_Swords[i]->ShootSwordSkill06(FrontPos, ShootCnt);
			m_Swords[i] = NULL;
		}
	}
}

void Player::RushSword()
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	// RigidBody���擾
	RigidBody* _RB = GetComponent<RigidBody>();

	// �J�����擾
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// Forward���擾
	D3DXVECTOR3 Forward = _Camera->GetForward();
	Forward *= 0.5f;
	// �O�Ƀ_�b�V������
	_RB->AddForce(Forward);

	// ���̏�Ԃ��Z�b�g
	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] != NULL)
		{
			m_Swords[i]->SetSwordStatus<SwordSkill05>();
		}
	}
}

void Player::Skill07Combo(int Combo)
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	// �������W
	D3DXVECTOR3 InitPos;
	// ����Tangent
	D3DXVECTOR3 InitTan;
	// �ړI���W
	D3DXVECTOR3 TarPos;
	// �ړITangent
	D3DXVECTOR3 TarTan;
	// �v���C���[��RigidBody
	RigidBody* _RB = GetComponent<RigidBody>();


	switch (Combo)
	{
	case 1:
		// ��ڂ̍U��
		// �������W�ݒu
		InitPos = m_Swords[4]->GetPosition();
		// �ړI���W�ݒu
		TarPos = m_Position;
		TarPos += GetRight() * 1.5f;
		// ����Tangent
		InitTan = -GetForward() * 15.0f;
		InitTan += GetUp() * 10.0f;
		// �ړITangent
		TarTan = -InitTan;
		// �U��
		m_Swords[4]->SetAtkDmg(2.0f);
		m_Swords[4]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.86f, 0.23f, 1.0f));
		m_Swords[4]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[4] = NULL;
		break;
	case 2:
		// ��ڂ̍U��
		// �������W�ݒu
		InitPos = m_Swords[0]->GetPosition();
		// �ړI���W�ݒu
		TarPos = m_Position;
		TarPos -= GetRight() * 1.5f;
		// ����Tangent
		InitTan = -GetForward() * 15.0f;
		InitTan += GetUp() * 10.0f;
		// �ړITangent
		TarTan = -InitTan;
		// �U��
		m_Swords[0]->SetAtkDmg(2.0f);
		m_Swords[0]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.86f, 0.23f, 1.0f));
		m_Swords[0]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[0] = NULL;
		break;
	case 3:
		// ��ڂ̍U��
		// �������W�ݒu
		InitPos = m_Swords[1]->GetPosition();
		// �ړI���W�ݒu
		TarPos = m_Position;
		TarPos -= GetRight() * 1.5f;
		// ����Tangent
		InitTan = -GetForward() * 25.0f;
		InitTan += GetUp() * 10.0f;
		// �ړITangent
		TarTan = -InitTan;
		// �U��
		m_Swords[1]->SetAtkDmg(2.0f);
		m_Swords[1]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[1] = NULL;

		// �������W�ݒu
		InitPos = m_Swords[3]->GetPosition();
		// �ړI���W�ݒu
		TarPos = m_Position;
		TarPos += GetRight() * 1.5f;
		// ����Tangent
		InitTan = -GetForward() * 25.0f;
		InitTan += GetUp() * 10.0f;
		// �ړITangent
		TarTan = -InitTan;
		// �U��
		m_Swords[3]->SetAtkDmg(2.0f);
		m_Swords[3]->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		m_Swords[3]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[3] = NULL;

		// �������W�ݒu
		InitPos = m_Swords[2]->GetPosition();
		// �ړI���W�ݒu
		TarPos = m_Position;
		// ����Tangent
		InitTan = -GetForward() * 25.0f;
		InitTan += GetUp() * 10.0f;
		// �ړITangent
		TarTan = -InitTan;
		// �U��
		m_Swords[2]->SetAtkDmg(2.0f);
		m_Swords[2]->ChangeTrailColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
		m_Swords[2]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[2] = NULL;

		_RB->AddForce((-GetForward() * 0.5f));
		break;
	}
}

void Player::Skill08Combo()
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	// �ڕW���W
	D3DXVECTOR3 TargetPos;

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �{�X�擾
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		// �ڕW���W���{�X�ɐݒu����
		TargetPos = _Boss->GetPosition();
		TargetPos.y += 2.0f;
	}
	else
	{
		// �{�X�����݂��Ȃ���Minion���������܂�
		// Minion�擾
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		if (_Minion != NULL)
		{
			// Minion���݂����Minion�̍��W��ݒu���܂�
			TargetPos = _Minion->GetPosition();
			TargetPos.y += 1.0f;
		}
		else
		{
			// �{�X��Minion�������݂��Ȃ��ƃv���C���[�̑O�ɐݒu���܂�
			TargetPos = m_Position - (GetForward() * 10.0f);
		}
	}

	// ������������i���v�P�O�{�j
	for (int i = 0; i < 10; i++)
	{
		// ����
		float Distance = 10.0f;
		// �p�x
		float Angle = rand() % 360;
		// X�l
		float ValX = cosf(Angle) * Distance;
		// Z�l
		float ValZ = sinf(Angle) * Distance;
		// Y�l
		float ValY = Math::FloatRandBetween(1.0f, 5.0f);

		// ���W�ݒu
		D3DXVECTOR3 SummonPos = TargetPos;
		SummonPos.x += ValX;
		SummonPos.y += ValY;
		SummonPos.z += ValZ;

		// ��������
		Sword* _SummonSword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
		_SummonSword->SetPosition(SummonPos);
		_SummonSword->SetScale(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
		// �U��������
		_SummonSword->ShootStraightSword(TargetPos);
	}
}

void Player::Skill09Combo()
{
	// ����炷
	AudioManager::PlaySE("SEShootSword");

	// �ڕW���W
	D3DXVECTOR3 TargetPos;

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �{�X�擾
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		// �ڕW���W���{�X�ɐݒu����
		TargetPos = _Boss->GetPosition();
		TargetPos.y += 2.0f;
	}
	else
	{
		// �{�X�����݂��Ȃ���Minion���������܂�
		// Minion�擾
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		if (_Minion != NULL)
		{
			// Minion���݂����Minion�̍��W��ݒu���܂�
			TargetPos = _Minion->GetPosition();
			TargetPos.y += 1.0f;
		}
		else
		{
			// �{�X��Minion�������݂��Ȃ��ƃv���C���[�̑O�ɐݒu���܂�
			TargetPos = m_Position - (GetForward() * 10.0f);
		}
	}
	// �������W
	D3DXVECTOR3 SummonPos = m_Position;
	SummonPos.y += 1.5f;
	SummonPos -= GetForward();

	// ������������
	Sword* _SummonSword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
	_SummonSword->SetPosition(SummonPos);
	// �T�C�Y��傫������
	_SummonSword->SetScale(D3DXVECTOR3(1.25f, 1.25f, 1.25f));
	// �U���͒���
	_SummonSword->SetAtkDmg(10.0f);
	_SummonSword->ShootStraightSword(TargetPos);
	
}

void Player::ChangeBackColor(D3DXVECTOR4 Color ,float Time)
{
	AnimModelManager* _AMM = GetComponent<AnimModelManager>();
	_AMM->SetPlayerColor(Color);

	m_StatusInitColor = Color;
	m_StatusTime = Time * Manager::Time;
	m_StatusInitTime = Time * Manager::Time;
	m_StatusColor = true;
}
