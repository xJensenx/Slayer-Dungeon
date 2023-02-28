#pragma once
#include "GameObject.h"
class PlayerSkillUI :
    public GameObject
{
private:
    class SpriteComponent* m_FullSprite;
    class SpriteComponent* m_NoSprite;

    class PlayerSkillUIType* m_SkillType;

    // �v���C���[
    class Player* m_Character;

    // ����UI�͉��̔ԍ����w�肵�Ă���
    int m_Slot;
    // �g��MP��
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

    // �v���C���[���Z�b�g
    void SetCharacter(class Player* Char) { m_Character = Char; }

    // �X���b�g���Z�b�g
    void SetSlot(int Slot);

    // �g��Mp�ʂ��Z�b�g
    void SetUseMp(float Mp) { m_UseMp = Mp; }

    // �t���X�v���C�g���Q�b�g
    class SpriteComponent* GetFullSprite() { return m_FullSprite; }

    // ��̃X�v���C�g���Q�b�g
    class SpriteComponent* GetNoSprite() { return m_NoSprite; }
};

