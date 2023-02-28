#pragma once
#include "GameObject.h"
class PlayerDpBar :
    public GameObject
{
private:
    class SpriteComponent* m_FullSprite;
    class SpriteComponent* m_NoSprite;

    class Player* m_Character;

public:
    void Init() override;
    void Update() override;

    void SetCharacter(class Player* Character) { m_Character = Character; }
};

