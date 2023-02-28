#pragma once
#include "GameObject.h"
class Boss_JumpAtkEffect :
    public GameObject
{
private:
    // 存在時間
    float m_Duration;
    // 初期座標（Y)
    float m_InitPosY;
    // スケール成長の時間
    float m_CurTime;
    // スケール成長合計どのぐらい時間必要
    const float m_TotalTime = 0.25f * Manager::Time;

public:
    void Init() override;
    void Update() override;

    // 座標設置
    void SetInitPos() { m_InitPosY = m_Position.y; }
};

