#pragma once
#include "GameObject.h"
class TitleUI :
    public GameObject
{
public:
    enum UIType
    {
        StartGame = 0,
        Setting,
        QuitGame,
        ChooseFile,
        BackButton,
        StageSelect,
        ModeSelect,
        StageButton,
        StatusButton,
        SkillButton,
        TutorialStage,
        Stage01,
        LockStage,
        Skill01,
        Skill02,
        Skill03,
    };
private:
    // UIの種類
    UIType m_UIType;
    // 選択されていない時のSpriteComponent
    class SpriteComponent* m_NSSprite;
    // 選択されている時のSpriteComponent
    class SpriteComponent* m_Sprite;
    // スキル表示用
    class TitleSkillUI* m_ShowSkill;
    // 表示用スキルに登録している番号
    int m_SkillNumber;

    // Number
    class Number* m_SkillPoint;
    // 選択されているかどうか
    bool m_Chosen = false;
    // ロックされてるかどうか
    bool m_isLock = false;
    // 出番
    bool m_Appear = false;
    // スクリーンに出てる時の座標
    D3DXVECTOR3 m_ScreenPos;
    // 出番じゃない時の座標
    D3DXVECTOR3 m_HidePos;
    // 移動用タイム
    float m_MoveTime;
    // 選択できない
    bool m_CantChoose = false;
    // 移動時間
    const float m_TotalMoveTime = 0.5f * Manager::Time;

public:
    void Init() override;
    void Update() override;
    // SpriteComponentなどの初期化
    void LoadInfo(UIType UIType);
    // 選択されているかどうかのセッター
    void SetChosen(bool Chosen) { m_Chosen = Chosen; }


    // UIの種類を返す
    UIType GetType() { return m_UIType; }
    // 選択されているかどうかのゲッター
    bool GetChosen() { return m_Chosen; }

    D3DXVECTOR3 GetWorldPosition();
    // 移動時間をゲット
    float GetTotalMoveTime() { return m_TotalMoveTime; }
    // 出番を取得
    bool GetAppear() { return m_Appear; }
    // 選択できないを取得
    bool GetCantChoose() { return m_CantChoose; }

    // ロックするかどうか
    void SetisLock(bool Lock) { m_isLock = Lock; }

    // ロックのゲッター
    bool GetisLock() { return m_isLock; }

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

    // スキルポイントの数をセット
    void SetSkillPointNum(int Num);
};

