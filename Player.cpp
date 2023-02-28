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

// ＜グローバル変数＞
// RigidBodyの変数
RigidBody* g_RigidBody;

// 初期化
void Player::Init()
{
	// シーン情報取得
	Scene* scene = Manager::GetScene();

	// 初期化処理
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
	// Hpの初期化
	m_MaxHp = 20.0f;
	m_CurHp = m_MaxHp;
	// Mpの初期化
	m_MaxMp = 100.0f;
	m_CurMp = m_MaxMp;
	// Dpの初期化
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

	// アニメーションモデル追加
	AnimModelManager* _AMM = AddComponent<AnimModelManager>(GameObject::ThirdPri);
	_AMM->SetModel("SwordMaster", AnimModelManager::PlayerType);
	_AMM->SetPlayerColor(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

	// 剣を追加する
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

	// サイズ取得
	//m_Size = _AMM->GetAnimModelSize();
	//m_Size = D3DXVECTOR3(m_Size.x * m_Scale.x, m_Size.y * m_Scale.y, m_Size.z * m_Scale.z);
	m_Size = D3DXVECTOR3(1.75f, 1.75f, 1.75f);

	// 物理のコンポーネントを追加する
	g_RigidBody = AddComponent<RigidBody>(GameObject::SecondPri);
	g_RigidBody->SetMass(D3DXVECTOR3(0.1f, 0.01f, 0.1f));
	g_RigidBody->SetGravity(0.01f);	

	// HpBarの追加
	scene->AddGameObject<PlayerHpBar>(Scene::Layer_UILayer)->SetCharacter(this);
	// MpBarの追加
	m_MpBar = scene->AddGameObject<PlayerMpBar>(Scene::Layer_UILayer);
	m_MpBar->SetCharacter(this);
	// DpBarの追加
	m_DpBar = scene->AddGameObject<PlayerDpBar>(Scene::Layer_UILayer);
	m_DpBar->SetCharacter(this);

	// プレイヤーコマンドの追加
	m_Slot = 1;
	m_LastSlot = m_Slot;
	for (int i = 0; i < 3; i++)
	{
		m_CommandSlot[i] = scene->AddGameObject<PlayerCommand>(Scene::Layer_UILayer);
		m_CommandSlot[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 260.0f + (i * 40.0f), 0.0f));
	}
	// スロットによってコマンドを設置する
	m_CommandSlot[0]->SetCommandType(PlayerCommand::Command_Logo);
	m_CommandSlot[1]->SetCommandType(PlayerCommand::Command_Attack);
	m_CommandSlot[2]->SetCommandType(PlayerCommand::Command_Ult);
	m_CommandSlot[2]->SetUseDp(m_MaxDp);

	
	// プレイヤーアニメーションマネージャーを追加する（必ず最後に追加する）
	m_PlayerAnimation = AddAnimationManager<PlayerAnimation>();
	m_PlayerAnimation->SetCharacter(this);	// プレイヤー情報を取得

	// 影がある
	m_ShadowDepth = true;

	// ステータスを表示する
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

// 更新処理
void Player::Update()
{
	if (m_Pause && !m_IgnorePause) return;

	// ゲージの調整
	AdjustGauge();

	// シーン情報取得
	Scene* scene = Manager::GetScene();
	// 速度取得
	D3DXVECTOR3 _Velocity = g_RigidBody->GetVelocity();
	// カメラ取得
	Camera* MainCam = scene->GetGameObject<Camera>();
	// メッシュフィールド取得
	MeshField* _MeshField = scene->GetGameObject<MeshField>();
	// プレイヤーアニメーションマネージャー取得
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (!m_isDead)
	{
		UltCommand();

		if (!m_Cinematic)
		{
			// 自信のForwardやRightやUpを取得
			D3DXVECTOR3 forward = GetForward();
			D3DXVECTOR3 right = GetRight();
			D3DXVECTOR3 up = GetUp();

			// カメラのForwardやRight取得
			D3DXVECTOR3 CamForward = MainCam->GetForward();
			D3DXVECTOR3 CamRight = MainCam->GetRight();

			// カメラのRightやForwardのYを０にする（縦移動しないように）
			CamForward.y = 0.0f;
			CamRight.y = 0.0f;

			// 攻撃された時のアニメーションは動けない
			if (_PA->GetPrevAniStatus() && _PA->GetPrevAnimationState<PlayerAnimation_Hit>())
			{
				m_isDamaged = false;
			}

			// 攻撃された時のアニメーションは動けない
			if (_PA->GetPrevAniStatus() && _PA->GetPrevAnimationState<PlayerAnimation_GetUp>())
			{
				m_isDamaged = false;
			}

			// ダメージされていない時は動ける
			if (!m_isDamaged)
			{
				// 攻撃していると移動処理行わない
				if (!m_isAttacking)
				{
					// 移動処理
					MoveEvent();
				}

				if (Input::GetKeyTrigger(VK_SPACE))
				{
					DodgeEvent();
				}

				// コマンドの処理
				CommandEvent();
			}

			// コマンド処理
			{
				// スロットを移動させる
				if (Input::GetKeyTrigger('Q'))
				{
					// 前のスロットを更新する
					m_LastSlot = m_Slot;

					// 上移動
					m_Slot--;

					if (m_Slot <= 0)
					{
						m_Slot = 2;
					}

				}
				if (Input::GetKeyTrigger('E'))
				{
					// 前のスロットを更新する
					m_LastSlot = m_Slot;

					// 下移動
					m_Slot++;

					if (m_Slot >= 3)
					{
						m_Slot = 1;
					}
				}

				// 選んだコマンドをチェックする
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

	// クールダウンのイベント
	CoolDownEvent();

	// コンポーネントなどの更新
	GameObject::Update();

	// メッシュフィールドの当たり判定処理
	if (!m_isDead)
	{
		if (_MeshField != NULL)
		{
			// メッシュフィールドより下にいる時地面に戻る
			if (m_Position.y <= _MeshField->GetHeight(m_Position))
			{
				m_Position.y = _MeshField->GetHeight(m_Position);
				g_RigidBody->SetVelocity(D3DXVECTOR3(g_RigidBody->GetVelocity().x, 0.0f, g_RigidBody->GetVelocity().z));
			}
		}
	}
}

// 描画処理
void Player::Draw()
{
	GameObject::Draw();
}

// ダメージ受けた時の処理
void Player::DealDamage(float Damage)
{
	if (m_isDead) return;

	// シーン取得
	Scene* _Scene = Manager::GetScene();

	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	// 防御成功
	if (m_isBlock)
	{
		// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
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

		// 色を変更する
		ChangeBackColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);

		// 防御のエフェクト
		Effect* _BCE = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
		// エフェクトの座標調整
		D3DXVECTOR3 EffectPos = m_Position - GetForward() * 0.6f;
		EffectPos.y += 1.0f;
		_BCE->SetPosition(EffectPos);
		_BCE->SetEffectType<EffectType_Block>();

		// 防御成功のセット
		m_BlockSuccess = true;
		// もう攻撃できる（ここで攻撃するとちょっと無敵時間に入る）
		ReadyToAtk();
		AttackCombo(NotAttacking);
		// アニメーションを変える
		_PA->ChangeState<PlayerAnimation_BlockCounter>();
		return;
	}

	// 防御ないけど無敵だとreturnする
	if (m_Invulnerable) return;

	// ダメージ受ける
	m_PlayerStatus->DmgTaken();
	// Hpを削る
	m_CurHp -= Damage;

	// Hpが０以下になると終わり
	if (m_CurHp <= 0.0f)
	{
		// 負けるのbool文をtrueにする
		m_isDead = true;

		// 
		g_RigidBody->SetMass(D3DXVECTOR3(0.0f, 0.0f, 0.1f));
		g_RigidBody->SetGravity(0.0f);

		// 負けるアニメーションをやる
		_PA->ChangeState<PlayerAnimation_Dead>();
		return;
	}

	// Ult状態でダメージ受けてもアニメーションは変えない
	if (m_isUlt) return;

	// ダメージされた
	m_isDamaged = true;

	// 念のために剣を補充する
	RecoverSword();

	// もう攻撃できるよな感じ
	AttackCombo(NotAttacking);
	if (!m_NextAtk)
	{
		m_NextAtk = true;
	}

	// 打たれているのアニメーション
	_PA->ChangeState<PlayerAnimation_Hit>();
}

// プレイヤーの攻撃処理
void Player::AttackCombo(AttackType AT)
{
	PlayerAnimation* _PA = m_PlayerAnimation;

	// 今の攻撃を更新
	m_AttackType = AT;

	// 攻撃の種類によって行う処理も違う
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

// 攻撃処理
void Player::AttackEvent()
{
	switch (m_AttackType)
	{
	case Attack01:
		{
			// 剣の初期座標
			D3DXVECTOR3 InitPos = m_Swords[4]->GetPosition() - (GetRight() * 1.2f);
			InitPos.y += 1.0f;
			// 向いている方向のTangent
			D3DXVECTOR3 InitTan = -GetForward() * 10.0f;
			// 目的座標
			D3DXVECTOR3 TargetPos = m_Swords[4]->GetPosition() - (GetRight() * -2.0f);
			TargetPos.y -= 0.3f;
			// 目的Tangent
			D3DXVECTOR3 TargetTan = -InitTan;

			// 色の調整
			m_Swords[4]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));

			// 音を鳴らす
			AudioManager::PlaySE("SEAttack01");

			// 剣を攻撃処理
			m_Swords[4]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.3f);

			m_Swords[4] = NULL;
		}
		break;
	case Attack02:
		{
			// 剣の初期座標
			D3DXVECTOR3 InitPos = m_Swords[3]->GetPosition();
			// 向いている方向のTangent
			D3DXVECTOR3 InitTan = m_Swords[3]->GetQuaternionUp() * -7.0f;
			// 目的座標
			D3DXVECTOR3 TargetPos = m_Position + (-GetForward() * 2.0f);
			TargetPos.y += 4.0f;
			// 目的Tangent
			D3DXVECTOR3 TargetTan = GetUp() * 10.0f;

			// 色の調整
			m_Swords[3]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));

			// 音を鳴らす
			AudioManager::PlaySE("SEAttack01");

			// 剣を攻撃処理
			m_Swords[3]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.4f);

			m_Swords[3] = NULL;
		}
		break;
	case Attack03:
		{
			// 剣の初期座標
			D3DXVECTOR3 InitPos = m_Swords[2]->GetPosition();
			// 向いている方向のTangent
			D3DXVECTOR3 InitTan = -GetRight() * 15.0f;
			// 目的座標
			D3DXVECTOR3 TargetPos = m_Position + (GetRight() * 2.0f);
			TargetPos.y += 1.0f;
			// 目的Tangent
			D3DXVECTOR3 TargetTan = GetForward() * 10.0f;

			// 色の調整
			m_Swords[2]->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));

			// 音を鳴らす
			AudioManager::PlaySE("SEAttack02");

			// 剣を攻撃処理
			m_Swords[2]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.4f);

			m_Swords[2] = NULL;
		}
		break;
	case Attack04:
		{
			// 剣の初期座標
			D3DXVECTOR3 InitPos = m_Swords[1]->GetPosition();
			// 向いている方向のTangent
			D3DXVECTOR3 InitTan = m_Swords[1]->GetQuaternionUp() * 10.0f;
			InitTan += GetRight() * 5.0f;
			// 目的座標
			D3DXVECTOR3 TargetPos = m_Position - (GetRight() * 1.5f);
			TargetPos.y += 0.5f;
			// 目的Tangent
			D3DXVECTOR3 TargetTan = GetForward() * 10.0f;

			// 色の調整
			m_Swords[1]->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));

			// 音を鳴らす
			AudioManager::PlaySE("SEAttack02");

			// 剣を攻撃処理
			m_Swords[1]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.4f);

			m_Swords[1] = NULL;
		}
		break;
	case Attack05:
		{
			// 剣の初期座標
			D3DXVECTOR3 InitPos = m_Swords[0]->GetPosition();
			// 向いている方向のTangent
			D3DXVECTOR3 InitTan = m_Swords[0]->GetQuaternionUp() * 10.0f;
			// 目的座標
			D3DXVECTOR3 TargetPos = m_Position + (-GetForward() * 2.0f);
			// 目的Tangent
			D3DXVECTOR3 TargetTan = GetForward() * 10.0f;
			// 色の調整
			m_Swords[0]->ChangeTrailColor(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));

			// 音を鳴らす
			AudioManager::PlaySE("SEAttack03");

			// 剣を攻撃処理
			m_Swords[0]->AttackSword(InitPos, InitTan, TargetPos, TargetTan, 0.2f);

			m_Swords[0] = NULL;

			// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
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

// コマンド処理
void Player::CommandEvent()
{
	if (m_Dodge) return;

	SkillShortCut();

	// 攻撃ボタン押したら攻撃処理を行う
	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		// コマンドの種類によって処理が変わります
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

	// シーン取得
	Scene* _Scene = Manager::GetScene();

	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (m_isBlock)
	{
		AddDp(8.0f);

		ChangeBackColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);

		// 防御のエフェクト
		Effect* _BCE = _Scene->AddGameObject<Effect>(Scene::Layer_ObjectLayer);
		// エフェクトの座標調整
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

	// 念のために剣を補充する
	RecoverSword();

	AttackCombo(NotAttacking);
	if (!m_NextAtk)
	{
		m_NextAtk = true;
	}

	D3DXVec3Normalize(&Dir, &Dir);

	// ダメージの方向に向きます
	m_Rotation.y = Math::RotateTowards(m_Position + Dir, m_Position);

	GetComponent<RigidBody>()->AddForce(Dir);

	_PA->ChangeState<PlayerAnimation_KnockedDown>();
}

// 死んでいる処理
void Player::DeadEvent()
{
	SetDestroy();
	Fade::SetFade<FadeSceneType_Title>();
	return;
}

void Player::PrepareNewSwords()
{
	// 剣を削除し、新しいやつ作ります
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

// コマンドがどれを選んでいるかをチェックする
void Player::CommandCheck()
{
	// コマンドが選ばれたらreturn
	if (m_CommandSlot[m_Slot]->GetChosen())
	{
		return;
	}

	// 前のコマンドをfalseにする
	m_CommandSlot[m_LastSlot]->SetChosen(false);

	// コマンドを選ばれているに設置する
	m_CommandSlot[m_Slot]->SetChosen(true);

}

// 剣を回復する
void Player::RecoverSword()
{
	Scene* scene = Manager::GetScene();

	for (int i = 0; i < 5; i++)
	{
		// 剣の場所がNULLなっていると剣を補充するの準備します
		if (m_Swords[i] == NULL)
		{
			// 新しい剣を生成して座標調整してから
			Sword* newSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			newSword->SetCharacter(this, (Sword::SwordPosition)i);
			newSword->BackToIdle();

			// 配列の中に入れます
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
	// 速度によって方向を決める
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

	// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
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

// 回避
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

	// 回避している状態
	m_Dodge = true;

	m_InvulTime = 49.0f;

	// 回避アニメーションに切り替える
	GetAnimationManager<PlayerAnimation>()->ChangeState<PlayerAnimation_Dodge>();
}

// Ultの処理
void Player::UltCommand()
{
	// Ultが実行中ではない場合はreturnする
	if (!m_isUlt) return;

	// シーン取得
	Scene* scene = Manager::GetScene();

	// カメラ取得
	Camera* MainCam = scene->GetGameObject<Camera>();

	// プレイヤーアニメーションを取得する
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	// Ultのステートによって処理を行います
	switch (m_UltState)
	{
	case 0:
		{
			// Ultの待ち時間を初期化する
			m_UltWaitTime = 0.0f;
			// カメラのCinematicModeをオンにする
			MainCam->SetCinematicMode(true);
			// ブレンド先の座標
			D3DXVECTOR3 Pos = m_Position + (-GetForward() * 2.0f);
			Pos.y += 1.8f;
			// ブレンド先のターゲット座標
			D3DXVECTOR3 Tar = m_Position;
			Tar.y += 1.8f;

			MainCam->BlendTo(Pos, Tar, 0.5f);
			m_UltState = 1;
		}
		break;
	case 1:
		// カメラ移動のステート
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
			// ブレンド先の座標
			D3DXVECTOR3 Pos = m_Position + (-GetForward() * 5.0f);
			Pos.y += 4.0f;
			Pos += (-GetRight() * 5.0f);
			// ブレンド先のターゲット座標
			D3DXVECTOR3 Tar = m_Position + (-GetForward() * 5.0f);
			Tar.y += 1.5f;

			MainCam->BlendTo(Pos, Tar, 0.8f);
			m_UltState = 3;
			m_UltWaitTime = 0.0f;
		}
		break;
	case 3:
		// カメラ移動のステート
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
		// アニメーションマネージャーから通知待ちので
		// 何もしない
		break;
	case 5:
		{
			// カメラをブレンドする
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
		// 何秒間剣を召喚する
		m_UltWaitTime++;
		if (m_UltWaitTime >= (0.15f * Manager::Time))
		{
			m_UltWaitTime = 0.0f;
			// 剣を召喚する
			Sword* SummonSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			// 座標設定
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
			// 大きい剣を召喚する
			Sword* SummonSword = scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
			// 座標設定
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
			// チュートリアルだとステートがウルトのチュートリアルだと完了確認送る
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

			// 敵などをポーズさせてUltを実行する
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

// 移動処理
void Player::MoveEvent()
{
	if (m_Dodge) return;

	if (m_BlockSuccess) return;

	// アニメーションマネージャーを取得
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// カメラ取得
	Camera* _MainCam = _Scene->GetGameObject<Camera>();

	// カメラのRight,Forward
	D3DXVECTOR3 CamRight = _MainCam->GetRight();
	D3DXVECTOR3 CamForward = _MainCam->GetForward();

	// 移動値入れるため
	D3DXVECTOR2 WalkValue = D3DXVECTOR2(0.0f, 0.0f);


	// 移動キー
	// 左移動
	if (Input::GetKeyPress('A'))
	{
		WalkValue.x -= 1.0f;
		if (WalkValue.x < -1.0f) WalkValue.x = -1.0f;
	}
	// 前に移動
	if (Input::GetKeyPress('W'))
	{
		WalkValue.y += 1.0f;
		if (WalkValue.y > 1.0f) WalkValue.y = 1.0f;
	}
	// 後ろ移動
	if (Input::GetKeyPress('S'))
	{
		WalkValue.y -= 1.0f;
		if (WalkValue.y < -1.0f) WalkValue.y = -1.0f;
	}
	// 右移動
	if (Input::GetKeyPress('D'))
	{
		WalkValue.x += 1.0f;
		if (WalkValue.x > 1.0f) WalkValue.y = 1.0f;
	}
	// WalkValueの値が両方０の場合はキー押されていない
	if (WalkValue.x == 0.0f && WalkValue.y == 0.0f)
	{
		// 動いていないためもし走っている状態なら待機状態に戻る
		if (_PA->GetCurAnimationState<PlayerAnimation_Run>())
		{
			_PA->ChangeState<PlayerAnimation_Idle>();
		}
	}
	else
	{
		// 移動方向の値を計算する
		D3DXVECTOR3 RightValue = CamRight * WalkValue.x;
		D3DXVECTOR3 ForwardValue = CamForward * WalkValue.y;

		// 物理の速度追加する
		g_RigidBody->AddForce((RightValue + ForwardValue) * m_MovementSpd);

		// プレイヤーのアニメーションを変更
		if (!_PA->GetCurAnimationState<PlayerAnimation_Run>())
		{
			_PA->ChangeState<PlayerAnimation_Run>();
		}

		// 現在の速度情報を取得してプレイヤーを向かっている方向に回転させます
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

// Ultを発動する
void Player::ActivateUlt()
{
	if (m_isUlt) return;

	if (m_CurDp < m_MaxDp)
	{

		return;
	}

	RotateEvent();

	BlockFinish();

	// プレイヤーアニメーションを取得する
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (!_PA->GetCurAnimationState<PlayerAnimation_Idle>())
	{
		_PA->ChangeState<PlayerAnimation_Idle>();
	}
	g_RigidBody->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_isUlt = true;
	m_UltState = 0;
	m_Cinematic = true;

	// 敵などをポーズさせてUltを実行する
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
	// ミニオンが近くにいるかどうか
	PhysicsCast* _PhyMinion = PhysicsCast::PhysicBoxCast<Minion>(m_Position, D3DXVECTOR3(20.0f, 20.0f, 20.0f));

	// 居たらMinionの方向に向きます
	if (_PhyMinion != NULL)
	{
		m_Rotation.y = Math::RotateTowards(_PhyMinion->GetColldeObj()->GetPosition(), m_Position) + Math::PI();
		return;
	}
	
	// ボスが近くいるかどうか
	PhysicsCast* _PhyBoss = PhysicsCast::PhysicBoxCast<Boss>(m_Position, D3DXVECTOR3(20.0f, 20.0f, 20.0f));

	// 居たらボスの方向に向きます
	if (_PhyBoss != NULL)
	{
		m_Rotation.y = Math::RotateTowards(_PhyBoss->GetColldeObj()->GetPosition(), m_Position) + Math::PI();
		return;
	}

	// 敵がいないとカメラの前に向きます
	// カメラ取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();
	// カメラのForwardを取得（前を取得）
	D3DXVECTOR3 CamForward = _Camera->GetForward();

	m_Rotation.y = Math::RotateTowards(m_Position + CamForward, m_Position) + Math::PI();

}

void Player::BackToIdle()
{
	SwordBlock(false);

	AttackCombo(NotAttacking);

	BlockFinish();

	// アニメーション取得
	PlayerAnimation* _PA = GetAnimationManager<PlayerAnimation>();

	if (!_PA->GetCurAnimationState<PlayerAnimation_Idle>())
	{
		_PA->ChangeState<PlayerAnimation_Idle>();
	}
}

// 剣で防御するかどうか
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
	// 音を鳴らす
	AudioManager::PlaySE("SEShootSword");

	// Minionかボスがいるかどうかをチェック
	Scene* _Scene = Manager::GetScene();
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		// 全部の剣を撃つ
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
		// 全部の剣を撃つ
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
	// 全部の剣を撃つ
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

	// Minionかボスがいるかどうかをチェック
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
	// まず全部の剣を補充する
	RecoverSword();

	return true;
}

void Player::AdjustGauge()
{
	// 最大値を超えた場合は最大値に設定します

	if (m_CurHp > m_MaxHp) m_CurHp = m_MaxHp;

	if (m_CurMp > m_MaxMp) m_CurMp = m_MaxMp;

	if (m_CurDp > m_MaxDp) m_CurDp = m_MaxDp;

	// 最小値より小さい場合は０に戻します
	if (m_CurHp < 0.0f) m_CurHp = 0.0f;

	if (m_CurMp < 0.0f) m_CurMp = 0.0f;

	if (m_CurDp < 0.0f) m_CurDp = 0.0f;
}

void Player::RainSword()
{
	// 時間増える
	m_SwordRainTime++;

	// 
	if (m_SwordRainTime > 4.0f)
	{	
		// 音を鳴らす
		AudioManager::PlaySE("SEShootSword");

		m_SwordRainTime = 0.0f;
		
		// シーン取得し、ボスやMinionを取得
		Scene* _Scene = Manager::GetScene();
		Boss* _Boss = _Scene->GetGameObject<Boss>();
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		// 剣の座標
		D3DXVECTOR3 SummonPos;
		D3DXVECTOR3 TargetPos;

		// ボスが居たら
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
		// 剣を追加する
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
	// 音を鳴らす
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
		// 音を鳴らす
		AudioManager::PlaySE("SEShootSword");

		// シーン取得
		Scene* _Scene = Manager::GetScene();
		// ボスやMinion取得
		Boss* _Boss = _Scene->GetGameObject<Boss>();
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		// 目的座標
		D3DXVECTOR3 TargetPos;
		if (_Boss == NULL && _Minion == NULL)
		{
			TargetPos = m_Position - GetForward() * 10.0f;
		}


		m_SwordRainTime = 0.0f;

		// 剣を召喚場所
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
	// まず全部の剣を補充する
	RecoverSword();

	// カメラの方向に向く
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
	// 音を鳴らす
	AudioManager::PlaySE("SEShootSword");

	// 剣を撃つ
	for (int i = 0; i < 5; i++)
	{
		if (m_Swords[i] != NULL)
		{
			// 撃つ回数設定
			int ShootCnt = 2;

			// シーン取得
			Scene* _Scene = Manager::GetScene();
			// ボス取得
			Boss* _Boss = _Scene->GetGameObject<Boss>();
			if (_Boss != NULL)
			{
				m_Swords[i]->ShootSwordSkill06(_Boss, ShootCnt);
				m_Swords[i] = NULL;
				continue;
			}
			// Minion取得
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
	// 音を鳴らす
	AudioManager::PlaySE("SEShootSword");

	// RigidBodyを取得
	RigidBody* _RB = GetComponent<RigidBody>();

	// カメラ取得
	Scene* _Scene = Manager::GetScene();
	Camera* _Camera = _Scene->GetGameObject<Camera>();

	// Forwardを取得
	D3DXVECTOR3 Forward = _Camera->GetForward();
	Forward *= 0.5f;
	// 前にダッシュする
	_RB->AddForce(Forward);

	// 剣の状態をセット
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
	// 音を鳴らす
	AudioManager::PlaySE("SEShootSword");

	// 初期座標
	D3DXVECTOR3 InitPos;
	// 初期Tangent
	D3DXVECTOR3 InitTan;
	// 目的座標
	D3DXVECTOR3 TarPos;
	// 目的Tangent
	D3DXVECTOR3 TarTan;
	// プレイヤーのRigidBody
	RigidBody* _RB = GetComponent<RigidBody>();


	switch (Combo)
	{
	case 1:
		// 一個目の攻撃
		// 初期座標設置
		InitPos = m_Swords[4]->GetPosition();
		// 目的座標設置
		TarPos = m_Position;
		TarPos += GetRight() * 1.5f;
		// 初期Tangent
		InitTan = -GetForward() * 15.0f;
		InitTan += GetUp() * 10.0f;
		// 目的Tangent
		TarTan = -InitTan;
		// 攻撃
		m_Swords[4]->SetAtkDmg(2.0f);
		m_Swords[4]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.86f, 0.23f, 1.0f));
		m_Swords[4]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[4] = NULL;
		break;
	case 2:
		// 二個目の攻撃
		// 初期座標設置
		InitPos = m_Swords[0]->GetPosition();
		// 目的座標設置
		TarPos = m_Position;
		TarPos -= GetRight() * 1.5f;
		// 初期Tangent
		InitTan = -GetForward() * 15.0f;
		InitTan += GetUp() * 10.0f;
		// 目的Tangent
		TarTan = -InitTan;
		// 攻撃
		m_Swords[0]->SetAtkDmg(2.0f);
		m_Swords[0]->ChangeTrailColor(D3DXVECTOR4(1.0f, 0.86f, 0.23f, 1.0f));
		m_Swords[0]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[0] = NULL;
		break;
	case 3:
		// 二個目の攻撃
		// 初期座標設置
		InitPos = m_Swords[1]->GetPosition();
		// 目的座標設置
		TarPos = m_Position;
		TarPos -= GetRight() * 1.5f;
		// 初期Tangent
		InitTan = -GetForward() * 25.0f;
		InitTan += GetUp() * 10.0f;
		// 目的Tangent
		TarTan = -InitTan;
		// 攻撃
		m_Swords[1]->SetAtkDmg(2.0f);
		m_Swords[1]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[1] = NULL;

		// 初期座標設置
		InitPos = m_Swords[3]->GetPosition();
		// 目的座標設置
		TarPos = m_Position;
		TarPos += GetRight() * 1.5f;
		// 初期Tangent
		InitTan = -GetForward() * 25.0f;
		InitTan += GetUp() * 10.0f;
		// 目的Tangent
		TarTan = -InitTan;
		// 攻撃
		m_Swords[3]->SetAtkDmg(2.0f);
		m_Swords[3]->ChangeTrailColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		m_Swords[3]->AttackSword_Skill(InitPos, InitTan, TarPos, TarTan, 0.3f);
		m_Swords[3] = NULL;

		// 初期座標設置
		InitPos = m_Swords[2]->GetPosition();
		// 目的座標設置
		TarPos = m_Position;
		// 初期Tangent
		InitTan = -GetForward() * 25.0f;
		InitTan += GetUp() * 10.0f;
		// 目的Tangent
		TarTan = -InitTan;
		// 攻撃
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
	// 音を鳴らす
	AudioManager::PlaySE("SEShootSword");

	// 目標座標
	D3DXVECTOR3 TargetPos;

	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// ボス取得
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		// 目標座標をボスに設置する
		TargetPos = _Boss->GetPosition();
		TargetPos.y += 2.0f;
	}
	else
	{
		// ボスが存在しないとMinionを検索します
		// Minion取得
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		if (_Minion != NULL)
		{
			// Minion存在するとMinionの座標を設置します
			TargetPos = _Minion->GetPosition();
			TargetPos.y += 1.0f;
		}
		else
		{
			// ボスとMinion両方存在しないとプレイヤーの前に設置します
			TargetPos = m_Position - (GetForward() * 10.0f);
		}
	}

	// 剣を召喚する（合計１０本）
	for (int i = 0; i < 10; i++)
	{
		// 距離
		float Distance = 10.0f;
		// 角度
		float Angle = rand() % 360;
		// X値
		float ValX = cosf(Angle) * Distance;
		// Z値
		float ValZ = sinf(Angle) * Distance;
		// Y値
		float ValY = Math::FloatRandBetween(1.0f, 5.0f);

		// 座標設置
		D3DXVECTOR3 SummonPos = TargetPos;
		SummonPos.x += ValX;
		SummonPos.y += ValY;
		SummonPos.z += ValZ;

		// 剣を召喚
		Sword* _SummonSword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
		_SummonSword->SetPosition(SummonPos);
		_SummonSword->SetScale(D3DXVECTOR3(0.75f, 0.75f, 0.75f));
		// 攻撃させる
		_SummonSword->ShootStraightSword(TargetPos);
	}
}

void Player::Skill09Combo()
{
	// 音を鳴らす
	AudioManager::PlaySE("SEShootSword");

	// 目標座標
	D3DXVECTOR3 TargetPos;

	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// ボス取得
	Boss* _Boss = _Scene->GetGameObject<Boss>();
	if (_Boss != NULL)
	{
		// 目標座標をボスに設置する
		TargetPos = _Boss->GetPosition();
		TargetPos.y += 2.0f;
	}
	else
	{
		// ボスが存在しないとMinionを検索します
		// Minion取得
		Minion* _Minion = _Scene->GetGameObject<Minion>();
		if (_Minion != NULL)
		{
			// Minion存在するとMinionの座標を設置します
			TargetPos = _Minion->GetPosition();
			TargetPos.y += 1.0f;
		}
		else
		{
			// ボスとMinion両方存在しないとプレイヤーの前に設置します
			TargetPos = m_Position - (GetForward() * 10.0f);
		}
	}
	// 召喚座標
	D3DXVECTOR3 SummonPos = m_Position;
	SummonPos.y += 1.5f;
	SummonPos -= GetForward();

	// 剣を召喚する
	Sword* _SummonSword = _Scene->AddGameObject<Sword>(Scene::Layer_ObjectLayer);
	_SummonSword->SetPosition(SummonPos);
	// サイズを大きくする
	_SummonSword->SetScale(D3DXVECTOR3(1.25f, 1.25f, 1.25f));
	// 攻撃力調整
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
