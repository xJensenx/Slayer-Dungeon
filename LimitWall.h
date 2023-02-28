#pragma once
#include "GameObject.h"
class LimitWall :
    public GameObject
{
public:
    void Init() override;
    void Update() override;
};

