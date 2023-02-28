#pragma once
#include "GameObject.h"
class TitleSkillUI :
    public GameObject
{
private:
    // �X�L�����
    class TitleSkillUIType* m_SkillType;
    // �I�΂ꂽ�e�N�X�`��
    class SpriteComponent* m_Sprite;
    // �I�΂�Ă��Ȃ��e�N�X�`��
    class SpriteComponent* m_SpriteNS;
    // �I�΂�Ă�����
    bool m_Chosen;
    // �\���p����
    bool m_JustForShow;
    // �B��Ă���
    bool m_Hiding;

public:
    void Init() override;
    void Update() override;

    // �X�L���̎�ނ��Z�b�g
    template <typename T>
    void SetSkillType()
    {
        if (m_SkillType != NULL)
        {
            delete m_SkillType;
            m_SkillType = NULL;
        }

        T* SkillType = new T();
        SkillType->SetInfo(this, m_Sprite, m_SpriteNS);
        SkillType->Init();
        
        m_SkillType = SkillType;
    }

    void ClickSkillEvent();

    // �I�΂�Ă�����Z�b�g
    void SetChosen(bool Chosen) { m_Chosen = Chosen; }
    // �\���p�������Z�b�g
    void SetJustForShow(bool Show) { m_JustForShow = Show; }
    // �B��Ă����Ԃ��Z�b�g
    void SetHide(bool Hide) { m_Hiding = Hide; }


    bool GetChosen() { return m_Chosen; }
    bool GetJustForShow() { return m_JustForShow; }
};

