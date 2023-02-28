#pragma once
#include "GameObject.h"
class Meteor :
    public GameObject
{
private:
    // 待機状態
    bool m_Idle;
    // 待機状態のステート
    int m_State;
    // 待機状態用時間
    float m_CurTime;
    // 初期座標
    D3DXVECTOR3 m_InitPos;
public:
    void Init() override;
    void Update() override;

    // 待機状態の設置
    void SetIdle(bool Idle) { m_Idle = Idle; m_InitPos = m_Position; }

    // 待機状態の動き
    void IdleAnimation();
    
    // 投げる時の動き
    void ThrowAnimation();
};

