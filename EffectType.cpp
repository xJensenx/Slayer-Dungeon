#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Effect.h"
#include "EffectType.h"

void EffectType::Update()
{
	// スプライトを取得
	SpriteComponent* _SC = m_Effect->GetComponent<SpriteComponent>();
	
	// 更新する
	m_Cnt++;
	// 最後まで行ったら削除します
	if (m_Cnt > m_Yoko * m_Tate)
	{
		m_Effect->SetDestroy();
		return;
	}

	// 横と縦の計算式
	float x = m_Cnt % m_Yoko * (1.0f / m_Yoko);
	float y = m_Cnt / m_Yoko * (1.0f / m_Tate);
	// スプライトのTexCoordを調整
	_SC->SetTexCoord(D3DXVECTOR2(x, y));

}

void EffectType_Block::Init()
{
	// 縦と横の設置
	m_Tate = 4;
	m_Yoko = 5;

	// スプライト
	SpriteComponent* _SC = m_Effect->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SC->LoadInfo("BlockCounterEffect", "Unlit", D3DXVECTOR2(0.2f, 0.25f));

	// 初期化
	m_Cnt = 0;
}

void EffectType_AttackHit::Init()
{
	// 縦と横の設置
	m_Tate = 4;
	m_Yoko = 5;

	// スプライト
	SpriteComponent* _SC = m_Effect->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SC->LoadInfo("AttackHitEffect", "Unlit", D3DXVECTOR2(0.2f, 0.25f));

	// 初期化
	m_Cnt = 0;
}

void EffectType_BossMeteor::Init()
{
	// 縦と横の設置
	m_Tate = 2;
	m_Yoko = 5;

	// スプライト
	SpriteComponent* _SC = m_Effect->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SC->LoadInfo("MeteorHitEffect", "Unlit", D3DXVECTOR2(0.2f, 0.5f));

	// 初期化
	m_Cnt = 0;
}
