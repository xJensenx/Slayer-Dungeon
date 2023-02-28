#pragma once
#include "GameObject.h"
class QTEButton :
    public GameObject
{
private:
    // アニメーションステート
    int m_State;
    // 時間
    float m_CurTime;
public:
    void Init() override;
    void Update() override;

};

