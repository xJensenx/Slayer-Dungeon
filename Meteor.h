#pragma once
#include "GameObject.h"
class Meteor :
    public GameObject
{
private:
    // �ҋ@���
    bool m_Idle;
    // �ҋ@��Ԃ̃X�e�[�g
    int m_State;
    // �ҋ@��ԗp����
    float m_CurTime;
    // �������W
    D3DXVECTOR3 m_InitPos;
public:
    void Init() override;
    void Update() override;

    // �ҋ@��Ԃ̐ݒu
    void SetIdle(bool Idle) { m_Idle = Idle; m_InitPos = m_Position; }

    // �ҋ@��Ԃ̓���
    void IdleAnimation();
    
    // �����鎞�̓���
    void ThrowAnimation();
};

