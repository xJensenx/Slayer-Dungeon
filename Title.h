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
	// ���j���[�̎��
	MenuType m_Menu;
	// ����
	int m_State;
	// �҂��p����
	float m_WaitTime;
	// �I��ł�X�L���X���b�g�ԍ�
	int m_SkillSlotNumber;

public:
	// �^�C�g���V�[���̃A�Z�b�g�����[�h����
	static void Load();

	void Init() override;
	void Uninit() override;
	void Update() override;

	// �Q�[���J�n����
	void LoadStartGame();
	// ���̃X�e�[�g�ɐi��
	void SetNextState(int NextState) { m_State = NextState; }

	// ���݂̃X�e�[�g���擾
	int GetCurState() { return m_State; }
	// ���݂̃��j���[���擾
	MenuType GetMenuType() { return m_Menu; }

	// �X���b�g�ԍ����擾
	int GetSkillSlotNumber() { return m_SkillSlotNumber; }

	// �}�E�X��UI��I��
	void MouseEvent();

	// �}�E�X�ŃX�L����I��
	void MouseSkillEvent();
};

