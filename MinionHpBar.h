#pragma once
#include "GameObject.h"
class MinionHpBar :
    public GameObject
{
private:
    class Minion* m_Character = NULL;
public:
    void Init() override;
    void Update() override;

    // Minion���Z�b�g����
    void SetCharacter(Minion* Char) { m_Character = Char; }
};

