#pragma once
#include "GameObject.h"
#include "PauseMenuUIType.h"

class PauseMenuUI :
    public GameObject
{
private:
    // UIの種類
    class PauseMenuUIType* m_UIType;

    // 選択されているスプライト
    class SpriteComponent* m_Sprite;
    // 選択されていないスプライト
    class SpriteComponent* m_NSSprite;

    // 選択されているかどうか
    bool m_Chosen;

public:
    void Init() override;
    void Update() override;

    // 種類のセッター
    template <typename T>
    void SetType()
    {
        T* Type = new T();
        Type->SetCharacter(this);
        Type->Init();
        m_UIType = Type;
    }

    // 種類のゲッター
    template <typename T>
    T* GetType()
    {
        if (typeid(*m_UIType) == typeid(T))
        {
            return (T*)m_UIType;
        }

        return NULL;
    }

    // 選択されているスプライトのゲッター
    class SpriteComponent* GetSprite() { return m_Sprite; }

    // 選択されていないスプライトのゲッター
    class SpriteComponent* GetNSSprite() { return m_NSSprite; }

    // 選ばれているのセッター
    void SetChosen(bool Chosen) { m_Chosen = Chosen; }

    // 選ばれているのゲッター
    bool GetChosen() { return m_Chosen; }
};

