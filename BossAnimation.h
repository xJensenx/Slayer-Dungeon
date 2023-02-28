#pragma once
#include "AnimationManager.h"
#include "BossAnimationState.h"

class BossAnimation :
    public AnimationManager
{
private:
	// ボス
	class Boss* m_Character = NULL;
	// アニメーションステート
	class BossAnimationState* m_AnimationState;
	// 前のアニメーションステート
	class BossAnimationState* m_PrevAnimationState;

	// ゲーム用
	bool m_isJumpFinish = false; // ジャンプ中はフレームを止まる
	bool m_isReadyJump = false; // ジャンプの準備
	bool m_isJumpDmg = false;	// ジャンプの攻撃ダメージしたかどうか

public:
    void Init() override;
    void Uninit() override;
    void Update() override;

	// ジャンプのダメージを取得
	bool GetJumpDmg() { return m_isJumpDmg; }
	// ジャンプの準備の情報を取る
	bool GetReadyJump() { return m_isReadyJump; }
	// ジャンプが終わるのゲッター
	bool GetJumpFinish() { return m_isJumpFinish; }

	// 前のアニメーションステートを取得
	template <typename T>
	bool GetPrevAnimationState()
	{
		// ステートがないとfalseをreturn
		if (m_PrevAnimationState == NULL) return false;
		
		// 同じ種類ならreturnする
		if (typeid(*m_PrevAnimationState) == typeid(T)) return true;


		return false;
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

	// ステートを変える処理
	template <typename T>
	void ChangeState()
	{
		// アニメーションステートがNULLではない場合は終了処理を行う
		if (m_AnimationState != NULL)
		{
			if (m_PrevAnimationState != NULL)
			{
				m_PrevAnimationState->Uninit();
				delete m_PrevAnimationState;
				m_PrevAnimationState = NULL;
			}
			m_PrevAnimationState = m_AnimationState;
			m_CurFrame = m_AnimationState->GetFrame();
			m_PrevLoop = m_AnimationState->GetLoop();		// 前回のループ状態を更新する
		}

		m_PrevFrame = m_CurFrame;	// 前のフレーム数を現在のフレーム数に更新する
		m_CurFrame = 0.0f;			// 現在のフレーム数を０にする（最初から始める）
		m_BlendRate = 0.0f;			// ブレンドレートを０にする
		m_PrevAnimationName = m_CurAnimationName; // 前のアニメーション名前を更新する
		m_isReadyJump = false;		// ジャンプ用
		m_isJumpDmg = false;		// ジャンプダメージ用

		// アニメーションステートを追加処理
		m_AnimationState = new T();
		// ボスの設置
		m_AnimationState->SetCharacter(m_Character);
		// アニメーションマネージャーの設置
		m_AnimationState->SetAnimationTree(this);
		// アニメーションステートの初期化
		m_AnimationState->Init();
		// 現在のループを取得
		m_CurLoop = m_AnimationState->GetLoop();

		// アニメーションをロード
		m_AnimModel->LoadAnimation(m_PrevAnimationName, m_CurAnimationName);
	}

	// ボスの変数を入れる
	void SetCharacter(class Boss* Character)
	{
		m_Character = Character;
	}

	// ジャンプの変数を調整する
	void SetJumpFinish(bool isFinish)
	{
		m_isJumpFinish = isFinish;
	}
	// ジャンプ準備のセッター
	void SetReadyJump(bool Ready)
	{
		m_isReadyJump = Ready;
	}
	// ジャンプダメージのセッター
	void SetJumpDmg(bool Dmg)
	{
		m_isJumpDmg = Dmg;
	}
};

