#pragma once
#include "Scene.h"
class Game : public Scene
{
public:
	enum CutsceneType
	{
		None = 0,
		FirstCutscene,
		SecondCutscene
	};
private:
	// カットシーンに入ってるかどうか
	bool m_Cinematic = false;
	// 何のカットシーンやってるか
	CutsceneType m_Cutscene;
	// 何番のステップ
	int m_State;

	// 待っている時間
	float m_WaitTime;

	// Minionが死んだかどうか
	bool m_isMinionDead;

public:
	// ゲームシーンのアセットをロードする
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetisMinionDead() { m_isMinionDead = true; }
};

