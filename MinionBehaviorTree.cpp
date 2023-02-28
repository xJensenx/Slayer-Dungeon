#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Minion.h"
#include "MinionAnimation.h"
#include "MinionBehaviorTree.h"

#include "Math.h"
#include "PhysicsCast.h"
#include "Player.h"
#include "Game.h"
#include "Tutorial.h"
#include "Fade.h"
#include "Title.h"

void MinionBehaviorTree_Idle::Init()
{			
	// 待機アニメーションに変える
	if (!m_AnimationTree->GetCurAnimationState<MinionAnimationState_Idle>())
	{
		m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
	}
}

void MinionBehaviorTree_Idle::Update()
{

}

void MinionBehaviorTree_Chase::Init()
{
}

void MinionBehaviorTree_Chase::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();

	// プレイヤーの情報取得
	Player* _Player = _Scene->GetGameObject<Player>();

	// MinionのPositionを取得
	D3DXVECTOR3 _Position = m_Character->GetPosition();

	// MinionのRotationを取得
	D3DXVECTOR3 _Rotation = m_Character->GetRotation();

	// プレイヤーの方向に向く
	_Rotation.y = Math::RotateTowards(_Player->GetPosition(), _Position) + Math::PI();
	m_Character->SetRotation(_Rotation);

	// 距離を計算する
	float Distance = Math::Distance(_Player->GetPosition(), _Position);

	// 方向を計算する
	D3DXVECTOR3 Dir = _Player->GetPosition() - _Position;
	D3DXVec3Normalize(&Dir, &Dir);
	Dir.y = 0.0f;

	if (Distance > 2.0f)
	{
		// プレイヤーを追う
		_Position += (Dir * 0.075f);
		m_Character->SetPosition(_Position);

		// 走るアニメーションに変える
		if (!m_AnimationTree->GetCurAnimationState<MinionAnimationState_Run>())
		{
			m_AnimationTree->ChangeState<MinionAnimationState_Run>();
		}
	}
	else
	{
		if (m_Character->GetAttackCD() <= 0.0f)
		{
			m_Character->SetisAttacking(true);
			m_Character->ChangeBehavior<MinionBehaviorTree_Attack>();
			return;
		}

		if (!m_AnimationTree->GetCurAnimationState<MinionAnimationState_Idle>())
		{
			m_AnimationTree->ChangeState<MinionAnimationState_Idle>();
		}
	}
}

void MinionBehaviorTree_Attack::Init()
{
	// 攻撃アニメーションをさせる
	int RandAtk = Math::IntRandBetween(0, 1);
	if (RandAtk == 0)
	{
		m_AnimationTree->ChangeState<MinionAnimationState_Attack01>();
	}
	else
	{
		m_AnimationTree->ChangeState<MinionAnimationState_Attack02>();
	}
}

void MinionBehaviorTree_Attack::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->SetisAttacking(false);
		m_Character->SetAttackCD(3.0f);
		m_Character->ChangeBehavior<MinionBehaviorTree_Chase>();
		return;
	}
}

void MinionBehaviorTree_BeenHit::Init()
{
	m_AnimationTree->ChangeState<MinionAnimationState_Hit>();
}

void MinionBehaviorTree_BeenHit::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->ChangeBehavior<MinionBehaviorTree_Chase>();
		m_Character->SetisDamaged(false);
		return;
	}
}

void MinionBehaviorTree_Show::Init()
{
	m_AnimationTree->ChangeState<MinionAnimationState_Show>();
}

void MinionBehaviorTree_Show::Update()
{

}

void MinionBehaviorTree_Dead::Init()
{
	m_AnimationTree->ChangeState<MinionAnimationState_Dead>();
}

void MinionBehaviorTree_Dead::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		if (Manager::CheckScene<Game>())
		{
			Scene* _Scene = Manager::GetScene();
			Game* _Game = (Game*)_Scene;
			_Game->SetisMinionDead();
		}

		if (Manager::CheckScene<Tutorial>())
		{
			Fade::SetFade<FadeSceneType_Title>();
		}

		m_Character->SetDestroy();
		return;
	}
}

void MinionBehaviorTree_TutorialBeenHit::Init()
{
	m_AnimationTree->ChangeState<MinionAnimationState_Hit>();
}

void MinionBehaviorTree_TutorialBeenHit::Update()
{
	if (m_AnimationTree->GetPrevAniStatus())
	{
		m_Character->ChangeBehavior<MinionBehaviorTree_Idle>();
		m_Character->SetisDamaged(false);
		return;
	}
}
