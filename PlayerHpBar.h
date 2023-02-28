#pragma once
#include "GameObject.h"
class PlayerHpBar :
    public GameObject
{
private:
    class Player* m_Character = NULL;
public:
    void Init() override;
    void Update() override;

    void SetCharacter(Player* P) { m_Character = P; }
};

