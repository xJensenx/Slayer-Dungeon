#pragma once
#include "GameObject.h"
class TitleSkillUIEvent :
    public GameObject
{
private:
    class SpriteComponent* m_Sprite;
public:
    void Init() override;
    void Update() override;
};

