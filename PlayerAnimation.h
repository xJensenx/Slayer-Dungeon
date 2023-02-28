#pragma once
#include "AnimationManager.h"
#include "PlayerAnimationState.h"
#include "Player.h"
#include "Tutorial.h"

class PlayerAnimation : public AnimationManager
{
private:
	// プレイヤーのキャラクター情報を取得
	class Player* m_Character;
	// プレイヤーのアニメーションステート
	class PlayerAnimationState* m_AnimationState;
	// 前のアニメーションステート
	class PlayerAnimationState* m_PrevAniState;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	// プレイヤーのセッター
	void SetCharacter(Player* Player) { m_Character = Player; }

	// プレイヤーのアニメーションを変える
	template <typename T>
	void ChangeState()
	{
		if (m_AnimationState != NULL)
		{
			if (m_PrevAniState != NULL)
			{
				m_PrevAniState->Uninit();
				delete m_PrevAniState;
				m_PrevAniState = NULL;
			}
			m_PrevAniState = m_AnimationState;
			m_CurFrame = m_AnimationState->GetFrame();
			m_PrevLoop = m_AnimationState->GetLoop();
			m_PrevPlayRate = m_AnimationState->GetPlayRate();
		}

		m_PrevAnimationName = m_CurAnimationName;
		m_PrevFrame = m_CurFrame;	// 前のフレーム数を現在のフレーム数に更新する
		m_CurFrame = 0.0f;			// 現在のフレーム数を０にする（最初から始める）
		m_BlendRate = 0.0f;			// ブレンドレートを０にする
		m_PrevLoop = m_CurLoop;		// 前回のループ状態を更新する

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

		m_AnimModel->LoadAnimation(m_PrevAnimationName, m_CurAnimationName);
	}

	// 前のアニメーションステートを取得
	template <typename T>
	bool GetPrevAnimationState()
	{
		// ステートがないとfalseをreturn
		if (m_PrevAniState == NULL) return false;

		// 同じ種類ならreturnする
		if (typeid(*m_PrevAniState) == typeid(T)) return true;


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
};

