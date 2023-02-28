#pragma once
#include "GameObject.h"
class PlayerMpBar :
    public GameObject
{
private:
    // プレイヤークラス
    class Player* m_Character = NULL;
    // フルの状態のスプライト
    class SpriteComponent* m_PlayerFullMpBar;
    // フルの状態のスプライト
    class SpriteComponent* m_PlayerNoMpBar;

    // 足りない状態
    bool m_Insufficient;
    // 表示時間
    float m_InsufficientTime;
public:
    void Init() override;
    void Update() override;

    // キャラクターの設置
    void SetCharacter(Player* P) { m_Character = P; }

    // 足りない状態を設置する
    void SetInsufficient() { m_Insufficient = true; m_InsufficientTime = 0.0f; }
};

