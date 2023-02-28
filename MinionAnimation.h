#pragma once
#include "AnimationManager.h"

#include "MinionAnimationState.h"
class MinionAnimation :
    public AnimationManager
{
private:
    // Minionの情報に入れる変数
    class Minion* m_Character = NULL;
    // Minionのアニメーションステート　
    class MinionAnimationState* m_AnimationState;
    // Minionの前のアニメーションステート
    class MinionAnimationState* m_PrevAnimationState;

public:
    void Init() override;
    void Uninit() override;
    void Update() override;

    // Minionの情報をセットする
    void SetCharacter(Minion* Character) { m_Character = Character; }

    // ステートを変える処理
    template <typename T>
    void ChangeState()
    {
        // 既にステートが存在している場合
        if (m_AnimationState != NULL)
        {
            // 前のアニメーションステートが存在している場合は消します
            if (m_PrevAnimationState != NULL)
            {
                delete m_PrevAnimationState;
                m_PrevAnimationState = NULL;
            }
            // 今のステートを前のアニメーションステートに入れます
            m_PrevAnimationState = m_AnimationState;
            // 前はループしているかどうかをゲット
            m_CurLoop = m_AnimationState->GetLoop();
            m_PrevPlayRate = m_AnimationState->GetPlayRate();
            m_AnimationState = NULL;
        }

        m_PrevFrame = m_CurFrame;	// 前のフレーム数を現在のフレーム数に更新する
        m_CurFrame = 0.0f;			// 現在のフレーム数を０にする（最初から始める）
        m_BlendRate = 0.0f;			// ブレンドレートを０にする
        m_PrevLoop = m_CurLoop;		// 前回のループ状態を更新する
        m_PrevAnimationName = m_CurAnimationName;

        // 新しいステート作成
        T* State = new T();
        State->SetCharacter(m_Character);
        State->SetAnimationTree(this);
        State->Init();
        m_AnimationState = State;


        m_AnimModel->LoadAnimation(m_PrevAnimationName, m_CurAnimationName);
    }

    // 現在のアニメーションステートを取得
    template <typename T>
    bool GetCurAnimationState()
    {
        // ステートがないとfalseをreturn
        if (m_AnimationState == NULL) return false;

        // 同じ種類ならreturnする
        if (typeid(*m_AnimationState) == typeid(T)) return true;

        return false;
    }
    
    // 前のアニメーションステートを取得
    template <typename T>
    bool GetPreAnimationState()
    {
        // ステートがないとfalseをreturn
        if (m_PrevAnimationState == NULL) return false;

        // 同じ種類ならreturn trueする
        if (typeid(*m_PrevAnimationState) == typeid(T)) return true;

        return false;
    }
};


