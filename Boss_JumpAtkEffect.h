#pragma once
#include "GameObject.h"
class Boss_JumpAtkEffect :
    public GameObject
{
private:
    // ���ݎ���
    float m_Duration;
    // �������W�iY)
    float m_InitPosY;
    // �X�P�[�������̎���
    float m_CurTime;
    // �X�P�[���������v�ǂ̂��炢���ԕK�v
    const float m_TotalTime = 0.25f * Manager::Time;

public:
    void Init() override;
    void Update() override;

    // ���W�ݒu
    void SetInitPos() { m_InitPosY = m_Position.y; }
};

