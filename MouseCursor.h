#pragma once
#include "GameObject.h"
class MouseCursor :
    public GameObject
{
private:
    // スプライト
    class SpriteComponent* m_MouseCursor;
    class SpriteComponent* m_ClickCursor;

    // マウスカーソルが表示しているかどうか
    static bool m_Visibility;
public:
    void Init() override;
    void Update() override;

    // マウスカーソルを表示するの設定
    static void SetVisibility(bool Visible) { m_Visibility = Visible; }
};

