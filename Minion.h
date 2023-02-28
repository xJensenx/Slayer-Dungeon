#pragma once
#include "GameObject.h"
#include "MinionBehaviorTree.h"

class Minion :
    public GameObject
{
private:
    // Minionのビヘイビアツリー
    class MinionBehaviorTree* m_Behavior;

    // Minionのアニメーション
    class MinionAnimation* m_Animation = NULL;

    // Minionの移動スピード
    float m_MovementSpd = 0.075f;

    // Minionの攻撃クールダウン
    float m_AttackCD = 3.0f * Manager::Time;

    // 攻撃しているかどうか
    bool m_isAttacking;

    // 
    float m_WaitTime;

    // 最大Hp
    float m_MaxHp = 10.0f;

    // 現在Hp
    float m_CurHp;

    // もう死んでるかどうか
    bool m_isDead;

    // HpBar
    class MinionHpBar* m_HpBar;
public:
    void Init() override;       // 初期化処理
    void Update() override;     // 更新処理

    // ビヘイビアツリーを変更
    template <typename T>
    void ChangeBehavior()
    {
        // ビヘイビアツリー既にがある場合は削除する
        if (m_Behavior != NULL)
        {
            delete m_Behavior;
            m_Behavior = NULL;
        }

        T* NewBehavior = new T();
        NewBehavior->SetCharacter(this);
        NewBehavior->SetAnimationTree(m_Animation);
        NewBehavior->Init();

        m_Behavior = NewBehavior;
    }

    // ビヘイビアツリー
    void BehaviorTree();

    // 攻撃通知用イベント
    void AttackEvent();

    // 攻撃CDをセット
    void SetAttackCD(float CD) { m_AttackCD = CD * Manager::Time; }

    // 攻撃中をセット
    void SetisAttacking(bool Attack) { m_isAttacking = Attack; }

    //// 攻撃をさせる
    //void SetAttackMode(MinionBehavior MB)
    //{
    //    m_State = MB;
    //}

    // ダメージ受けた時
    void DealDamage(float Damage) override;

    // Minionの現在のHpのゲッター
    float GetCurrentHp() { return m_CurHp; }

    // Minionの最大のHpのゲッター
    float GetMaxHp() { return m_MaxHp; }

    // Minionの攻撃CDを取得
    float GetAttackCD() { return m_AttackCD; }

    // Minionの攻撃中を取得
    bool GetisAttacking() { return m_isAttacking; }

    // Minionが倒されたかどうか
    bool GetisDead() { return m_isDead; }
};

