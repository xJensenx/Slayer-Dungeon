#pragma once
#include "AnimationManager.h"
class TitlePlayerAnimation :
	public AnimationManager
{
public:
	// プレイヤーのステート名前
	enum PlayerState
	{
		Idle01 = 0,
		Idle02,
		Idle03,
		Chosen
	};
private:
	class TitleCharacter* m_Character = NULL;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	void ChangeState(PlayerState NextState)
	{
		m_PreviousState = m_State;	// 前回のステートを更新する
		m_State = NextState;		// 現在のステートを更新する
		m_PrevFrame = m_CurFrame;	// 前のフレーム数を現在のフレーム数に更新する
		m_CurFrame = 0.0f;			// 現在のフレーム数を０にする（最初から始める）
		m_BlendRate = 0.0f;			// ブレンドレートを０にする
		m_PrevLoop = m_CurLoop;		// 前回のループ状態を更新する

		switch (m_State)
		{
		case Idle01:
			m_CurAnimationName = "Idle01";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle02:
				m_AnimModel->LoadAnimation("Idle02", "Idle01");
				break;
			case Idle03:
				m_AnimModel->LoadAnimation("Idle03", "Idle01");
				break;
			}
			break;
		case Idle02:
			m_CurAnimationName = "Idle02";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle01:
				m_AnimModel->LoadAnimation("Idle01", "Idle02");
				break;
			case Idle03:
				m_AnimModel->LoadAnimation("Idle03", "Idle02");
				break;
			}
			break;
		case Idle03:
			m_CurAnimationName = "Idle03";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle02:
				m_AnimModel->LoadAnimation("Idle02", "Idle03");
				break;
			case Idle01:
				m_AnimModel->LoadAnimation("Idle01", "Idle03");
				break;
			}
			break;
		case Chosen:
			m_CurAnimationName = "Chosen";
			m_CurLoop = false;

			switch (m_PreviousState)
			{
			case Idle01:
				m_AnimModel->LoadAnimation("Idle01", "Chosen");
				break;
			case Idle02:
				m_AnimModel->LoadAnimation("Idle02", "Chosen");
				break;
			case Idle03:
				m_AnimModel->LoadAnimation("Idle03", "Chosen");
				break;
			}

			break;
		default:
			break;
		}
	}

	// ボスの変数を入れる
	void SetCharacter(class TitleCharacter* Character)
	{
		m_Character = Character;
	}

};

