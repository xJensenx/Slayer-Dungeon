#pragma once
#include "GameObject.h"
class AttackMeteor :
    public GameObject
{
private:
    class Boss_AttackWarning* m_Warning;
public:
    void Init() override;
    void Update() override;
};

