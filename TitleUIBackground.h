#pragma once
#include "GameObject.h"
class TitleUIBackground :
    public GameObject
{
private:
    // 準備終わったかどうか
    bool m_isReady = false;
public:
    void Init() override;
    void Update() override;

    // 準備終わったかどうかを取得
    bool GetReady() { return m_isReady; }
};

