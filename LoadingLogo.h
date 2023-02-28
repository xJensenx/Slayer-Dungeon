#pragma once
#include "GameObject.h"
class LoadingLogo :
    public GameObject
{
private:
    // テクスチャの何番の座標
    int m_Cnt;
public:
    void Init() override;
    void Update() override;
};

