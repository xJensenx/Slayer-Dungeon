#pragma once
#include "GameObject.h"
class TitleUIBackground :
    public GameObject
{
private:
    // �����I��������ǂ���
    bool m_isReady = false;
public:
    void Init() override;
    void Update() override;

    // �����I��������ǂ������擾
    bool GetReady() { return m_isReady; }
};

