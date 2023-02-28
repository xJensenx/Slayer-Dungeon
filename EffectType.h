#pragma once
class EffectType
{
protected:
	// エフェクトクラス
	class Effect* m_Effect;
	// テクスチャの縦何個ありますかを記録
	int m_Tate;
	// テクスチャの横何個ありますかを記録
	int m_Yoko;
	// テクスチャアニメーション用
	int m_Cnt;
public:
	EffectType() {}
	~EffectType() {}

	// エフェクトをセット
	void SetEffect(class Effect* pEffect) { m_Effect = pEffect; }

	// 初期処理
	virtual void Init() = 0;
	// 更新処理
	virtual void Update();
};

class EffectType_Block : public EffectType
{
public:
	void Init() override;
};

class EffectType_AttackHit : public EffectType
{
public:
	void Init() override;
};

class EffectType_BossMeteor : public EffectType
{
public:
	void Init() override;
};