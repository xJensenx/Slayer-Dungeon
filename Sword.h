#pragma once
#include "GameObject.h"
#include "SwordStatus.h"

class Sword :
    public GameObject
{
public:
    // この剣がどの位置にいるか
    enum SwordPosition
    {
        First = 0,
        Second,
        Third,
        Fourth,
        Fifth
    };

private:
    class SwordStatus* m_SwordStatus;

    class SwordTrail* m_SwordTrail;

    // プレイヤークラス
    class Player* m_Character = NULL;
    // 剣の位置
    SwordPosition m_SwordPos;
    // 打つ時の現在時間
    float m_CurShootTime;
    // 目標まで到達するまでの時間
    const float m_TotalShootTime = 1.0f * Manager::Time;
    // 防御の時剣が来る時間
    const float m_TotalBlockTime = 0.2f * Manager::Time;
    // 待機状態に戻る時間
    const float m_TotalIdleTime = 0.2f * Manager::Time;
    // 目標
    class GameObject* m_TargetObj = NULL;
    // 目標ターゲット地点
    D3DXVECTOR3 m_TargetPos;
    // 攻撃時間
    float m_TotalAttackTime;
    // 初期ポジション
    D3DXVECTOR3 m_InitPos;
    // 初期ローテーション
    D3DXVECTOR3 m_InitRot;
    // 最初のUpを取得
    D3DXVECTOR3 m_InitUp;
    // 目標ポジション（攻撃用）
    D3DXVECTOR3 m_EndPos;
    // 目標Tangent（攻撃用）
    D3DXVECTOR3 m_EndTan;
    // 攻撃成功したかどうか
    bool m_Damaged;
    // 攻撃力
    float m_AtkDmg;
    // Ultのカメラシェーク
    bool m_isShake;
    // シェークの強さ
    float m_ShakeStr;
    // 剣の軌跡の色
    D3DXVECTOR4 m_SwordTrailColor;
    // Skill06の撃つ回数
    int m_ShootCnt;
    
    // 待機状態のアニメーション用時間
    float m_IdleAnimTime;
    int m_IdleState;

public:
    void Init() override;
    void Uninit() override;
    void Update() override;

    // ソードステータスを追加
    template <typename T>
    T* SetSwordStatus()
    {
        if (m_SwordStatus != NULL)
        {
            delete m_SwordStatus;
            m_SwordStatus = NULL;
        }

        T* Stat = new T();
        Stat->SetCharacter(this);
        Stat->Init();
        m_SwordStatus = Stat;
        return (T*)m_SwordStatus;
    }
    // トレールを初期化
    void InitSwordTrail();

    void SetCharacter(Player* P, SwordPosition SP);

    // Skill06の剣初期化
    void ShootSwordSkill06(GameObject* Target, int ShootCnt)
    {
        m_TargetObj = Target;
        m_InitUp = GetQuaternionUp();
        m_ShootCnt = ShootCnt;
        SetSwordStatus<SwordSkill06>();
    }
    // Skill06の剣初期化
    void ShootSwordSkill06(D3DXVECTOR3 Target, int ShootCnt)
    {
        m_TargetPos = Target;
        m_InitUp = GetQuaternionUp();
        m_ShootCnt = ShootCnt;
        SetSwordStatus<SwordSkill06>();
    }

    // 剣を射出する
    void ShootSword(GameObject* Target)
    {
        m_TargetObj = Target;
        m_CurShootTime = 0.0f;
        m_InitPos = m_Position;
        m_InitUp = GetQuaternionUp();
        SetSwordStatus<SwordShoot>();
    }
    // 剣を射出する
    void ShootSword(D3DXVECTOR3 Target)
    {
        m_TargetPos = Target;
        m_CurShootTime = 0.0f;
        m_InitPos = m_Position;
        m_InitUp = GetQuaternionUp();
        SetSwordStatus<SwordShoot>();
    }
    // 剣を直線で射出
    void ShootStraightSword(D3DXVECTOR3 Target)
    {
        m_TargetPos = Target;
        m_CurShootTime = 0.0f;
        m_InitPos = m_Position;
        SetSwordStatus<SwordShootStraight>();
    }

    // 剣で攻撃する
    void AttackSword(D3DXVECTOR3 InitPos, D3DXVECTOR3 InitTan, D3DXVECTOR3 EndPos, D3DXVECTOR3 EndTan, float AtkTime)
    {
        m_Damaged = false;
        m_InitPos = InitPos;
        m_InitUp = InitTan;
        m_EndPos = EndPos;
        m_EndTan = EndTan;
        m_CurShootTime = 0.0f;
        m_TotalAttackTime = AtkTime * Manager::Time;

        SetSwordStatus<SwordAttack>();
    }

    // 剣で攻撃する
    void AttackSword_Skill(D3DXVECTOR3 InitPos, D3DXVECTOR3 InitTan, D3DXVECTOR3 EndPos, D3DXVECTOR3 EndTan, float AtkTime)
    {
        m_Damaged = false;
        m_InitPos = InitPos;
        m_InitUp = InitTan;
        m_EndPos = EndPos;
        m_EndTan = EndTan;
        m_CurShootTime = 0.0f;
        m_TotalAttackTime = AtkTime * Manager::Time;

        SetSwordStatus<SwordAttack_ForSkill>();
    }

    // 剣で防御する
    void DefenseSword(D3DXVECTOR3 InitPos, D3DXVECTOR3 InitRot)
    {
        m_InitPos = InitPos;
        m_InitRot = InitRot;
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordBlock>();
    }

    // QTEの剣の射出
    void QTEShootSword(D3DXVECTOR3 Tar)
    {
        m_InitPos = m_Position;
        m_EndPos = Tar;
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordQTE>();
    }

    // 待機状態に戻る
    void BackToIdle()
    {
        m_InitPos = m_Position;
        m_InitRot = m_Rotation;
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordIdle>();
    }

    // 剣でUltを使う
    void UltSword()
    {
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordUlt>();
    }

    // 攻撃力をセット
    void SetAtkDmg(float AtkDmg) { m_AtkDmg = AtkDmg; }

    // 剣の軌跡の色を調整
    void ChangeTrailColor(D3DXVECTOR4 _Color) { m_SwordTrailColor = _Color; }

    // TrailRenderer（剣の軌跡）
    void TrailEffect();
    
    // HitEffect
    void HitEffect(D3DXVECTOR3 HitPos);
    
    // DissolveEffect
    void DissolveEffect();

    void SetIdleAnimTime(float T) { m_IdleAnimTime = T; }

    // ShakeStrを設置する
    void SetShakeStr(float ShakeStr) { m_ShakeStr = ShakeStr; }

    //
    class GameObject* GetTargetObj() { return m_TargetObj; }

    // キャラクターをゲット
    class Player* GetCharacter() { return m_Character; }

    //
    D3DXVECTOR3 GetTargetPos() { return m_TargetPos; }

    // 
    D3DXVECTOR3 GetInitUp() { return m_InitUp; }

    //
    D3DXVECTOR3 GetEndPos() { return m_EndPos; }

    D3DXVECTOR3 GetEndTan() { return m_EndTan; }

    float GetTotalAtkTime() { return m_TotalAttackTime; }

    float GetShakeStr() { return m_ShakeStr; }

    int GetShootCnt() { return m_ShootCnt; }

    // 攻撃力を取得
    float GetAtkDmg() { return m_AtkDmg; }

    // ソードの置く位置をゲット
    SwordPosition GetSwordPos() { return m_SwordPos; }
};

