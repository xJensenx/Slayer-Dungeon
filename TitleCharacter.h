#pragma once
#include "GameObject.h"
class TitleCharacter :
    public GameObject
{
private:
    // 選ばれたアニメーション終わったかどうか
    bool m_AnimationFinish = false;
public:
    void Init() override;
    void Chosen();
    // アニメーション終わった
    void SetAnimationFinish() { m_AnimationFinish = true; }
    // アニメーション終わったかどうかゲッター
    bool CheckFinish();
};

