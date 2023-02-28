#pragma once
#include "Component.h"
class ProgressBar :
    public Component
{
public:
    enum ProgressType
    {
        RightToLeft = 0,
        LeftToRight,
        TopToDown,
        DownToTop
    };
private:
    // 空白状態の時（後ろに置きます）
    class SpriteComponent* m_BlankProgress = NULL;
    // フル状態の時（前に置きます）
    class SpriteComponent* m_FullProgress = NULL;
    // フル状態の値
    float m_MaxValue;
    // 現在状態の値
    float m_CurValue;
    // 次の状態の値
    float m_NexValue;

    // 次の状態までのブレンド時間
    const float m_MaxBlendTime = 0.5f * Manager::Time;
    // 現在のブレンド時間
    float m_CurBlendTime;
    // ブレンドしているかどうか
    bool m_isBlend;
    // ブレンド前の値
    float m_oldValue;
    // Progressの値
    float m_Value;
    // プログレスの向いてる方向
    ProgressType m_ProgressType;
public:
    void Init() override;
    void Uninit() override {}
    void Update() override;
    void Draw() override {}

    // バーを設置します
    void SetProgressBar(class SpriteComponent* Blank, class SpriteComponent* Full)
    {
        m_BlankProgress = Blank;
        m_FullProgress = Full;
    }
    
    // フル状態の値設置
    void SetMaxValue(float Val) { m_MaxValue = Val; }

    // 現在状態の値設置
    void SetCurrentValue(float Val) { m_NexValue = Val; }

    // Progressの向きを設置
    void SetProgressType(ProgressType PT) { m_ProgressType = PT; }

    // Progressの値のセッター
    float GetProgressValue() { return m_Value; }
};

