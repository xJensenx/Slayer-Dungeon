#pragma once
#include "GameObject.h"

class Boss :
    public GameObject
{
public:
    enum BossPhase
    {
        NormalPhase = 0,
        RagePhase
    };

    enum AttackType
    {
        HeavyAtk = 0,
        JumpAtk,
        JumpAtkSec,
        KnockBackAtk
    };
private:

    // アニメーションマネージャー
    class BossAnimation* m_BossAnimation;

    class BossBehaviorTree* m_BehaviorTree;

    // デバッグ用
    bool m_Debug = false;
    
    // ボスのAI用変数
    bool m_PlayerFound = false;                 // プレイヤーが見つかったかどうか
    bool m_Attackable = false;                  // 攻撃できるかどうか
    D3DXVECTOR3 m_TargetPos;                    // 追うターゲットの座標
    float m_ChaseSpd;                           // プレイヤーを追うスピード
    float m_CDTime = 3.0f * Manager::Time;// ジャンプ攻撃のクールダウン
    bool m_CoolDown = false;                    // ジャンプ攻撃がクールダウン中かどうか
    bool m_isAttacking = false;                 // 攻撃しているかどうか
    float m_CurHp;                              // ボスの現在のHp
    float m_MaxHp;                              // ボスのフルのHp
    bool m_isDead;                              // ボスが死んでいるかどうか
    bool m_HalfHp = false;                      // ボスが半分のHpまで行ったか（行ったらQTEを発生します）
    BossPhase m_BossPhase;                      // ボスの段階
    float m_BossJumpCurTime;                    // 
    D3DXVECTOR3 m_JumpStartPosition;            // 
    D3DXVECTOR3 m_JumpEndPosition;              // 
    const float m_BossJumpMaxTime = 3.0f * Manager::Time;    // 目標まで至る時間（線形補間用）

    // QTE用
    int m_QTEState;                             // QTEのステート（順番）
    bool m_QTEFinish = false;                   // QTEイベントが完了したかどうか
    float m_QTETime;                            // QTE用タイム
    D3DXVECTOR3 m_QTEInitPos;                   // QTE用初期座標
    D3DXVECTOR3 m_QTETarPos;                    // QTE用目的座標
    D3DXVECTOR3 m_QTECamTar;                    // QTE用カメラターゲット
    class Meteor* m_Meteor[3];                  // QTEの隕石攻撃
    class Sword* m_PlayerSword;                 // QTEのプレイヤーのソード
    class QTEButton* m_QTEButton;               // QTE用ボタン


public:
    // ビヘイビアツリー追加
    template<typename T>
    void ChangeBehaviorTree()
    {
        if (m_BehaviorTree != NULL)
        {
            delete m_BehaviorTree;
        }

        T* Behavior = new T();
        Behavior->SetCharacter(this);
        Behavior->SetAnimationTree(m_BossAnimation);
        Behavior->Init();
        m_BehaviorTree = Behavior;
    }

    // ビヘイビアツリーチェック
    template<typename T>
    T* GetBehaviorTree()
    {
        if (typeid(*m_BehaviorTree) == typeid(T))
        {
            return (T*)m_BehaviorTree;
        }

        return NULL;
    }

    void Init() override;
    void Uninit() override;
    void Update() override;
    void DealDamage(float damage) override;
    
    //// 攻撃通知用イベント
    //void AttackEvent(AttackType AtkType);

    // 攻撃通知用イベント
    template <typename T>
    void AttackEvent()
    {
        T* Attack = new T();
        Attack->SetCharacter(this);
        Attack->DamageEvent();
        delete Attack;
    }

    // ジャンプのアニメーション再開できる
    void SetAlmostJumpFinish();

    // 攻撃が終わる時の処理
    void StartCoolDown();

    // ジャンプ攻撃によってエフェクト
    void JumpAtkEffect();

    // 隕石召喚関数
    void SummonMeteor();
    
    // プレイヤーの周りに回すファイアボールを召喚する
    void ShootSpinningFireBall();

    // ファイアボールを召喚関数
    void ShootFireBall();

    // ファイアボールを召喚（エルミート）
    void ShootHermiteBall();

    // ボスのQTEイベント
    void BossQuickTimeEvent();

    // クールダウンをセット
    void SetCoolDown(bool CD) { m_CoolDown = CD; }

    // 攻撃中をセット
    void SetisAttacking(bool isAttack) { m_isAttacking = isAttack; }

    // 半分のHpのセッター
    void SetHalfHp(bool HalfHp) { m_HalfHp = HalfHp; }

    // ボスのQTEステートを変える
    void SetQTEState(int State) { m_QTEState = State; }

    // QTEFinishをセット
    void SetQTEFinish(bool Finish) { m_QTEFinish = Finish; }

    // ボスの段階をセット
    void SetBossPhase(BossPhase Phase) { m_BossPhase = Phase; }

    void SetBossJumpCurTime(float Time) { m_BossJumpCurTime = Time; }

    void SetBossJumpStartPosition(D3DXVECTOR3 Pos) { m_JumpStartPosition = Pos; }

    void SetBossJumpEndPosition(D3DXVECTOR3 Pos) { m_JumpEndPosition = Pos; }

    float GetBossJumpCurTime() { return m_BossJumpCurTime; }

    D3DXVECTOR3 GetBossJumpStartPos() { return m_JumpStartPosition; }

    D3DXVECTOR3 GetBossJumpEndPos() { return m_JumpEndPosition; }

    float GetBossJumpMaxTime() { return m_BossJumpMaxTime; }
    // ターゲットPosを取得
    D3DXVECTOR3 GetTargetPos() { return m_TargetPos; }

    // クールダウン
    bool GetCoolDown() { return m_CoolDown; }

    // 半分のHpを取得
    bool GetHalfHp() { return m_HalfHp; }

    // 現在のHpを取得
    float GetCurHp() { return m_CurHp; }

    // フルのHpを取得
    float GetMaxHp() { return m_MaxHp; }

    // 死んでる状態を取得
    bool GetIsDead() { return m_isDead; }

    // ChaseSpdを取得
    float GetChaseSpd() { return m_ChaseSpd; }

    // 現在の段階をゲットする
    BossPhase GetBossPhase() { return m_BossPhase; }

    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    // 暴走状態のスキル

    // 暴走状態の隕石召喚
    void RageSummonMeteor(int Cnt);
    // ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
};

