#pragma once
#include "GameObject.h"
class BossHpBar :
    public GameObject
{
private:
    class Boss* m_Character = NULL;
public:
    void Init() override;
    void Update() override;

    void SetCharacter(Boss* Character) { m_Character = Character; }
};

