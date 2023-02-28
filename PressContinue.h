#pragma once
#include "GameObject.h"
class PressContinue :
    public GameObject
{
private:
    // �����w�肵�����W�Ɉړ�������
    bool m_isReady = false;
    // �����鏀��
    bool m_Disappear = false;
    // �F�̃X�e�[�g
    int m_State = 0;    // 0 = �����A1 = ����
    // �F�̐��`��ԗp����
    float m_Time;
    // �F�̐��`��ԗp�ő厞��
    float m_MaxTime = 2.0f * Manager::Time;
    
public:
    void Init() override;
    void Update() override;

    void Disappear();
};

