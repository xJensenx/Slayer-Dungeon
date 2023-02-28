#pragma once
#include "GameObject.h"
class PressContinue :
    public GameObject
{
private:
    // もう指定した座標に移動したか
    bool m_isReady = false;
    // 消える準備
    bool m_Disappear = false;
    // 色のステート
    int m_State = 0;    // 0 = 減少、1 = 増加
    // 色の線形補間用時間
    float m_Time;
    // 色の線形補間用最大時間
    float m_MaxTime = 2.0f * Manager::Time;
    
public:
    void Init() override;
    void Update() override;

    void Disappear();
};

