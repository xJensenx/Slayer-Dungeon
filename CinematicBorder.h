#pragma once
#include "GameObject.h"
class CinematicBorder :
    public GameObject
{
public:
    enum PositionType
    {
        Top = 0,
        Bot
    };
private:
    // カットシーンではない時の上の座標
    const D3DXVECTOR3 m_TopHidePos = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 16, 0.0f);
    // カットシーンではない時の下の座標
    const D3DXVECTOR3 m_BotHidePos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT + (SCREEN_HEIGHT / 16), 0.0f);
    // 上の座標
    const D3DXVECTOR3 m_TopPosition = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 16, 0.0f);
    // 下の座標
    const D3DXVECTOR3 m_BotPosition = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 16), 0.0f);
    // ポジションタイプ
    PositionType m_PosType;
    // カットシーン用時間
    float m_CurTime;
    const float m_TotalTime = 3.0f * Manager::Time;

public:
    void Init() override;
    void Update() override;

    // ポジションタイプのセッター
    void SetPosType(PositionType PT);
    // カットシーンの発動
    void SetCutscene(bool CutScene)
    {
        m_CurTime = 0.0f;
        m_Cinematic = CutScene;
    }
};

