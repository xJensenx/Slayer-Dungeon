#pragma once
#include "GameObject.h"
class PlayerCommand :
    public GameObject
{
public:
    enum CommandType
    {
        Command_Logo = 0,
        Command_Attack,
        Command_Ult
    };

private:
    // コマンドの種類
    CommandType m_CommandType;
    // 選ばれているかどうか
    bool m_Chosen;

    // 待機状態テクスチャ
    class SpriteComponent* m_Sprite;

    // 選ばれたテクスチャ
    class SpriteComponent* m_ChosenSprite;

    // アニメーション時間
    float m_WaitTime;

    // アニメーションの指定時間
    const float m_TotalTime = 0.1f * Manager::Time;

    // 選ばれていない時のXサイズ
    const float m_NormalSize = 350.0f;

    // 選ばれている時のXサイズ
    const float m_ChosenSize = 450.0f;

    // 使うDP量
    float m_UseDp;

public:
    void Init() override;
    void Update() override;
   
    // コマンドの種類を設定する
    void SetCommandType(CommandType _CT);

    // コマンドを選ぶ状態
    void SetChosen(bool _C)
    {
        m_Chosen = _C;
        if (m_WaitTime >= m_TotalTime)
        {
            m_WaitTime = 0.0f;
        }
    }

    // 使うDPをセット
    void SetUseDp(float Dp) { m_UseDp = Dp; }


    // コマンドが選ばれているかどうかのゲッター
    bool GetChosen() { return m_Chosen; }

    // コマンドの種類をゲットする
    CommandType GetCommandType() { return m_CommandType; }
};

