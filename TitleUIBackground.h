#pragma once
#include "GameObject.h"
class TitleUIBackground :
    public GameObject
{
private:
    // €”õI‚í‚Á‚½‚©‚Ç‚¤‚©
    bool m_isReady = false;
public:
    void Init() override;
    void Update() override;

    // €”õI‚í‚Á‚½‚©‚Ç‚¤‚©‚ğæ“¾
    bool GetReady() { return m_isReady; }
};

