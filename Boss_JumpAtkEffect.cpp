#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Boss_JumpAtkEffect.h"
#include "Math.h"

void Boss_JumpAtkEffect::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 存在時間
	m_Duration = 2.0f * Manager::Time;
	m_CurTime = 0.0f;

	// モデル追加
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	//_MR->SetQuaternion(true);
	_MR->SetTexture("StoneGroundNormal");
	_MR->SetModel("Rock", ModelRenderer::TitleGroundType);
	
}

void Boss_JumpAtkEffect::Update()
{
	// 存在時間が過ぎると自動的に破壊されます
	if (m_Duration < 0.0f)
	{
		SetDestroy();
		return;
	}

	// 存在時間更新
	m_Duration--;

	// スケール更新
	if (m_CurTime < m_TotalTime)
	{
		m_CurTime++;

		// 線形補間用
		float T = m_CurTime / m_TotalTime;

		// 初期スケール値
		D3DXVECTOR3 InitScale = D3DXVECTOR3(7.5f, 0.0f, 7.5f);
		// 目標スケール値
		D3DXVECTOR3 TargetScale = D3DXVECTOR3(7.5f, 7.5f, 7.5f);
		// 線形補間用変数
		D3DXVECTOR3 LerpScale;
		// 移動距離
		float MoveAmt = 2.0f;


		// 線形補間
		D3DXVec3Lerp(&LerpScale, &InitScale, &TargetScale, T);
		float PlusAmt = Math::FloatLerp(0.0f, MoveAmt, T);
		
		// 座標更新
		m_Position.y = m_InitPosY + PlusAmt;

		// スケール更新
		m_Scale = LerpScale;
	}
	else
	{
		// スケールは目標スケール値にする
		m_Scale = D3DXVECTOR3(7.5f, 7.5f, 7.5f);
		// 座標更新
		m_Position.y = m_InitPosY + 2.0f;
	}
	

	// コンポーネントの更新処理
	GameObject::Update();
}
