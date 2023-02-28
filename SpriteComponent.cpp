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

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// Title読み込み
	// PressToContinueテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Title.png",
		NULL,
		NULL,
		&m_Texture["TitleLogo"],
		NULL);
	// PressToContinueテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Continue.png",
		NULL,
		NULL,
		&m_Texture["Continue"],
		NULL);
	// Chooseテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_ChooseBox.png",
		NULL,
		NULL,
		&m_Texture["Choose"],
		NULL);
	// まだ解放されていないものに使うテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_LockBox.png",
		NULL,
		NULL,
		&m_Texture["LockChoose"],
		NULL);
	// StartGameUI_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_StartGame_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["StartGameNS"],
		NULL);
	// StartGameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_StartGame.png",
		NULL,
		NULL,
		&m_Texture["StartGame"],
		NULL);
	// SettingUI_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Settings_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["SettingNS"],
		NULL);
	// SettingUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Settings.png",
		NULL,
		NULL,
		&m_Texture["Setting"],
		NULL);
	// QuitGameUI_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_QuitGame_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["QuitGameNS"],
		NULL);
	// QuitGameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_QuitGame.png",
		NULL,
		NULL,
		&m_Texture["QuitGame"],
		NULL);
	// UIBackgroundテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Background.png",
		NULL,
		NULL,
		&m_Texture["UIBackground"],
		NULL);
	// UIBackButtonテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_BackButton.png",
		NULL,
		NULL,
		&m_Texture["UIBackButton"],
		NULL);
	// UIChooseFileテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_ChooseFile.png",
		NULL,
		NULL,
		&m_Texture["UIChooseFile"],
		NULL);
	// UI_Status_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Status_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIStatusNS"],
		NULL);
	// UI_Statusテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Status.png",
		NULL,
		NULL,
		&m_Texture["UIStatus"],
		NULL);
	// UIStageNSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIStageNS"],
		NULL);
	// UIStageテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage.png",
		NULL,
		NULL,
		&m_Texture["UIStage"],
		NULL);
	// UI_SkillsNSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skills_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkillsNS"],
		NULL);
	// UI_Skillsテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skills.png",
		NULL,
		NULL,
		&m_Texture["UISkills"],
		NULL);
	// UI_ModeSelectテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_ModeSelect.png",
		NULL,
		NULL,
		&m_Texture["UIModeSelect"],
		NULL);
	// UI_StageSelectテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_StageSelect.png",
		NULL,
		NULL,
		&m_Texture["UIStageSelect"],
		NULL);
	// UI_TutorialStageテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_TutorialStage.png",
		NULL,
		NULL,
		&m_Texture["UITutorialStage"],
		NULL);
	// UI_TutorialStage_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_TutorialStage_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UITutorialStageNS"],
		NULL);
	// UI_LockStageテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_LockStage.png",
		NULL,
		NULL,
		&m_Texture["UILockStage"],
		NULL);
	// UI_LockStage_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_LockStage_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UILockStageNS"],
		NULL);
	// Skill01テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill01.png",
		NULL,
		NULL,
		&m_Texture["UISkill01"],
		NULL);
	// Skill01NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill01_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill01NS"],
		NULL);
	// Skill02テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill02.png",
		NULL,
		NULL,
		&m_Texture["UISkill02"],
		NULL);
	// Skill02NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill02_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill02NS"],
		NULL);
	// Skill03テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill03.png",
		NULL,
		NULL,
		&m_Texture["UISkill03"],
		NULL);
	// Skill03NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Skill03_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill03NS"],
		NULL);

	// Skill選択01テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill01.png",
		NULL,
		NULL,
		&m_Texture["UISkill01Custom"],
		NULL);
	// Skill選択01NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill01_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill01CustomNS"],
		NULL);
	// Skill選択02テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill02.png",
		NULL,
		NULL,
		&m_Texture["UISkill02Custom"],
		NULL);
	// Skill選択02NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill02_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill02CustomNS"],
		NULL);
	// Skill選択03テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill03.png",
		NULL,
		NULL,
		&m_Texture["UISkill03Custom"],
		NULL);
	// Skill選択03NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill03_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill03CustomNS"],
		NULL);
	// Skill選択04テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill04.png",
		NULL,
		NULL,
		&m_Texture["UISkill04Custom"],
		NULL);
	// Skill選択04NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill04_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill04CustomNS"],
		NULL);
	// Skill選択05テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill05.png",
		NULL,
		NULL,
		&m_Texture["UISkill05Custom"],
		NULL);
	// Skill選択05NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill05_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill05CustomNS"],
		NULL);
	// Skill選択06テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill06.png",
		NULL,
		NULL,
		&m_Texture["UISkill06Custom"],
		NULL);
	// Skill選択06NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill06_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill06CustomNS"],
		NULL);
	// Skill選択07テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill07.png",
		NULL,
		NULL,
		&m_Texture["UISkill07Custom"],
		NULL);
	// Skill選択07NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill07_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill07CustomNS"],
		NULL);
	// Skill選択08テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill08.png",
		NULL,
		NULL,
		&m_Texture["UISkill08Custom"],
		NULL);
	// Skill選択08NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill08_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill08CustomNS"],
		NULL);
	// Skill選択09テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill09.png",
		NULL,
		NULL,
		&m_Texture["UISkill09Custom"],
		NULL);
	// Skill選択09NSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_Skill09_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UISkill09CustomNS"],
		NULL);
	// UI_SkillChooseテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/PlayerSkill/UI_SkillChoose.png",
		NULL,
		NULL,
		&m_Texture["UISkillChoose"],
		NULL);
	// UI_Stage01テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage01.png",
		NULL,
		NULL,
		&m_Texture["UIStage01"],
		NULL);
	// UI_Stage01テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Stage01_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIStage01NS"],
		NULL);
	// UI_BGMテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_BGM.png",
		NULL,
		NULL,
		&m_Texture["UIBGM"],
		NULL);
	// UI_SEテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_SE.png",
		NULL,
		NULL,
		&m_Texture["UISE"],
		NULL);
	// UI_AdjustButtonテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_AdjustButton.png",
		NULL,
		NULL,
		&m_Texture["UIAdjustButton"],
		NULL);
	// UI_AdjustButton_NotSelectedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/Settings/UI_AdjustButton_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["UIAdjustButtonNS"],
		NULL);
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// Tutorial読み込み用
	// Tutorial_MissionUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_MissionUI.png",
		NULL,
		NULL,
		&m_Texture["MissionUI"],
		NULL);

	// Tutorial_Mission01_NotClearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission01_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission01NC"],
		NULL);

	// Tutorial_Mission01_Clearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission01_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission01"],
		NULL);

	// Tutorial_Mission02_NotClearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission02_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission02NC"],
		NULL);

	// Tutorial_Mission02_Clearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission02_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission02"],
		NULL);

	// Tutorial_Mission03_NotClearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission03_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission03NC"],
		NULL);

	// Tutorial_Mission03_Clearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission03_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission03"],
		NULL);

	// Tutorial_Mission04_NotClearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission04_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission04NC"],
		NULL);

	// Tutorial_Mission04_Clearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission04_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission04"],
		NULL);

	// Tutorial_Mission05_NotClearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission05_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission05NC"],
		NULL);

	// Tutorial_Mission05_Clearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission05_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission05"],
		NULL);

	// Tutorial_Mission06_NotClearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission06_NotCleared.png",
		NULL,
		NULL,
		&m_Texture["Mission06NC"],
		NULL);

	// Tutorial_Mission06_Clearedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission06_Cleared.png",
		NULL,
		NULL,
		&m_Texture["Mission06"],
		NULL);

	// Tutorial_Mission01_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission01_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission01Hint"],
		NULL);

	// Tutorial_Mission02_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission02_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission02Hint"],
		NULL);

	// Tutorial_Mission03_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission03_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission03Hint"],
		NULL);

	// Tutorial_Mission04_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission04_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission04Hint"],
		NULL);

	// Tutorial_Mission05_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission05_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission05Hint"],
		NULL);

	// Tutorial_Mission06_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Mission06_Hint.png",
		NULL,
		NULL,
		&m_Texture["Mission06Hint"],
		NULL);

	// Tutorial_Greeting_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_Greeting_Hint.png",
		NULL,
		NULL,
		&m_Texture["GreetingHint"],
		NULL);

	// Tutorial_TutorialFinish_Hintテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Tutorial/Tutorial_TutorialFinish_Hint.png",
		NULL,
		NULL,
		&m_Texture["TutorialFinish"],
		NULL);

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// UIBackgroundテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/CinematicBorder.png",
		NULL,
		NULL,
		&m_Texture["CinematicBorder"],
		NULL);
	// ローディングロゴテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/LoadingLogo.png",
		NULL,
		NULL,
		&m_Texture["LoadingLogo"],
		NULL);
	// 当たってるエフェクトテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/HitEffect.png",
		NULL,
		NULL,
		&m_Texture["HitEffect"],
		NULL);
	// ターゲットをロックするテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/LockTarget.png",
		NULL,
		NULL,
		&m_Texture["LockTarget"],
		NULL);
	// MinionフルHpのテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/MinionFullHp.png",
		NULL,
		NULL,
		&m_Texture["MinionFullHp"],
		NULL);
	// Minion空のHpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/MinionNoHp.png",
		NULL,
		NULL,
		&m_Texture["MinionNoHp"],
		NULL);
	// Boss空のHpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/BossNoHp.png",
		NULL,
		NULL,
		&m_Texture["BossNoHp"],
		NULL);
	// BossフルのHpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/BossFullHp.png",
		NULL,
		NULL,
		&m_Texture["BossFullHp"],
		NULL);
	// Player空のHpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerNoHp.png",
		NULL,
		NULL,
		&m_Texture["PlayerNoHp"],
		NULL);
	// PlayerフルのHpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerFullHp.png",
		NULL,
		NULL,
		&m_Texture["PlayerFullHp"],
		NULL);
	// Player空のMpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerNoMp.png",
		NULL,
		NULL,
		&m_Texture["PlayerNoMp"],
		NULL);
	// PlayerフルのMpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerFullMp.png",
		NULL,
		NULL,
		&m_Texture["PlayerFullMp"],
		NULL);
	// TutorialPicテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/TutorialPic.png",
		NULL,
		NULL,
		&m_Texture["TutorialPic"],
		NULL);
	// CharacterTutorialPicテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/CharacterTutorialPic.png",
		NULL,
		NULL,
		&m_Texture["CharacterTutorialPic"],
		NULL);
	// MoveOrAttackテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/MoveOrAttack.png",
		NULL,
		NULL,
		&m_Texture["MoveOrAttack"],
		NULL);
	// ToBeContinuedテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/ToBeContinued.png",
		NULL,
		NULL,
		&m_Texture["ToBeContinued"],
		NULL);
	// CommandLogoテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Command.png",
		NULL,
		NULL,
		&m_Texture["CommandLogo"],
		NULL);
	// CommandAttackテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Attack.png",
		NULL,
		NULL,
		&m_Texture["CommandAttack"],
		NULL);
	// CommandAttackChosenテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_AttackChosen.png",
		NULL,
		NULL,
		&m_Texture["CommandAttackChosen"],
		NULL);
	// CommandSkillテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill.png",
		NULL,
		NULL,
		&m_Texture["CommandSkill"],
		NULL);
	// CommandSkillChosenテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_SkillChosen.png",
		NULL,
		NULL,
		&m_Texture["CommandSkillChosen"],
		NULL);
	// CommandUltテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Ult.png",
		NULL,
		NULL,
		&m_Texture["CommandUlt"],
		NULL);
	// CommandUltChosenテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_UltChosen.png",
		NULL,
		NULL,
		&m_Texture["CommandUltChosen"],
		NULL);
	// Particleテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/models/Particle/ParticleTexture.png",
		NULL,
		NULL,
		&m_Texture["Particle"],
		NULL);
	// MouseCursorテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/SystemTexture/MouseCursor.png",
		NULL,
		NULL,
		&m_Texture["MouseCursor"],
		NULL);
	// MouseCursorClickテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/SystemTexture/MouseCursorClick.png",
		NULL,
		NULL,
		&m_Texture["MouseCursorClick"],
		NULL);
	// Player_DmgTakenテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_DmgTaken.png",
		NULL,
		NULL,
		&m_Texture["PlayerDmgTaken"],
		NULL);
	// Player_BlockSuccessテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_BlockSuccess.png",
		NULL,
		NULL,
		&m_Texture["PlayerBlockSuccess"],
		NULL);
	// Player_QTEButtonテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_QTEButton.png",
		NULL,
		NULL,
		&m_Texture["PlayerQTEButton"],
		NULL);
	// AttackHitEffectテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/AttackHitEffect.png",
		NULL,
		NULL,
		&m_Texture["AttackHitEffect"],
		NULL);
	// BlockCounterEffectテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/BlockCounterEffect.png",
		NULL,
		NULL,
		&m_Texture["BlockCounterEffect"],
		NULL);
	// ParticleStarEffectテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/HitStarParticleEffect.png",
		NULL,
		NULL,
		&m_Texture["HitStarParticleEffect"],
		NULL);
	// Numberテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Number.png",
		NULL,
		NULL,
		&m_Texture["Number"],
		NULL);

	// PlayerFullDpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerFullDp.png",
		NULL,
		NULL,
		&m_Texture["PlayerFullDp"],
		NULL);
	// PlayerNoDpテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerNoDp.png",
		NULL,
		NULL,
		&m_Texture["PlayerNoDp"],
		NULL);

	// Player_Skill01GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill01GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill01GameUI"],
		NULL);
	// Player_Skill01GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill01GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill01GameUIEmpty"],
		NULL);
	// Player_Skill02GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill02GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill02GameUI"],
		NULL);
	// Player_Skill02GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill02GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill02GameUIEmpty"],
		NULL);
	// Player_Skill03GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill03GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill03GameUI"],
		NULL);
	// Player_Skill03GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill03GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill03GameUIEmpty"],
		NULL);
	// Player_Skill04GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill04GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill04GameUI"],
		NULL);
	// Player_Skill04GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill04GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill04GameUIEmpty"],
		NULL);
	// Player_Skill05GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill05GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill05GameUI"],
		NULL);
	// Player_Skill05GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill05GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill05GameUIEmpty"],
		NULL);
	// Player_Skill06GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill06GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill06GameUI"],
		NULL);
	// Player_Skill06GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill06GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill06GameUIEmpty"],
		NULL);
	// Player_Skill07GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill07GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill07GameUI"],
		NULL);
	// Player_Skill07GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill07GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill07GameUIEmpty"],
		NULL);
	// Player_Skill08GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill08GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill08GameUI"],
		NULL);
	// Player_Skill08GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill08GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill08GameUIEmpty"],
		NULL);
	// Player_Skill09GameUIテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill09GameUI.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill09GameUI"],
		NULL);
	// Player_Skill09GameUI_Emptyテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_Skill09GameUI_Empty.png",
		NULL,
		NULL,
		&m_Texture["PlayerSkill09GameUIEmpty"],
		NULL);
	// Bossの攻撃警告テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Game/BossAtkWarning.png",
		NULL,
		NULL,
		&m_Texture["BossAtkWarning"],
		NULL);
	// 隕石のエフェクトテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/MeteorHitEffect.png",
		NULL,
		NULL,
		&m_Texture["MeteorHitEffect"],
		NULL);

	// PauseMenuのUI読み込み＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝=
	// PauseMenuBackgroundテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_PauseMenuBackground.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuBackground"],
		NULL);
	// PauseMenuResumeテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Resume.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuResume"],
		NULL);
	// PauseMenuResumeNSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Resume_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuResumeNS"],
		NULL);
	// PauseMenuTitleテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Title.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuTitle"],
		NULL);
	// PauseMenuTitleNSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Title_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuTitleNS"],
		NULL);
	// PauseMenuQuitテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Quit.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuQuit"],
		NULL);
	// PauseMenuQuitNSテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PauseMenu/UI_Quit_NotSelected.png",
		NULL,
		NULL,
		&m_Texture["PauseMenuQuitNS"],
		NULL);

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	// Normalテクスチャロード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	// HpBarNoiseTextureテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/HpBarNoise.jpg",
		NULL,
		NULL,
		&m_NormalTexture["HpBarNoise"],
		NULL);
	// ChosenCommandNoiseテクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Player/Player_CommandChosenNoise.jpg",
		NULL,
		NULL,
		&m_NormalTexture["CommandChosenNoise"],
		NULL);

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	
	// VSシェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader["Unlit"], &m_VertexLayout["Unlit"], "unlitTextureVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Lit"], &m_VertexLayout["Lit"], "vertexLightingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["HpBar"], &m_VertexLayout["HpBar"], "HpBarShaderVS.cso");

	// PSシェーダー読み込み
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
	// 色の設置
	m_Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

}

void SpriteComponent::Uninit()
{
	m_VertexBuffer->Release();
}

void SpriteComponent::Update()
{
	// ノーマルテクスチャ設置
	if (m_NormalName != "None")
	{
		m_NormalUV.x += 0.0035f;
	}
}

void SpriteComponent::Draw()
{
	if (!m_Visible) return;

	// 頂点データ書き換え
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

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout[m_ShaderName]);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader[m_ShaderName], NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader[m_ShaderName], NULL, 0);

	// カメラのビューマトリクス取得
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

	// ビルボード
	if (m_SpriteType == BilBoard)
	{
		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // 逆行列

		// Yが1.0f
		invView._21 = 0.0f;
		invView._22 = 1.0f;
		invView._23 = 0.0f;

		// 木とカメラの位置のベクトルを取って、Yを0にして
		// そのベクトルをNormalizeしたら代入します
		D3DXVECTOR3 VectorOfDist = camera->GetPosition() - m_GameObject->GetPosition();
		D3DXVECTOR3 XVectorOfDist = D3DXVECTOR3(VectorOfDist.x, 0.0f, VectorOfDist.z);
		D3DXVECTOR3 NormalizeDist;
		D3DXVec3Normalize(&NormalizeDist, &XVectorOfDist);
		invView._31 = camera->GetForward().x;
		invView._32 = camera->GetForward().y;
		invView._33 = camera->GetForward().z;

		// ベクトルYとベクトルZの外積を求めたら代入します
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

		// ワールドマトリクス設定
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == AnimationBilBoard)
	{
		// カメラのビューマトリクス取得
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>();
		D3DXMATRIX view = camera->GetViewMatrix();

		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // 逆行列
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ワールドマトリクス設定
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == ProgressBarBilBoard)
	{
		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // 逆行列

		// Yが1.0f
		invView._21 = 0.0f;
		invView._22 = 1.0f;
		invView._23 = 0.0f;

		// 木とカメラの位置のベクトルを取って、Yを0にして
		// そのベクトルをNormalizeしたら代入します
		D3DXVECTOR3 VectorOfDist = camera->GetPosition() - m_GameObject->GetPosition();
		D3DXVECTOR3 XVectorOfDist = D3DXVECTOR3(VectorOfDist.x, 0.0f, VectorOfDist.z);
		D3DXVECTOR3 NormalizeDist;
		D3DXVec3Normalize(&NormalizeDist, &XVectorOfDist);
		invView._31 = camera->GetForward().x;
		invView._32 = camera->GetForward().y;
		invView._33 = camera->GetForward().z;

		// ベクトルYとベクトルZの外積を求めたら代入します
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

		// ワールドマトリクス設定
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == WarningBilBoard)
	{
		// ワールドマトリクス設定
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//// マテリアル設定
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[m_Name]);

	// ノーマルテクスチャ設置
	if (m_NormalName != "None")
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_NormalTexture[m_NormalName]);
	}

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::SetParameter(m_NormalUV);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::LoadInfo(std::string Name, std::string Shader, D3DXVECTOR2 UV)
{
	// テクスチャ座標やUVの設置
	m_TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	m_UV = UV;

	// テクスチャやシェーダーの名前の設置
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
	// 頂点バッファ生成
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
