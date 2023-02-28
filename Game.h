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
	// �J�b�g�V�[���ɓ����Ă邩�ǂ���
	bool m_Cinematic = false;
	// ���̃J�b�g�V�[������Ă邩
	CutsceneType m_Cutscene;
	// ���Ԃ̃X�e�b�v
	int m_State;

	// �҂��Ă��鎞��
	float m_WaitTime;

	// Minion�����񂾂��ǂ���
	bool m_isMinionDead;

public:
	// �Q�[���V�[���̃A�Z�b�g�����[�h����
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetisMinionDead() { m_isMinionDead = true; }
};

