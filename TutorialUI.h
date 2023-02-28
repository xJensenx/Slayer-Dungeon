#pragma once
#include "GameObject.h"
#include "TutorialUIType.h"
class TutorialUI :
    public GameObject
{
private:
    // 種類のクラス
    class TutorialUIType* m_UIType;
public:
    void Init() override;
    void Update() override;

    // 種類を設置
    template <typename T>
    void SetUIType()
    {
        // 既に設置してある場合は削除する
        if (m_UIType != NULL)
        {
            delete m_UIType;
            m_UIType = NULL;
        }

        T* Type = new T();
        Type->SetCharacter(this);
        Type->Init();

        m_UIType = Type;
    }

    // クリアした関数
    void SetFinish() { m_UIType->TutorialClear(); }
};

