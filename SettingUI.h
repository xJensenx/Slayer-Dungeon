#pragma once
#include "GameObject.h"

#include "SettingUI_Type.h"
class SettingUI :
    public GameObject
{
private:
    // UIの種類
    class SettingUI_Type* m_UIType;
    // 出現しているかどうか
    bool m_Appear;
    // 移動時間
    float m_MoveTime;
    // 隠している座標
    D3DXVECTOR3 m_HidePos;
    // 出ている座標
    D3DXVECTOR3 m_ScreenPos;
public:
    void Init() override;
    void Uninit() override;
    void Update() override;

    // 出番を設置
    void SetAppear(bool Appear)
    {
        m_MoveTime = 0.0f;
        m_Appear = Appear;
    }
    // 座標設置
    void SetAppearPos(D3DXVECTOR3 AppearPos, D3DXVECTOR3 HidePos)
    {
        m_ScreenPos = AppearPos;
        m_HidePos = HidePos;
    }

    // UIの種類をセット
    template <typename T>
    void SetUIType()
    {
        // 既に存在している場合は消します
        if (m_UIType != NULL)
        {
            delete m_UIType;
            m_UIType = NULL;
        }

        T* Type = new T();
        Type->SetSettingUI(this);
        Type->Init();
        m_UIType = Type;
    }
};

