#pragma once
#include "GameObject.h"
class Boss_AttackWarning :
    public GameObject
{
public:
    void Init() override;
    void Update() override;
};

