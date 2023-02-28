#pragma once
#include "GameObject.h"
class TitleEvent :
    public GameObject
{
private:
    class SpriteComponent* m_ChooseSC;
    class SpriteComponent* m_LockSC;

    // 押してからの待機時間
    float m_WaitTime;
public:
    void Init() override;
    void Update() override;
};

