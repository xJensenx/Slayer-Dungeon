#pragma once
#include "GameObject.h"
class LoadingLogo :
    public GameObject
{
private:
    // �e�N�X�`���̉��Ԃ̍��W
    int m_Cnt;
public:
    void Init() override;
    void Update() override;
};

