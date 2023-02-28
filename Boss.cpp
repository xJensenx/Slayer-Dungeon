#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "BossAnimation.h"
#include "PhysicsCast.h"

#include "Boss.h"
#include "MeshField.h"
#include "input.h"
#include "Player.h"
#include "Math.h"
#include "DebugColliderBox.h"
#include "BossHpBar.h"
#include "Camera.h"
#include "Meteor.h"
#include "PlayerAnimation.h"
#include "Sword.h"
#include "QTEButton.h"
#include "Fade.h"
#include "BossBehaviorTree.h"
#include "Boss_JumpAtkEffect.h"
#include "BossAnimationState.h"
#include "AttackMeteor.h"
#include "AttackFireBall.h"
#include "Effect.h"
#include "AudioManager.h"

// �W�����v�U���̎��ԁi���`��ԗp�j
float g_BossJumpCurTime;
// �ڕW�܂Ŏ��鎞�ԁi���`��ԗp�j
float g_BossJumpMaxTime = 3.0f * Manager::Time;
// �W�����v����O�̃|�W�V����
D3DXVECTOR3 g_JumpStartPosition;
// �ڕW�̃|�W�V����
D3DXVECTOR3 g_JumpEndPosition;
// �W�����v���Ă��邩�ǂ���
bool g_isJump = false;
// �W�����v�U�����U���p
bool g_JumpAtkDmg = false;

// ����������
void Boss::Init()
{
	// �A�j���[�V�����̃��f���R���|�l���g��ǉ�����
	AnimModelManager* _AMM = AddComponent<AnimModelManager>(GameObject::ThirdPri);
	_AMM->SetModel("Boss", AnimModelManager::BlinnPhongType);
	m_Size = _AMM->GetAnimModelSize();

	// �����R���|�l���g��ǉ�����
	RigidBody* _RGB = AddComponent<RigidBody>(GameObject::ThirdPri);
	_RGB->SetGravity(0.01f);
	_RGB->SetMass(D3DXVECTOR3(0.1f, 0.01f, 0.1f));

	// ���W�Ȃǂ̏�����
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MaxHp = 150.0f;
	m_CurHp = m_MaxHp;
	m_isDead = false;
	m_CoolDown = false;

	m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);

	g_BossJumpCurTime = 0.0f;

	// �{�X�̒ǂ��X�s�[�h�𒲐�����
	m_ChaseSpd = 0.1f;
	m_QTEState = 0;
	m_QTETime = 0.0f;

	g_JumpAtkDmg = false;
	g_isJump = false;
	m_HalfHp = false;
	m_QTEFinish = false;
	m_BossPhase = NormalPhase;


	// �{�X�̃A�j���[�V�����}�l�[�W���[��ǉ�����
	m_BossAnimation = AddAnimationManager<BossAnimation>();
	m_BossAnimation->SetCharacter(this);

	ChangeBehaviorTree<BossIdle>();

}

// �I������
void Boss::Uninit()
{
	GameObject::Uninit();
}

// �X�V����
void Boss::Update()
{
	if (m_Pause && !m_IgnorePause) return;

	// �{�X��QTE�C�x���g
	BossQuickTimeEvent();

	// �V�[���̏����擾����
	Scene* _Scene = Manager::GetScene();
	// ���b�V���t�B�[���h�̏����擾����
	MeshField* _Field = _Scene->GetGameObject<MeshField>();
	// �A�j���[�V�����}�l�[�W���[���Q�b�g����
	BossAnimation* _BA = GetAnimationManager<BossAnimation>();
	// �v���C���[�̏��
	Player* _Player = _Scene->GetGameObject<Player>();
	// �{�X��RigidBody�̏��
	RigidBody* _RGB = GetComponent<RigidBody>();

	if (_Player != NULL)
	{
		if (!m_Cinematic)
		{
			m_PlayerFound = true;
			if (GetBehaviorTree<BossIdle>() != NULL)
			{
				ChangeBehaviorTree<BossChase>();
			}
			m_TargetPos = _Player->GetPosition();
		}
	}

	// �G�̃r�w�C�r�A�c���[
	//BehaviorTree(_BA);
	m_BehaviorTree->Update();

	// �N�[���_�E��
	if (m_CoolDown)
	{
		if (m_CDTime > 0.0f)
		{
			m_CDTime--;
		}
		else
		{
			m_CoolDown = false;
			m_CDTime = 0.0f;
		}
	}
	
	// �p�������Q�[���I�u�W�F�N�g�̍X�V����
	// ��ɂ̓R���|�l���g�X�V������q�I�u�W�F�N�g�̏�����A�j���[�V�����}�l�[�W���[�̍X�V����
	GameObject::Update();

	// ���b�V���t�B�[���h�̍������擾���ē����蔻���t����
	if (!m_isDead)
	{
		if (_Field != NULL)
		{
			if (m_Position.y <= _Field->GetHeight(m_Position) - 1.0f)
			{
				m_Position.y = _Field->GetHeight(m_Position) - 1.0f;
				_RGB->SetVelocity(D3DXVECTOR3(_RGB->GetVelocity().x, 0.0f, _RGB->GetVelocity().z));
			}
		}
	}
}

void Boss::DealDamage(float damage)
{
	if (m_isDead) return;
	m_CurHp -= damage;

	AudioManager::PlaySE("SEHitEnemy");

	if (m_CurHp <= 0.0f)
	{
		m_isDead = true;
		ChangeBehaviorTree<BossDead>();
	}
}

void Boss::SetAlmostJumpFinish()
{
	// �A�j���[�V�������擾
	BossAnimation* _BA = GetAnimationManager<BossAnimation>();

	if (!_BA->GetCurAnimationState<BossAnimation_Jump>()) return;

	_BA->SetJumpFinish(true);
}

// �{�X�̃W�����v���I�������
void Boss::StartCoolDown()
{
	// �N�[���_�E�������ǂ���
	m_CoolDown = true;
	// �W�����v�̃N�[���_�E�����R�b�ɂ���
	m_CDTime = 3.0f * Manager::Time;
	// �ҋ@��Ԃɖ߂�
	ChangeBehaviorTree<BossIdle>();
}

// �W�����v�U���̃G�t�F�N�g
void Boss::JumpAtkEffect()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �G�t�F�N�g�ǉ�
	Boss_JumpAtkEffect* _Effect = _Scene->AddGameObject<Boss_JumpAtkEffect>(Scene::Layer_ObjectLayer);
	// ���b�V���t�B�[���h�̍������擾
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();
	D3DXVECTOR3 SpawnPos = m_Position;
	SpawnPos.y = _MeshField->GetHeight(m_Position) - 1.75f;
	// ���W����
	_Effect->SetPosition(SpawnPos);
	_Effect->SetInitPos();
}

void Boss::SummonMeteor()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// 覐΂���������
	AttackMeteor* _AttackMeteor = _Scene->AddGameObject<AttackMeteor>(Scene::Layer_ObjectLayer);

	// �v���C���[���擾
	Player* _Player = _Scene->GetGameObject<Player>();
	// �v���C���[�����Ȃ���return����
	if (_Player == NULL) return;
	// �v���C���[�̏�ɐݒu����
	D3DXVECTOR3 SummonPos = _Player->GetPosition();
	SummonPos.y += 30.0f;

	_AttackMeteor->SetPosition(SummonPos);
}

void Boss::ShootSpinningFireBall()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	
	for (int i = 0; i < 6; i++)
	{
		// �t�@�C�A�{�[������������
		AttackFireBall* _FireBall = _Scene->AddGameObject<AttackFireBall>(Scene::Layer_ObjectLayer);
		// �v���C���[�擾
		Player* _Player = _Scene->GetGameObject<Player>();
		if (_Player == NULL) return;
		// �p�x�v�Z
		float Angle = (Math::PI() / 3) * i;
		// �����ݒu
		float Dist = 2.0f;
		// ���W�ݒu
		D3DXVECTOR3 SummonPos = _Player->GetPosition();
		SummonPos.x += cosf(Angle) * Dist;
		SummonPos.z += sinf(Angle) * Dist;
		SummonPos.y += 2.0f;
		
		_FireBall->SetPosition(SummonPos);
		_FireBall->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
		_FireBall->SetTargetObj(_Player);
		_FireBall->SetInitAngle(Angle);

		_FireBall->SetType<AttackFireBall_Type_ChargeShoot>();
	}
}

void Boss::ShootFireBall()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �t�@�C�A�{�[������������
	AttackFireBall* _FireBall = _Scene->AddGameObject<AttackFireBall>(Scene::Layer_ObjectLayer);
	// �v���C���[�擾
	Player* _Player = _Scene->GetGameObject<Player>();
	if (_Player == NULL) return;

	// ���W�ݒu
	D3DXVECTOR3 SummonPos = m_Position - GetForward() * 1.0f;
	SummonPos.y += 4.0f;

	_FireBall->SetPosition(SummonPos);
	_FireBall->SetTargetObj(_Player);

	_FireBall->SetType<AttackFireBall_Type_ShootTowardsTarget>();
}

void Boss::ShootHermiteBall()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �v���C���[�擾
	Player* _Player = _Scene->GetGameObject<Player>();
	if (_Player == NULL) return;

	for (int i = 0; i < 5; i++)
	{
		// �t�@�C�A�{�[������������
		AttackFireBall* _FireBall = _Scene->AddGameObject<AttackFireBall>(Scene::Layer_ObjectLayer);

		// ���W�ݒu
		D3DXVECTOR3 SummonPos = m_Position - GetForward() * 1.0f;
		SummonPos.y += 4.0f;

		_FireBall->SetPosition(SummonPos);
		_FireBall->SetTargetObj(_Player);
		_FireBall->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

		// Tan�ݒu
		D3DXVECTOR3 Tan;
		float ValueRight;
		float ValueUp;
		switch (i)
		{
		case 0:
			ValueRight = -1.0f;
			ValueUp = 0.0f;
			break;
		case 1:
			ValueRight = -0.5f;
			ValueUp = 0.5f;
			break;
		case 2:
			ValueRight = 0.0f;
			ValueUp = 1.0f;
			break;
		case 3:
			ValueRight = 0.5f;
			ValueUp = 0.5f;
			break;
		case 4:
			ValueRight = 1.0f;
			ValueUp = 0.0f;
			break;
		}

		Tan = GetRight() * ValueRight * 30.0f;
		Tan.y = ValueUp * 30.0f;

		_FireBall->SetHermiteTan(Tan);

		_FireBall->SetType<AttackFireBall_Type_HermiteShoot>();
	}
}

void Boss::BossQuickTimeEvent()
{
	// QTE������������return���܂�
	if (m_QTEFinish) return;
	// ������Hp�܂��s���ĂȂ���return���܂�
	if (!m_HalfHp) return;

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �v���C���[�擾
	Player* _Player = _Scene->GetGameObject<Player>();
	// �J�����擾
	Camera* _MainCam = _Scene->GetGameObject<Camera>();
	// �A�j���[�V�����}�l�[�W���[�擾
	BossAnimation* AnimationTree = GetAnimationManager<BossAnimation>();


	// ���Ԃ�QuickTimeEvent���s���܂�
	switch (m_QTEState)
	{
	case 0:
		m_Cinematic = true;
		ChangeBehaviorTree<BossQTE>();
		AnimationTree->ChangeState<BossAnimation_Roar>();
		_Player->SetCinematicMode(true);
		m_QTETime = 0.0f;
		m_QTEState = 1;
		m_QTETarPos = D3DXVECTOR3(0.0f, 0.0f, -40.0f);
		m_QTEInitPos = _Player->GetPosition();
		m_QTETarPos.y = _Player->GetPosition().y;
		_Player->BackToIdle();
		break;
	case 1:
		if (m_QTETime < 43.0f)
		{
			m_QTETime++;
		}
		else
		{
			_MainCam->ShakeCam(D3DXVECTOR3(0.1f, 0.1f, 0.0f), 2.5f);
			m_QTETime = 0.0f;
			m_QTEState = 2;
		}
		break;
	case 2:
		if (m_QTETime < (0.5f * Manager::Time))
		{
			m_QTETime++;
			float T = m_QTETime / (0.5f * Manager::Time);
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			_Player->SetPosition(LerpPos);
			float PlayerRotationY = Math::RotateTowards(m_Position, _Player->GetPosition()) + Math::PI();
			_Player->SetRotation(D3DXVECTOR3(_Player->GetRotation().x, PlayerRotationY, _Player->GetRotation().z));
			
		}
		else
		{
			m_QTETime = 0.0f;
			m_QTEState = 3;
		}
		break;
	case 3:
		if (m_QTETime < (3.0f * Manager::Time))
		{
			m_QTETime++;
		}
		else
		{
			m_QTETime = 0.0f;
			m_QTEState = 4;
		}
		break;
	case 4:
		_Player->SetRotation(D3DXVECTOR3(0.0f, Math::PI(), 0.0f));
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 40.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_QTETarPos = m_Position - (GetForward() * 10.0f);
		m_QTETarPos.y += 3.0f;
		m_QTEInitPos = m_Position;
		m_QTEInitPos.y += 5.0f;
		_MainCam->SetCinematicMode(true);
		_MainCam->BlendTo(m_QTETarPos, m_QTEInitPos, 1.0f);
		m_QTETime = 0.0f;
		m_QTEState = 5;

		break;
	case 5:
		if (m_QTETime < (1.0f * Manager::Time))
		{
			m_QTETime++;
		}
		else
		{
			// 覐΂̍��W�ݒ�
			D3DXVECTOR3 SetMeteorPos = m_Position - (GetRight() * 20.0f);
			// ���覐�
			m_Meteor[0] = _Scene->AddGameObject<Meteor>(Scene::Layer_ObjectLayer);
			m_Meteor[0]->SetPosition(SetMeteorPos);
			// ���覐�
			SetMeteorPos = m_Position;
			SetMeteorPos.y += 30.0f;
			m_Meteor[1] = _Scene->AddGameObject<Meteor>(Scene::Layer_ObjectLayer);
			m_Meteor[1]->SetPosition(SetMeteorPos);
			// ��O覐�
			SetMeteorPos = m_Position + (GetRight() * 20.0f);
			m_Meteor[2] = _Scene->AddGameObject<Meteor>(Scene::Layer_ObjectLayer);
			m_Meteor[2]->SetPosition(SetMeteorPos);

			m_QTETime = 0.0f;
			AnimationTree->ChangeState<BossAnimation_QTERoar>();
			m_QTETarPos -= (GetForward() * 5.0f);
			m_QTEInitPos.y += 5.0f;
			_MainCam->BlendTo(m_QTETarPos, m_QTEInitPos, 5.0f);

			// 覐΂��ړ�������p
			m_QTEInitPos = m_Position - (GetRight() * 20.0f);
			m_QTETarPos = m_Position - (GetRight() * 10.0f);
			m_QTETarPos.y += 10.0f;

			m_QTEState = 6;
		}

		break;
	case 6:
		if (m_QTETime < (2.0f * Manager::Time))
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 HermitePos;
			D3DXVECTOR3 Tan1 = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			Tan1 *= 4.0f;
			D3DXVECTOR3 Tan2 = -Tan1;


			D3DXVec3Hermite(&HermitePos, &m_QTEInitPos, &Tan1, &m_QTETarPos, &Tan2, T);

			m_Meteor[0]->SetPosition(HermitePos);
		}
		else
		{
			m_Meteor[0]->SetPosition(m_QTETarPos);
			m_Meteor[0]->SetIdle(true);
			m_QTETime = 0.0f;

			// 覐΂��ړ�������p
			m_QTEInitPos = m_Meteor[2]->GetPosition();
			m_QTETarPos = m_Position + (GetRight() * 10.0f);
			m_QTETarPos.y += 10.0f;

			m_QTEState = 7;
		}
		break;
	case 7:
		if (m_QTETime < (2.0f * Manager::Time))
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 HermitePos;
			D3DXVECTOR3 Tan1 = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			Tan1 *= 4.0f;
			D3DXVECTOR3 Tan2 = -Tan1;


			D3DXVec3Hermite(&HermitePos, &m_QTEInitPos, &Tan1, &m_QTETarPos, &Tan2, T);

			m_Meteor[2]->SetPosition(HermitePos);
		}
		else
		{
			m_Meteor[2]->SetPosition(m_QTETarPos);
			m_Meteor[2]->SetIdle(true);
			m_QTETime = 0.0f;

			// 覐΂��ړ�������p
			m_QTEInitPos = m_Meteor[1]->GetPosition();
			m_QTETarPos = m_Position;
			m_QTETarPos.y += 15.0f;

			m_QTEState = 8;
		}
		break;
	case 8:
		if (m_QTETime < (1.0f * Manager::Time))
		{
			m_QTETime++;
			float T = m_QTETime / (1.0f * Manager::Time);
			D3DXVECTOR3 HermitePos;
			D3DXVECTOR3 Tan1 = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			Tan1 *= 4.0f;
			D3DXVECTOR3 Tan2 = -Tan1;


			D3DXVec3Hermite(&HermitePos, &m_QTEInitPos, &Tan1, &m_QTETarPos, &Tan2, T);

			m_Meteor[1]->SetPosition(HermitePos);
		}
		else
		{
			m_Meteor[1]->SetPosition(m_QTETarPos);
			m_Meteor[1]->SetIdle(true);
			m_QTETime = 0.0f;

			m_QTEState = 9;
		}
		break;
	case 9:
		AnimationTree->ChangeState<BossAnimation_QTEAfterRoar>();
		m_Meteor[2]->SetIdle(false);
		m_QTETarPos = _Player->GetPosition();
		m_QTETarPos += _Player->GetForward() * 2.0f;
		m_QTETarPos -= _Player->GetRight() * 1.0f;
		m_QTETarPos.y += 1.0f;

		m_QTEInitPos = _Player->GetPosition();
		m_QTEInitPos -= _Player->GetForward() * 2.0f;
		m_QTEInitPos.y += 2.5f;

		m_QTECamTar = m_QTEInitPos;

		_MainCam->BlendTo(m_QTETarPos, m_QTEInitPos, 3.0f);

		// ��O覐΂��U�����Ă���
		m_QTEInitPos = m_Meteor[2]->GetPosition();
		m_QTETarPos = _Player->GetPosition();
		m_QTETarPos.y += 1.0f;
		m_QTETime = 0.0f;
		m_QTEState = 10;
		break;
	case 10:
		if (m_QTETime < 2.4f * Manager::Time)
		{
			m_QTETime++;

			float T = m_QTETime / (3.0f * Manager::Time);

			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[2]->SetPosition(LerpPos);
		}
		else
		{
			m_QTEInitPos = m_Meteor[2]->GetPosition();
			m_QTETarPos = _Player->GetPosition();
			m_QTETarPos.y += 1.0f;
			m_QTETime = 0.0f;
			m_QTEState = 11;
		}
		break;
	case 11:
		if (m_QTETime < 0.6f * Manager::Time)
		{
			m_QTETime++;
		}
		else
		{
			// QTE�{�^���\��
			m_QTEButton = _Scene->AddGameObject<QTEButton>(Scene::Layer_UILayer);
			m_QTEButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 150.0f, 0.0f));

			m_QTETime = 0.0f;
			m_QTEState = 12;
		}
		break;
	case 12:
		if (m_QTETime < 3.0f * Manager::Time)
		{
			m_QTETime++;
			if (Input::GetKeyTrigger(VK_LBUTTON))
			{
				m_QTEButton->SetDestroy();
				m_QTEButton = NULL;

				m_QTEInitPos = m_Meteor[2]->GetPosition();
				m_QTETarPos = _Player->GetPosition();
				m_QTETarPos.y += 1.0f;
				m_QTETime = 0.0f;
				m_QTEState = 14;

				PlayerAnimation* _PA = _Player->GetAnimationManager<PlayerAnimation>();
				_PA->ChangeState<PlayerAnimation_QTEDodge01>();
			}

			float T = m_QTETime / (13.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[2]->SetPosition(LerpPos);
		}
		else
		{	
			m_QTEButton->SetDestroy();
			m_QTEButton = NULL;

			m_QTEInitPos = m_Meteor[2]->GetPosition();
			m_QTETarPos = _Player->GetPosition();
			m_QTETarPos.y += 1.0f;
			m_QTETime = 0.0f;
			m_QTEState = 13;
		}
		break;
	case 13:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[2]->SetPosition(LerpPos);

			if (m_QTETime >= 1.0f * Manager::Time)
			{
				_MainCam->SetCinematicMode(false);
				_Player->SetCinematicMode(false);
				_Player->DealDamage(1000.0f);
			}
		}
		else
		{
			m_Meteor[2]->SetDestroy();
		}
		break;
	case 14:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[2]->SetPosition(LerpPos);

			D3DXVECTOR3 PlayerPos = _Player->GetPosition();
			PlayerPos += _Player->GetForward() * 2.0f;
			PlayerPos += _Player->GetRight() * 1.0f;
			PlayerPos.y += 1.0f;

			D3DXVECTOR3 NewTar = m_Position;
			NewTar.y += 2.0f;
			D3DXVECTOR3 LerpTar;
			
			D3DXVec3Lerp(&LerpTar, &m_QTECamTar, &NewTar, T);

			_MainCam->SetOldPosTar(PlayerPos, LerpTar);
		}
		else
		{
			m_Meteor[2]->SetDestroy();
			m_QTETime = 0.0f;
			m_QTEState = 15;
			D3DXVECTOR3 NewPos = m_Meteor[0]->GetPosition();
			NewPos -= m_Meteor[0]->GetForward() * 8.0f;

			_MainCam->BlendTo(NewPos, m_Meteor[0]->GetPosition(), 1.0f);
			AnimationTree->ChangeState<BossAnimation_QTEAfterRoar>();
		}
		break;
	case 15:
		if (m_QTETime < 1.0f * Manager::Time)
		{
			m_QTETime++;
		}
		else
		{
			D3DXVECTOR3 PlayerPos = _Player->GetPosition();
			PlayerPos += _Player->GetForward() * 2.0f;
			PlayerPos += _Player->GetRight() * 1.0f;
			PlayerPos.y += 1.0f;

			D3DXVECTOR3 NewTar = m_Position;
			NewTar.y += 2.0f;
			m_QTECamTar = NewTar;
			_MainCam->BlendTo(PlayerPos, NewTar, 2.7f);

			m_QTEInitPos = m_Meteor[0]->GetPosition();
			m_Meteor[0]->SetIdle(false);
			m_QTETarPos = _Player->GetPosition();
			m_QTETarPos.y += 1.0f;

			m_QTETime = 0.0f;
			m_QTEState = 16;
		}
		break;
	case 16:
		if (m_QTETime < 2.4f * Manager::Time)
		{
			m_QTETime++;

			float T = m_QTETime / (3.0f * Manager::Time);

			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[0]->SetPosition(LerpPos);
		}
		else
		{
			m_QTETime = 0.0f;
			m_QTEState = 17;
		}
		break;
	case 17:
		m_QTEInitPos = m_Meteor[0]->GetPosition();

		m_QTEButton = _Scene->AddGameObject<QTEButton>(Scene::Layer_UILayer);
		m_QTEButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50.0f, SCREEN_HEIGHT / 2 - 50.0f, 0.0f));


		m_QTETime = 0.0f;
		m_QTEState = 18;
		break;
	case 18:
		if (m_QTETime < 2.5f * Manager::Time)
		{
			m_QTETime++;
			// �������ԓ��Ƀ{�^�����������𐬌�
			if (Input::GetKeyTrigger(VK_LBUTTON))
			{
				m_QTEButton->SetDestroy();
				m_QTEButton = NULL;

				m_QTEInitPos = m_Meteor[0]->GetPosition();
				m_QTETarPos = _Player->GetPosition();
				m_QTETarPos.y += 1.0f;
				m_QTETime = 0.0f;
				m_QTEState = 20;

				PlayerAnimation* _PA = _Player->GetAnimationManager<PlayerAnimation>();
				_PA->ChangeState<PlayerAnimation_QTEDodge02>();
			}

			float T = m_QTETime / (13.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[0]->SetPosition(LerpPos);
		}
		else
		{
			m_QTEButton->SetDestroy();
			m_QTEButton = NULL;

			// �{�^��������Ă��Ȃ��ꍇ��QuickTimeEvent�����s�������܂�
			m_QTEInitPos = m_Meteor[0]->GetPosition();
			m_QTETarPos = _Player->GetPosition();
			m_QTETarPos.y += 1.0f;
			m_QTETime = 0.0f;
			m_QTEState = 19;
		}
		break;
	case 19:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[0]->SetPosition(LerpPos);

			if (m_QTETime >= 1.5f * Manager::Time)
			{
				// �v���C���[��������
				_MainCam->SetCinematicMode(false);
				_Player->SetCinematicMode(false);
				_Player->DealDamage(1000.0f);
			}
		}
		else
		{
			m_Meteor[0]->SetDestroy();
		}
		break;
	case 20:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[0]->SetPosition(LerpPos);

			D3DXVECTOR3 PlayerPos = _Player->GetPosition();
			PlayerPos += _Player->GetForward() * 2.0f;
			PlayerPos -= _Player->GetRight() * 1.0f;
			PlayerPos.y += 1.0f;

			D3DXVECTOR3 NewTar = m_Position;
			NewTar.y += 2.0f;
			D3DXVECTOR3 LerpTar;

			D3DXVec3Lerp(&LerpTar, &m_QTECamTar, &NewTar, T);

			_MainCam->SetOldPosTar(PlayerPos, LerpTar);
		}
		else
		{
			m_Meteor[1]->SetIdle(false);
			m_QTEInitPos = m_Meteor[1]->GetPosition();
			m_QTETarPos = _Player->GetPosition();
			m_QTETarPos.y += 1.0f;
			m_Meteor[0]->SetDestroy();
			m_QTETime = 0.0f;
			m_QTEState = 21;
		}
		break;
	case 21:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;

			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);

			m_Meteor[1]->SetPosition(LerpPos);
			
			if (m_QTETime > 1.5f * Manager::Time)
			{
				m_QTETime = 0.0f;
				m_QTEInitPos = m_Meteor[1]->GetPosition();

				m_QTEButton = _Scene->AddGameObject<QTEButton>(Scene::Layer_UILayer);
				m_QTEButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50.0f, SCREEN_HEIGHT / 2 - 100.0f, 0.0f));

				m_QTEState = 22;
			}
		}
		break;
	case 22:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			if (Input::GetKeyTrigger(VK_LBUTTON))
			{
				m_QTEButton->SetDestroy();
				m_QTEButton = NULL;

				D3DXVECTOR3 NextPos = _Player->GetPosition();
				NextPos -= (GetRight() * 5.0f);
				NextPos.y += 2.0f;

				m_QTETarPos = NextPos;
				m_QTECamTar = _Player->GetPosition();
				m_QTECamTar.y += 2.0f;

				_MainCam->BlendTo(m_QTETarPos, m_QTECamTar, 0.1f);

				PlayerAnimation* _PA = _Player->GetAnimationManager<PlayerAnimation>();
				_PA->ChangeState<PlayerAnimation_QTEThrowSword>();

				m_QTETime = 0.0f;
				m_QTEState = 24;
			}

			float T = m_QTETime / (12.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[1]->SetPosition(LerpPos);
		}
		else
		{
			m_QTEButton->SetDestroy();
			m_QTEButton = NULL;

			m_QTEInitPos = m_Meteor[1]->GetPosition();
			m_QTETarPos = _Player->GetPosition();
			m_QTETarPos.y += 1.0f;
			m_QTETime = 0.0f;
			m_QTEState = 23;
		}
		break;
	case 23:
		if (m_QTETime < 1.5f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);
			D3DXVECTOR3 LerpPos;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &m_QTETarPos, T);
			m_Meteor[1]->SetPosition(LerpPos);

			if (m_QTETime > 1.35f * Manager::Time)
			{
				// �v���C���[��������
				_MainCam->SetCinematicMode(false);
				_Player->SetCinematicMode(false);
				_Player->DealDamage(1000.0f);
			}
		}
		else
		{
			m_Meteor[1]->SetDestroy();
		}
		break;
	case 24:
		if (m_QTETime < 1.3f * Manager::Time)
		{
			m_QTETime++;
		}
		else
		{
			m_QTETime = 0.0f;
			m_QTEState = 25;
		}
		break;
	case 25:
		{
			// ������������
			m_PlayerSword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			// ���̍��W�A�T�C�Y�A���[�e�[�V�����Ȃǂ̏�����
			D3DXVECTOR3 SummonPos = _Player->GetPosition();
			SummonPos += _Player->GetForward() * 10.0f;
			SummonPos.y += 2.0f;
			SummonPos -= _Player->GetRight() * 5.0f;
			D3DXVECTOR3 SummonSize = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
			D3DXVECTOR3 SummonRot = D3DXVECTOR3((Math::PI() / 2), 0.0f, 0.0f);
			m_PlayerSword->SetInformation(SummonPos, SummonRot, SummonSize);

			D3DXVECTOR3 ShootPos = m_Position;
			ShootPos.y += 4.0f;
			m_PlayerSword->QTEShootSword(ShootPos);

			m_QTEInitPos = _MainCam->GetPosition();
			m_QTECamTar = _MainCam->GetTargetPos();

			m_QTETime = 0.0f;
			m_QTEState = 26;
		}
		break;
	case 26:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
			float T = m_QTETime / (2.0f * Manager::Time);

			// �J������Target
			D3DXVECTOR3 Tar = m_PlayerSword->GetPosition();
			Tar += m_PlayerSword->GetUp() * 2.0f;
			
			// �J�����̍��W
			D3DXVECTOR3 Pos = m_PlayerSword->GetPosition();
			Pos -= m_PlayerSword->GetRight() * 10.0f;

			D3DXVECTOR3 LerpPos, LerpTar;
			D3DXVec3Lerp(&LerpPos, &m_QTEInitPos, &Pos, T);
			D3DXVec3Lerp(&LerpTar, &m_QTECamTar, &Tar, T);

			_MainCam->SetOldPosTar(Pos, Tar);

			if (m_QTETime >= 0.5f * Manager::Time)
			{
				if (m_Meteor[1] != NULL)
				{
					_MainCam->ShakeCam(D3DXVECTOR3(0.1f, 0.1f, 0.0f), 1.0f);
					Effect* _E = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
					_E->SetPosition(m_Meteor[1]->GetPosition());
					_E->SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
					_E->SetEffectType<EffectType_AttackHit>();
					m_Meteor[1]->SetDestroy();
					m_Meteor[1] = NULL;
				}
			}
		}
		else
		{
			D3DXVECTOR3 CamPos = m_Position;
			CamPos -= GetRight() * 7.0f;
			CamPos -= GetForward() * 10.0f;
			CamPos.y += 3.0f;
			D3DXVECTOR3 NewTar = m_Position;
			NewTar.y += 3.0f;

			_MainCam->BlendTo(CamPos, NewTar, 0.2f);
			m_QTETime = 0.0f;
			m_QTEState = 27;
		}
		break;
	case 27:
		if (m_QTETime < 0.8f * Manager::Time)
		{
			m_QTETime++;
		}
		else
		{
			_MainCam->ShakeCam(D3DXVECTOR3(0.1f, 0.1f, 0.0f), 1.0f);
			DealDamage(5.0f);
			AnimationTree->ChangeState<BossAnimation_QTEInjured>();
			m_QTETime = 0.0f;
			m_QTEState = 28;
		}
		break;
	case 28:
		// �A�j���[�V�����I���܂ő҂��܂�
		break;
	case 29:
		_MainCam->BlendBack(2.0f);
		m_QTETime = 0.0f;
		m_QTEState = 30;
		break;
	case 30:
		if (m_QTETime < 2.0f * Manager::Time)
		{
			m_QTETime++;
		}
		else
		{
			_MainCam->SetCinematicMode(false);
			_Player->SetCinematicMode(false);
			_Player->AttackCombo(Player::NotAttacking);
			_Player->SetisDamaged(false);
			_Player->BlockFinish();
			m_Cinematic = false;
			ChangeBehaviorTree<BossIdle>();
			m_QTEFinish = true;
			m_BossPhase = RagePhase;
			m_QTEState = 31;
		}
		break;
	}
}

void Boss::RageSummonMeteor(int Cnt)
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// �{�X�̎��͂�覐΂���������
	for (int i = 0; i < 8; i++)
	{
		// 覐Ώ���
		AttackMeteor* _Meteor = _Scene->AddGameObject<AttackMeteor>(Scene::Layer_ObjectLayer);

		// �p�x�v�Z
		float Angle = (Math::PI() / 4) * (i + 1);

		// �����ݒ�
		float Dist = 5.0f;

		// ���W�v�Z
		D3DXVECTOR3 SummonPos = m_Position;
		SummonPos.x += cosf(Angle) * (Dist * Cnt);
		SummonPos.z += sinf(Angle) * (Dist * Cnt);
		SummonPos.y += 30.0f;

		// ���W�ݒu
		_Meteor->SetPosition(SummonPos);
	}
}
