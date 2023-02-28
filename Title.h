#pragma once
#include "Scene.h"
class Title : public Scene
{
public:
	enum MenuType
	{
		TitleMenu = 0,
		MainMenu,
		ModeSelect,
		StageSelect,
		SkillCustom,
		Settings
	};
private:
	// メニューの種類
	MenuType m_Menu;
	// 順番
	int m_State;
	// 待ち用時間
	float m_WaitTime;
	// 選んでるスキルスロット番号
	int m_SkillSlotNumber;

public:
	// タイトルシーンのアセットをロードする
	static void Load();

	void Init() override;
	void Uninit() override;
	void Update() override;

	// ゲーム開始する
	void LoadStartGame();
	// 次のステートに進む
	void SetNextState(int NextState) { m_State = NextState; }

	// 現在のステートを取得
	int GetCurState() { return m_State; }
	// 現在のメニューを取得
	MenuType GetMenuType() { return m_Menu; }

	// スロット番号を取得
	int GetSkillSlotNumber() { return m_SkillSlotNumber; }

	// マウスでUIを選ぶ
	void MouseEvent();

	// マウスでスキルを選ぶ
	void MouseSkillEvent();
};

