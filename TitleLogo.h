#pragma once
#include "GameObject.h"
class TitleLogo : public GameObject
{
private:
	// エフェクトを出すかどうか
	bool m_TitleEffect;
	// エフェクト出す時間
	float m_TitleEffectTime;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// タイトルロゴのパーティクルエフェクト
	void TitleEffect();
	// タイトルエフェクトを閉じる
	void SetTitleEffect(bool TitleEffect) { m_TitleEffect = TitleEffect; }
};

