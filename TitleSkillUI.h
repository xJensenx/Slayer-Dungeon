#pragma once
#include "GameObject.h"
class TitleSkillUI :
    public GameObject
{
private:
    // スキル種類
    class TitleSkillUIType* m_SkillType;
    // 選ばれたテクスチャ
    class SpriteComponent* m_Sprite;
    // 選ばれていないテクスチャ
    class SpriteComponent* m_SpriteNS;
    // 選ばれている状態
    bool m_Chosen;
    // 表示用だけ
    bool m_JustForShow;
    // 隠れている
    bool m_Hiding;

public:
    void Init() override;
    void Update() override;

    // スキルの種類をセット
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

    // 選ばれているをセット
    void SetChosen(bool Chosen) { m_Chosen = Chosen; }
    // 表示用だけをセット
    void SetJustForShow(bool Show) { m_JustForShow = Show; }
    // 隠れている状態をセット
    void SetHide(bool Hide) { m_Hiding = Hide; }


    bool GetChosen() { return m_Chosen; }
    bool GetJustForShow() { return m_JustForShow; }
};

