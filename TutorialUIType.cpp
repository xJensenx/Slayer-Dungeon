#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"
#include "TutorialUI.h"
#include "TutorialUIType.h"
#include "Math.h"


void TutorialUIType_MissionUI::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("MissionUI", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void TutorialUIType_MissionUI::Update()
{
}

void TutorialUIType_Mission01::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// クリアしてないスプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission01NC", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// クリアしたスプライト追加
	m_ClearedSprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClearedSprite->LoadInfo("Mission01", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClearedSprite->SetVisibility(false);
	// アニメーションステートの初期化
	m_AnimationState = 0;
	// 時間初期化
	m_Time = 0.0f;
}

void TutorialUIType_Mission01::Update()
{
	// スプライトのアニメーション
	// 初期α値
	float InitAlpha = 1.0f;
	// 目標α値
	float TargetAlpha = 0.5f;
	// 線形補間用変数
	float LerpAlpha;
	float T;
	// 線形補間
	// ステートによって違う
	switch (m_AnimationState)
	{
	case 0:
		if (m_Time < 1.0f * Manager::Time)
		{
			m_Time++;
		}
		else
		{
			m_AnimationState = 1;
		}
		break;
	case 1:
		if (m_Time > 0.0f)
		{
			m_Time--;
		}
		else
		{
			m_AnimationState = 0;
		}
		break;
	}
	T = m_Time / (1.0f * Manager::Time);

	// 線形補間
	LerpAlpha = Math::FloatLerp(InitAlpha, TargetAlpha, T);

	// α代入
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
	m_ClearedSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));

}

void TutorialUIType_Mission02::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// クリアしてないスプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission02NC", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// クリアしたスプライト追加
	m_ClearedSprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClearedSprite->LoadInfo("Mission02", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClearedSprite->SetVisibility(false);
	// アニメーションステートの初期化
	m_AnimationState = 0;
	// 時間初期化
	m_Time = 0.0f;
}

void TutorialUIType_Mission02::Update()
{
	// スプライトのアニメーション
	// 初期α値
	float InitAlpha = 1.0f;
	// 目標α値
	float TargetAlpha = 0.5f;
	// 線形補間用変数
	float LerpAlpha;
	float T;
	// 線形補間
	// ステートによって違う
	switch (m_AnimationState)
	{
	case 0:
		if (m_Time < 1.0f * Manager::Time)
		{
			m_Time++;
		}
		else
		{
			m_AnimationState = 1;
		}
		break;
	case 1:
		if (m_Time > 0.0f)
		{
			m_Time--;
		}
		else
		{
			m_AnimationState = 0;
		}
		break;
	}
	T = m_Time / (1.0f * Manager::Time);

	// 線形補間
	LerpAlpha = Math::FloatLerp(InitAlpha, TargetAlpha, T);

	// α代入
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
	m_ClearedSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
}

void TutorialUIType_Mission03::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// クリアしてないスプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission03NC", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// クリアしたスプライト追加
	m_ClearedSprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClearedSprite->LoadInfo("Mission03", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClearedSprite->SetVisibility(false);
	// アニメーションステートの初期化
	m_AnimationState = 0;
	// 時間初期化
	m_Time = 0.0f;
}

void TutorialUIType_Mission03::Update()
{
	// スプライトのアニメーション
// 初期α値
	float InitAlpha = 1.0f;
	// 目標α値
	float TargetAlpha = 0.5f;
	// 線形補間用変数
	float LerpAlpha;
	float T;
	// 線形補間
	// ステートによって違う
	switch (m_AnimationState)
	{
	case 0:
		if (m_Time < 1.0f * Manager::Time)
		{
			m_Time++;
		}
		else
		{
			m_AnimationState = 1;
		}
		break;
	case 1:
		if (m_Time > 0.0f)
		{
			m_Time--;
		}
		else
		{
			m_AnimationState = 0;
		}
		break;
	}
	T = m_Time / (1.0f * Manager::Time);

	// 線形補間
	LerpAlpha = Math::FloatLerp(InitAlpha, TargetAlpha, T);

	// α代入
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
	m_ClearedSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));

}

void TutorialUIType_Mission04::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// クリアしてないスプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission04NC", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// クリアしたスプライト追加
	m_ClearedSprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClearedSprite->LoadInfo("Mission04", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClearedSprite->SetVisibility(false);
	// アニメーションステートの初期化
	m_AnimationState = 0;
	// 時間初期化
	m_Time = 0.0f;
}

void TutorialUIType_Mission04::Update()
{
	// スプライトのアニメーション
// 初期α値
	float InitAlpha = 1.0f;
	// 目標α値
	float TargetAlpha = 0.5f;
	// 線形補間用変数
	float LerpAlpha;
	float T;
	// 線形補間
	// ステートによって違う
	switch (m_AnimationState)
	{
	case 0:
		if (m_Time < 1.0f * Manager::Time)
		{
			m_Time++;
		}
		else
		{
			m_AnimationState = 1;
		}
		break;
	case 1:
		if (m_Time > 0.0f)
		{
			m_Time--;
		}
		else
		{
			m_AnimationState = 0;
		}
		break;
	}
	T = m_Time / (1.0f * Manager::Time);

	// 線形補間
	LerpAlpha = Math::FloatLerp(InitAlpha, TargetAlpha, T);

	// α代入
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
	m_ClearedSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));

}

void TutorialUIType_Mission05::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// クリアしてないスプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission05NC", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// クリアしたスプライト追加
	m_ClearedSprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClearedSprite->LoadInfo("Mission05", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClearedSprite->SetVisibility(false);
	// アニメーションステートの初期化
	m_AnimationState = 0;
	// 時間初期化
	m_Time = 0.0f;
}

void TutorialUIType_Mission05::Update()
{
	// スプライトのアニメーション
// 初期α値
	float InitAlpha = 1.0f;
	// 目標α値
	float TargetAlpha = 0.5f;
	// 線形補間用変数
	float LerpAlpha;
	float T;
	// 線形補間
	// ステートによって違う
	switch (m_AnimationState)
	{
	case 0:
		if (m_Time < 1.0f * Manager::Time)
		{
			m_Time++;
		}
		else
		{
			m_AnimationState = 1;
		}
		break;
	case 1:
		if (m_Time > 0.0f)
		{
			m_Time--;
		}
		else
		{
			m_AnimationState = 0;
		}
		break;
	}
	T = m_Time / (1.0f * Manager::Time);

	// 線形補間
	LerpAlpha = Math::FloatLerp(InitAlpha, TargetAlpha, T);

	// α代入
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
	m_ClearedSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));

}

void TutorialUIType_Mission06::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(250.0f, 40.0f, 0.0f));
	// クリアしてないスプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission06NC", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// クリアしたスプライト追加
	m_ClearedSprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_ClearedSprite->LoadInfo("Mission06", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_ClearedSprite->SetVisibility(false);
	// アニメーションステートの初期化
	m_AnimationState = 0;
	// 時間初期化
	m_Time = 0.0f;
}

void TutorialUIType_Mission06::Update()
{
	// スプライトのアニメーション
// 初期α値
	float InitAlpha = 1.0f;
	// 目標α値
	float TargetAlpha = 0.5f;
	// 線形補間用変数
	float LerpAlpha;
	float T;
	// 線形補間
	// ステートによって違う
	switch (m_AnimationState)
	{
	case 0:
		if (m_Time < 1.0f * Manager::Time)
		{
			m_Time++;
		}
		else
		{
			m_AnimationState = 1;
		}
		break;
	case 1:
		if (m_Time > 0.0f)
		{
			m_Time--;
		}
		else
		{
			m_AnimationState = 0;
		}
		break;
	}
	T = m_Time / (1.0f * Manager::Time);

	// 線形補間
	LerpAlpha = Math::FloatLerp(InitAlpha, TargetAlpha, T);

	// α代入
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));
	m_ClearedSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, LerpAlpha));

}

void TutorialUIType_Mission01Hint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission01Hint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_Mission01Hint::Update()
{
}

void TutorialUIType_Mission02Hint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission02Hint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_Mission02Hint::Update()
{
}

void TutorialUIType_Mission03Hint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission03Hint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_Mission03Hint::Update()
{
}

void TutorialUIType_Mission04Hint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission04Hint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_Mission04Hint::Update()
{
}

void TutorialUIType_Mission05Hint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission05Hint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_Mission05Hint::Update()
{
}

void TutorialUIType_Mission06Hint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("Mission06Hint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_Mission06Hint::Update()
{
}

void TutorialUIType_GreetingHint::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("GreetingHint", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_GreetingHint::Update()
{
}

void TutorialUIType_TutorialFinish::Init()
{
	// サイズ指定
	m_Character->SetSize(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));
	// スプライト追加
	m_Sprite = m_Character->AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("TutorialFinish", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TutorialUIType_TutorialFinish::Update()
{
}
