#pragma once
#include "GameObject.h"
class PlayerSkillUI :
    public GameObject
{
private:
    class SpriteComponent* m_FullSprite;
    class SpriteComponent* m_NoSprite;

    class PlayerSkillUIType* m_SkillType;

    // プレイヤー
    class Player* m_Character;

    // このUIは何の番号を指定している
    int m_Slot;
    // 使うMP量
    float m_UseMp;

public:
    void Init() override;
    void Update() override;

    template <typename T>
    void SetSkillType()
    {
        if (m_SkillType != NULL)
        {
            delete m_SkillType;
            m_SkillType = NULL;
        }

        T* Type = new T();
        Type->SetCharacter(this);
        Type->Init();
        m_SkillType = Type;
    }

    // プレイヤーをセット
    void SetCharacter(class Player* Char) { m_Character = Char; }

    // スロットをセット
    void SetSlot(int Slot);

    // 使うMp量をセット
    void SetUseMp(float Mp) { m_UseMp = Mp; }

    // フルスプライトをゲット
    class SpriteComponent* GetFullSprite() { return m_FullSprite; }

    // 空のスプライトをゲット
    class SpriteComponent* GetNoSprite() { return m_NoSprite; }
};

