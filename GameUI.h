#pragma once
#include "GameObject.h"
class GameUI :
    public GameObject
{
public:
    enum UIType
    {
        TutorialPic = 0,
        CharacterTutorial,
        MoveOrAttack
    };
private:
    // UIの種類
    UIType m_UIType;
    // SpriteComponentの変数
    class SpriteComponent* m_SpriteComponent;

    // 隠しているかどうか
    bool m_Appear;
    // 隠している座標
    D3DXVECTOR3 m_HidePos;
    // 出現している座標
    D3DXVECTOR3 m_ShowPos;

    // 出現する場所までの線形補間用時間
    float m_WaitTime;

public:
    void Init() override;
    void Update() override;

    // 出る処理
    void SetAppear(bool Appear) 
    { 
        m_WaitTime = 0.0f;
        m_Appear = Appear;
    }

    // 情報をセットする
    void LoadInfo(UIType Type);
    //  座標設置
    void SetAppearPosition(D3DXVECTOR3 AppearPos, D3DXVECTOR3 HidePos)
    {
        m_ShowPos = AppearPos;
        m_HidePos = HidePos;
    }
};

