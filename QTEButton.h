#pragma once
#include "GameObject.h"
class QTEButton :
    public GameObject
{
private:
    // �A�j���[�V�����X�e�[�g
    int m_State;
    // ����
    float m_CurTime;
public:
    void Init() override;
    void Update() override;

};

