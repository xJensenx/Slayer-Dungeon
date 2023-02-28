#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "Camera.h"
#include "SpriteComponent.h"

std::unordered_map<std::string, ID3D11ShaderResourceView*>	SpriteComponent::m_Texture;
std::unordered_map<std::string, ID3D11ShaderResourceView*>	SpriteComponent::m_NormalTexture;

std::unordered_map<std::string, ID3D11VertexShader*>		SpriteComponent::m_VertexShader;
std::unordered_map<std::string, ID3D11PixelShader*>			SpriteComponent::m_PixelShader;
std::unordered_map<std::string, ID3D11InputLayout*>			SpriteComponent::m_VertexLayout;

void SpriteComponent::Load()
{
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/field001.jpg",
		NULL,
		NULL,
		&m_Texture["Field"],
		NULL);

	// ������������������������������������������������������������������������������������
	// Title�ǂݍ���
	// PressToContinue�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Title.png",
		NULL,
		NULL,
		&m_Texture["TitleLogo"],
		NULL);
	// PressToContinue�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Continue.png",
		NULL,
		NULL,
		&m_Texture["Continue"],
		NULL);
	// Choose�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_ChooseBox.png",
		NULL,
		NULL,
		&m_Texture["Choose"],
		NULL);
	// �܂��������Ă��Ȃ����̂Ɏg���e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_LockBox.png",
		NULL,
		NULL,
		&m_Texture["LockChoose"],
		NULL);
	// StartGameUI_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_StartGame_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["StartGameNS"],
		NULL);
	// StartGameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_StartGame.png",
		NULL,
		NULL,
		&m_Texture["StartGame"],
		NULL);
	// SettingUI_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Settings_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["SettingNS"],
		NULL);
	// SettingUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Settings.png",
		NULL,
		NULL,
		&m_Texture["Setting"],
		NULL);
	// QuitGameUI_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_QuitGame_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["QuitGameNS"],
		NULL);
	// QuitGameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_QuitGame.png",
		NULL,
		NULL,
		&m_Texture["QuitGame"],
		NULL);
	// UIBackground�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Background.png",
		NULL,
		NULL,
		&m_Texture["UIBackground"],
		NULL);
	// UIBackButton�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_BackButton.png",
		NULL,
		NULL,
		&m_Texture["UIBackButton"],
		NULL);
	// UIChooseFile�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_ChooseFile.png",
		NULL,
		NULL,
		&m_Texture["UIChooseFile"],
		NULL);
	// UI_Status_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Status_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIStatusNS"],
		NULL);
	// UI_Status�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Status.png",
		NULL,
		NULL,
		&m_Texture["UIStatus"],
		NULL);
	// UIStageNS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIStageNS"],
		NULL);
	// UIStage�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage.png",
		NULL,
		NULL,
		&m_Texture["UIStage"],
		NULL);
	// UI_SkillsNS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skills_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkillsNS"],
		NULL);
	// UI_Skills�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skills.png",
		NULL,
		NULL,
		&m_Texture["UISkills"],
		NULL);
	// UI_ModeSelect�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_ModeSelect.png",
		NULL,
		NULL,
		&m_Texture["UIModeSelect"],
		NULL);
	// UI_StageSelect�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_StageSelect.png",
		NULL,
		NULL,
		&m_Texture["UIStageSelect"],
		NULL);
	// UI_TutorialStage�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_TutorialStage.png",
		NULL,
		NULL,
		&m_Texture["UITutorialStage"],
		NULL);
	// UI_TutorialStage_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_TutorialStage_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UITutorialStageNS"],
		NULL);
	// UI_LockStage�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_LockStage.png",
		NULL,
		NULL,
		&m_Texture["UILockStage"],
		NULL);
	// UI_LockStage_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_LockStage_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UILockStageNS"],
		NULL);
	// Skill01�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill01.png",
		NULL,
		NULL,
		&m_Texture["UISkill01"],
		NULL);
	// Skill01NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill01_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill01NS"],
		NULL);
	// Skill02�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill02.png",
		NULL,
		NULL,
		&m_Texture["UISkill02"],
		NULL);
	// Skill02NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill02_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill02NS"],
		NULL);
	// Skill03�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill03.png",
		NULL,
		NULL,
		&m_Texture["UISkill03"],
		NULL);
	// Skill03NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill03_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill03NS"],
		NULL);

	// Skill�I��01�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill01.png",
		NULL,
		NULL,
		&m_Texture["UISkill01Custom"],
		NULL);
	// Skill�I��01NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill01_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill01CustomNS"],
		NULL);
	// Skill�I��02�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill02.png",
		NULL,
		NULL,
		&m_Texture["UISkill02Custom"],
		NULL);
	// Skill�I��02NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill02_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill02CustomNS"],
		NULL);
	// Skill�I��03�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill03.png",
		NULL,
		NULL,
		&m_Texture["UISkill03Custom"],
		NULL);
	// Skill�I��03NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill03_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill03CustomNS"],
		NULL);
	// Skill�I��04�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill04.png",
		NULL,
		NULL,
		&m_Texture["UISkill04Custom"],
		NULL);
	// Skill�I��04NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill04_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill04CustomNS"],
		NULL);
	// Skill�I��05�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill05.png",
		NULL,
		NULL,
		&m_Texture["UISkill05Custom"],
		NULL);
	// Skill�I��05NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill05_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill05CustomNS"],
		NULL);
	// Skill�I��06�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill06.png",
		NULL,
		NULL,
		&m_Texture["UISkill06Custom"],
		NULL);
	// Skill�I��06NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill06_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill06CustomNS"],
		NULL);
	// Skill�I��07�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill07.png",
		NULL,
		NULL,
		&m_Texture["UISkill07Custom"],
		NULL);
	// Skill�I��07NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill07_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill07CustomNS"],
		NULL);
	// Skill�I��08�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill08.png",
		NULL,
		NULL,
		&m_Texture["UISkill08Custom"],
		NULL);
	// Skill�I��08NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill08_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill08CustomNS"],
		NULL);
	// Skill�I��09�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill09.png",
		NULL,
		NULL,
		&m_Texture["UISkill09Custom"],
		NULL);
	// Skill�I��09NS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill09_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill09CustomNS"],
		NULL);
	// UI_SkillChoose�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_SkillChoose.png",
		NULL,
		NULL,
		&m_Texture["UISkillChoose"],
		NULL);
	// UI_Stage01�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage01.png",
		NULL,
		NULL,
		&m_Texture["UIStage01"],
		NULL);
	// UI_Stage01�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage01_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIStage01NS"],
		NULL);
	// UI_BGM�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_BGM.png",
		NULL,
		NULL,
		&m_Texture["UIBGM"],
		NULL);
	// UI_SE�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_SE.png",
		NULL,
		NULL,
		&m_Texture["UISE"],
		NULL);
	// UI_AdjustButton�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_AdjustButton.png",
		NULL,
		NULL,
		&m_Texture["UIAdjustButton"],
		NULL);
	// UI_AdjustButton_NotSelected�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_AdjustButton_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIAdjustButtonNS"],
		NULL);
	// ������������������������������������������������������������������������������������
	// 
	// ������������������������������������������������������������������������������������
	// Tutorial�ǂݍ��ݗp
	// Tutorial_MissionUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_MissionUI.png",
		NULL,
		NULL,
		&m_Texture["MissionUI"],
		NULL);

	// Tutorial_Mission01_NotCleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission01_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission01NC"],
		NULL);

	// Tutorial_Mission01_Cleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission01_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission01"],
		NULL);

	// Tutorial_Mission02_NotCleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission02_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission02NC"],
		NULL);

	// Tutorial_Mission02_Cleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission02_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission02"],
		NULL);

	// Tutorial_Mission03_NotCleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission03_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission03NC"],
		NULL);

	// Tutorial_Mission03_Cleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission03_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission03"],
		NULL);

	// Tutorial_Mission04_NotCleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission04_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission04NC"],
		NULL);

	// Tutorial_Mission04_Cleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission04_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission04"],
		NULL);

	// Tutorial_Mission05_NotCleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission05_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission05NC"],
		NULL);

	// Tutorial_Mission05_Cleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission05_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission05"],
		NULL);

	// Tutorial_Mission06_NotCleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission06_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission06NC"],
		NULL);

	// Tutorial_Mission06_Cleared�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission06_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission06"],
		NULL);

	// Tutorial_Mission01_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission01_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission01Hint"],
		NULL);

	// Tutorial_Mission02_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission02_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission02Hint"],
		NULL);

	// Tutorial_Mission03_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission03_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission03Hint"],
		NULL);

	// Tutorial_Mission04_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission04_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission04Hint"],
		NULL);

	// Tutorial_Mission05_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission05_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission05Hint"],
		NULL);

	// Tutorial_Mission06_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission06_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission06Hint"],
		NULL);

	// Tutorial_Greeting_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Greeting_Hint.png",
		NULL,
		NULL,
		&m_Texture["GreetingHint"],
		NULL);

	// Tutorial_TutorialFinish_Hint�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_TutorialFinish_Hint.png",
		NULL,
		NULL,
		&m_Texture["TutorialFinish"],
		NULL);

	// ������������������������������������������������������������������������������������
	// UIBackground�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/CinematicBorder.png",
		NULL,
		NULL,
		&m_Texture["CinematicBorder"],
		NULL);
	// ���[�f�B���O���S�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/LoadingLogo.png",
		NULL,
		NULL,
		&m_Texture["LoadingLogo"],
		NULL);
	// �������Ă�G�t�F�N�g�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/HitEffect.png",
		NULL,
		NULL,
		&m_Texture["HitEffect"],
		NULL);
	// �^�[�Q�b�g�����b�N����e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/LockTarget.png",
		NULL,
		NULL,
		&m_Texture["LockTarget"],
		NULL);
	// Minion�t��Hp�̃e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/MinionFullHp.png",
		NULL,
		NULL,
		&m_Texture["MinionFullHp"],
		NULL);
	// Minion���Hp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/MinionNoHp.png",
		NULL,
		NULL,
		&m_Texture["MinionNoHp"],
		NULL);
	// Boss���Hp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/BossNoHp.png",
		NULL,
		NULL,
		&m_Texture["BossNoHp"],
		NULL);
	// Boss�t����Hp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/BossFullHp.png",
		NULL,
		NULL,
		&m_Texture["BossFullHp"],
		NULL);
	// Player���Hp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerNoHp.png",
		NULL,
		NULL,
		&m_Texture["PlayerNoHp"],
		NULL);
	// Player�t����Hp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerFullHp.png",
		NULL,
		NULL,
		&m_Texture["PlayerFullHp"],
		NULL);
	// Player���Mp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerNoMp.png",
		NULL,
		NULL,
		&m_Texture["PlayerNoMp"],
		NULL);
	// Player�t����Mp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerFullMp.png",
		NULL,
		NULL,
		&m_Texture["PlayerFullMp"],
		NULL);
	// TutorialPic�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/TutorialPic.png",
		NULL,
		NULL,
		&m_Texture["TutorialPic"],
		NULL);
	// CharacterTutorialPic�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/CharacterTutorialPic.png",
		NULL,
		NULL,
		&m_Texture["CharacterTutorialPic"],
		NULL);
	// MoveOrAttack�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/MoveOrAttack.png",
		NULL,
		NULL,
		&m_Texture["MoveOrAttack"],
		NULL);
	// ToBeContinued�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/ToBeContinued.png",
		NULL,
		NULL,
		&m_Texture["ToBeContinued"],
		NULL);
	// CommandLogo�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Command.png",
		NULL,
		NULL,
		&m_Texture["CommandLogo"],
		NULL);
	// CommandAttack�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Attack.png",
		NULL,
		NULL,
		&m_Texture["CommandAttack"],
		NULL);
	// CommandAttackChosen�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_AttackChosen.png",
		NULL,
		NULL,
		&m_Texture["CommandAttackChosen"],
		NULL);
	// CommandSkill�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill.png",
		NULL,
		NULL,
		&m_Texture["CommandSkill"],
		NULL);
	// CommandSkillChosen�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_SkillChosen.png",
		NULL,
		NULL,
		&m_Texture["CommandSkillChosen"],
		NULL);
	// CommandUlt�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Ult.png",
		NULL,
		NULL,
		&m_Texture["CommandUlt"],
		NULL);
	// CommandUltChosen�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_UltChosen.png",
		NULL,
		NULL,
		&m_Texture["CommandUltChosen"],
		NULL);
	// Particle�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/models/Particle/ParticleTexture.png",
		NULL,
		NULL,
		&m_Texture["Particle"],
		NULL);
	// MouseCursor�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/SystemTexture/MouseCursor.png",
		NULL,
		NULL,
		&m_Texture["MouseCursor"],
		NULL);
	// MouseCursorClick�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/SystemTexture/MouseCursorClick.png",
		NULL,
		NULL,
		&m_Texture["MouseCursorClick"],
		NULL);
	// Player_DmgTaken�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_DmgTaken.png",
		NULL,
		NULL,
		&m_Texture["PlayerDmgTaken"],
		NULL);
	// Player_BlockSuccess�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_BlockSuccess.png",
		NULL,
		NULL,
		&m_Texture["PlayerBlockSuccess"],
		NULL);
	// Player_QTEButton�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_QTEButton.png",
		NULL,
		NULL,
		&m_Texture["PlayerQTEButton"],
		NULL);
	// AttackHitEffect�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/AttackHitEffect.png",
		NULL,
		NULL,
		&m_Texture["AttackHitEffect"],
		NULL);
	// BlockCounterEffect�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/BlockCounterEffect.png",
		NULL,
		NULL,
		&m_Texture["BlockCounterEffect"],
		NULL);
	// ParticleStarEffect�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/HitStarParticleEffect.png",
		NULL,
		NULL,
		&m_Texture["HitStarParticleEffect"],
		NULL);
	// Number�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Number.png",
		NULL,
		NULL,
		&m_Texture["Number"],
		NULL);

	// PlayerFullDp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerFullDp.png",
		NULL,
		NULL,
		&m_Texture["PlayerFullDp"],
		NULL);
	// PlayerNoDp�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerNoDp.png",
		NULL,
		NULL,
		&m_Texture["PlayerNoDp"],
		NULL);

	// Player_Skill01GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill01GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill01GameUI"],
		NULL);
	// Player_Skill01GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill01GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill01GameUIEmpty"],
		NULL);
	// Player_Skill02GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill02GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill02GameUI"],
		NULL);
	// Player_Skill02GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill02GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill02GameUIEmpty"],
		NULL);
	// Player_Skill03GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill03GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill03GameUI"],
		NULL);
	// Player_Skill03GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill03GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill03GameUIEmpty"],
		NULL);
	// Player_Skill04GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill04GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill04GameUI"],
		NULL);
	// Player_Skill04GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill04GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill04GameUIEmpty"],
		NULL);
	// Player_Skill05GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill05GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill05GameUI"],
		NULL);
	// Player_Skill05GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill05GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill05GameUIEmpty"],
		NULL);
	// Player_Skill06GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill06GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill06GameUI"],
		NULL);
	// Player_Skill06GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill06GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill06GameUIEmpty"],
		NULL);
	// Player_Skill07GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill07GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill07GameUI"],
		NULL);
	// Player_Skill07GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill07GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill07GameUIEmpty"],
		NULL);
	// Player_Skill08GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill08GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill08GameUI"],
		NULL);
	// Player_Skill08GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill08GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill08GameUIEmpty"],
		NULL);
	// Player_Skill09GameUI�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill09GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill09GameUI"],
		NULL);
	// Player_Skill09GameUI_Empty�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill09GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill09GameUIEmpty"],
		NULL);
	// Boss�̍U���x���e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/BossAtkWarning.png",
		NULL,
		NULL,
		&m_Texture["BossAtkWarning"],
		NULL);
	// 覐΂̃G�t�F�N�g�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/MeteorHitEffect.png",
		NULL,
		NULL,
		&m_Texture["MeteorHitEffect"],
		NULL);

	// PauseMenu��UI�ǂݍ��݁�������������������������������������������������������������=
	// PauseMenuBackground�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_PauseMenuBackground.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuBackground"],
		NULL);
	// PauseMenuResume�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Resume.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuResume"],
		NULL);
	// PauseMenuResumeNS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Resume_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuResumeNS"],
		NULL);
	// PauseMenuTitle�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Title.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuTitle"],
		NULL);
	// PauseMenuTitleNS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Title_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuTitleNS"],
		NULL);
	// PauseMenuQuit�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Quit.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuQuit"],
		NULL);
	// PauseMenuQuitNS�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Quit_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuQuitNS"],
		NULL);

	// ������������������������������������������������������������������������������������

	// Normal�e�N�X�`�����[�h��������������������������������������������������������������

	// HpBarNoiseTexture�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/HpBarNoise.jpg",
		NULL,
		NULL,
		&m_NormalTexture["HpBarNoise"],
		NULL);
	// ChosenCommandNoise�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_CommandChosenNoise.jpg",
		NULL,
		NULL,
		&m_NormalTexture["CommandChosenNoise"],
		NULL);

	// ������������������������������������������������������������������������������������
	
	// VS�V�F�[�_�[�ǂݍ���
	Renderer::CreateVertexShader(&m_VertexShader["Unlit"], &m_VertexLayout["Unlit"], "unlitTextureVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Lit"], &m_VertexLayout["Lit"], "vertexLightingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["HpBar"], &m_VertexLayout["HpBar"], "HpBarShaderVS.cso");

	// PS�V�F�[�_�[�ǂݍ���
	Renderer::CreatePixelShader(&m_PixelShader["Unlit"], "unlitTexturePS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Lit"], "vertexLightingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["HpBar"], "HpBarShaderPS.cso");

}

void SpriteComponent::Unload()
{
	for (auto T : m_Texture)
	{
		T.second->Release();
		delete T.second;
	}
	m_Texture.clear();

	for (auto VS : m_VertexShader)
	{
		VS.second->Release();
		delete VS.second;
	}
	m_VertexShader.clear();
	
	for (auto VL : m_VertexLayout)
	{
		VL.second->Release();
		delete VL.second;
	}
	m_VertexLayout.clear();

	for (auto PS : m_PixelShader)
	{
		PS.second->Release();
		delete PS.second;
	}
	m_PixelShader.clear();

}

void SpriteComponent::Init()
{
	m_SpriteType = None;
	m_Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_NormalUV = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	m_NormalName = "None";
	// �F�̐ݒu
	m_Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

}

void SpriteComponent::Uninit()
{
	m_VertexBuffer->Release();
}

void SpriteComponent::Update()
{
	// �m�[�}���e�N�X�`���ݒu
	if (m_NormalName != "None")
	{
		m_NormalUV.x += 0.0035f;
	}
}

void SpriteComponent::Draw()
{
	if (!m_Visible) return;

	// ���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	D3DXVECTOR3 Pos = m_GameObject->GetPosition() + m_Offset;
	D3DXVECTOR3 Size = m_GameObject->GetSize() + m_SizeOffset;

	switch (m_SpriteType)
	{
	case None:
		vertex[0].Position = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	case ProgressBarBilBoard:
		vertex[0].Position = D3DXVECTOR3(0.0f, Size.y / 2, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Size.x, Size.y / 2, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(0.0f, -Size.y / 2, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Size.x, -Size.y / 2, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	case ProgressBar:
		vertex[0].Position = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Pos.x + Size.x, Pos.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(Pos.x, Pos.y + Size.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Pos.x + Size.x, Pos.y + Size.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	case WarningBilBoard:
		vertex[0].Position = D3DXVECTOR3(-Size.x / 2, 0.0f, Size.z / 2);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Size.x / 2, 0.0f, Size.z / 2);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(-Size.x / 2, 0.0f, -Size.z / 2);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Size.x / 2, 0.0f, -Size.z / 2);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	default:
		vertex[0].Position = D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	}

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout[m_ShaderName]);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader[m_ShaderName], NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader[m_ShaderName], NULL, 0);

	// �J�����̃r���[�}�g���N�X�擾
	Scene* scene = Manager::GetScene();
	if (scene == NULL) return;

	Camera* camera = scene->GetGameObject<Camera>();
	D3DXMATRIX view;
	if (camera != NULL)
	{
		view = camera->GetViewMatrix();
	}
	D3DXVECTOR3 _GameObjectSca = m_GameObject->GetScale();
	D3DXVECTOR3 _GameObjectPos = m_GameObject->GetPosition();
	D3DXVECTOR3 _GameObjectRot = m_GameObject->GetRotation();

	// �r���{�[�h
	if (m_SpriteType == BilBoard)
	{
		// �r���[�̋t�s��
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // �t�s��

		// Y��1.0f
		invView._21 = 0.0f;
		invView._22 = 1.0f;
		invView._23 = 0.0f;

		// �؂ƃJ�����̈ʒu�̃x�N�g��������āAY��0�ɂ���
		// ���̃x�N�g����Normalize�����������܂�
		D3DXVECTOR3 VectorOfDist = camera->GetPosition() - m_GameObject->GetPosition();
		D3DXVECTOR3 XVectorOfDist = D3DXVECTOR3(VectorOfDist.x, 0.0f, VectorOfDist.z);
		D3DXVECTOR3 NormalizeDist;
		D3DXVec3Normalize(&NormalizeDist, &XVectorOfDist);
		invView._31 = camera->GetForward().x;
		invView._32 = camera->GetForward().y;
		invView._33 = camera->GetForward().z;

		// �x�N�g��Y�ƃx�N�g��Z�̊O�ς����߂��������܂�
		D3DXVECTOR3 CrossDist;
		D3DXVECTOR3 VectorY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVECTOR3 VectorZ = camera->GetForward();

		D3DXVec3Cross(&CrossDist, &VectorY, &VectorZ);
		invView._11 = CrossDist.x;
		invView._12 = CrossDist.y;
		invView._13 = CrossDist.z;

		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ���[���h�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == AnimationBilBoard)
	{
		// �J�����̃r���[�}�g���N�X�擾
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>();
		D3DXMATRIX view = camera->GetViewMatrix();

		// �r���[�̋t�s��
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // �t�s��
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ���[���h�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == ProgressBarBilBoard)
	{
		// �r���[�̋t�s��
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // �t�s��

		// Y��1.0f
		invView._21 = 0.0f;
		invView._22 = 1.0f;
		invView._23 = 0.0f;

		// �؂ƃJ�����̈ʒu�̃x�N�g��������āAY��0�ɂ���
		// ���̃x�N�g����Normalize�����������܂�
		D3DXVECTOR3 VectorOfDist = camera->GetPosition() - m_GameObject->GetPosition();
		D3DXVECTOR3 XVectorOfDist = D3DXVECTOR3(VectorOfDist.x, 0.0f, VectorOfDist.z);
		D3DXVECTOR3 NormalizeDist;
		D3DXVec3Normalize(&NormalizeDist, &XVectorOfDist);
		invView._31 = camera->GetForward().x;
		invView._32 = camera->GetForward().y;
		invView._33 = camera->GetForward().z;

		// �x�N�g��Y�ƃx�N�g��Z�̊O�ς����߂��������܂�
		D3DXVECTOR3 CrossDist;
		D3DXVECTOR3 VectorY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVECTOR3 VectorZ = camera->GetForward();

		D3DXVec3Cross(&CrossDist, &VectorY, &VectorZ);
		invView._11 = CrossDist.x;
		invView._12 = CrossDist.y;
		invView._13 = CrossDist.z;

		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ���[���h�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == WarningBilBoard)
	{
		// ���[���h�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixRotationYawPitchRoll(&rot, _GameObjectRot.y, _GameObjectRot.x, _GameObjectRot.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else
	{
		Renderer::SetWorldViewProjection2D();
	}

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//// �}�e���A���ݒ�
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[m_Name]);

	// �m�[�}���e�N�X�`���ݒu
	if (m_NormalName != "None")
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_NormalTexture[m_NormalName]);
	}

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::SetParameter(m_NormalUV);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::LoadInfo(std::string Name, std::string Shader, D3DXVECTOR2 UV)
{
	// �e�N�X�`�����W��UV�̐ݒu
	m_TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	m_UV = UV;

	// �e�N�X�`����V�F�[�_�[�̖��O�̐ݒu
	m_Name = Name;
	m_ShaderName = Shader;

	VERTEX_3D vertex[4];

	D3DXVECTOR3 Pos = m_GameObject->GetPosition();
	D3DXVECTOR3 Size = m_GameObject->GetSize();

	switch (m_SpriteType)
	{
	case None:
		vertex[0].Position = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	case ProgressBarBilBoard:
		vertex[0].Position = D3DXVECTOR3(0.0f, Size.y / 2, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Size.x, Size.y / 2, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(0.0f, -Size.y / 2, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Size.x, -Size.y / 2, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	case ProgressBar:
		vertex[0].Position = D3DXVECTOR3(Pos.x, Size.y / 2, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Pos.x + Size.x, Size.y / 2, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(Pos.x, -Size.y / 2, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Pos.x + Size.x, -Size.y / 2, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	case WarningBilBoard:
		vertex[0].Position = D3DXVECTOR3(-Size.x / 2, 0.0f, Size.z / 2);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Size.x / 2, 0.0f, Size.z / 2);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(-Size.x / 2, 0.0f, -Size.z / 2);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Size.x / 2, 0.0f, -Size.z / 2);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	default:
		vertex[0].Position = D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);

		vertex[1].Position = D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_TexCoord.y);

		vertex[2].Position = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_UV.y + m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(m_UV.x + m_TexCoord.x, m_UV.y + m_TexCoord.y);
		break;
	}

	D3D11_BUFFER_DESC bd{};
	// ���_�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	assert(m_Texture[m_Name]);
}

void SpriteComponent::SetNormalTexture(std::string NormalName)
{
	m_NormalName = NormalName;
}
