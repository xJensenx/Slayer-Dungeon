#pragma once
#include "GameObject.h"
class PlayerStatusWarning :
    public GameObject
{
private:
    // ステータスのスプライト
    class SpriteComponent* m_DmgTakenSprite;
    class SpriteComponent* m_BlockSprite;

    // ダメージ受けた用変数
    float m_DmgTime;
    bool m_isDmg;
    int m_DmgState;
public:
    void Init() override;
    void Update() override;

    // DmgTaken
    void DmgTaken();
};

