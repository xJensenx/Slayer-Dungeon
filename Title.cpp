#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "AudioManager.h"
#include "ComponentInclude.h"
#include "Fade.h"
#include "input.h"
#include "Game.h"

#include "TitleLogo.h"
#include "Camera.h"
#include "Sky.h"
#include "Sea.h"
#include "PressContinue.h"
#include "TitleIsland.h"
#include "TitleUI.h"
#include "TitleSkillUI.h"
#include "TitleUIBackground.h"
#include "PhysicsCast.h"
#include "TitleEvent.h"
#include "TitleCharacter.h"

#include "Title.h"
#include "MouseCursor.h"
#include "TitleSkillUIType.h"
#include "TitleSkillUIEvent.h"
#include "LoadingScene.h"
#include "SwordTrail.h"
#include "SettingUI.h"
#include "SettingAdjustButton.h"

// カメラ
Camera* WorldCam;
// カメラの初期座標
D3DXVECTOR3 InitPos;
// カメラの現在座標
D3DXVECTOR3 CurPos;
// カメラの目標座標
D3DXVECTOR3 TargetPos = D3DXVECTOR3(18.0f, 4.0f, 0.0f);

// カメラの初期ターゲット座標
D3DXVECTOR3 InitTarget;
// カメラの現在ターゲット座標
D3DXVECTOR3 CurTarget;
// カメラの目標ターゲット座標
D3DXVECTOR3 NextTarget = D3DXVECTOR3(18.0f, 1.0f, 5.0f);

// ボタン
TitleUI* g_StartButton;
TitleUI* g_SettingButton;
TitleUI* g_QuitButton;
TitleUI* g_BackButton;
TitleUI* g_ModeSelectUI;
TitleUI* g_StageSelectUI;
TitleUI* g_StageButton;
TitleUI* g_SkillButton;
TitleUI* g_TutorialStageButton;
TitleUI* g_Stage2Button;
TitleUI* g_Skill01Button;
TitleUI* g_Skill02Button;
TitleUI* g_Skill03Button;
TitleSkillUI* g_Skill01CustomButton;
TitleSkillUI* g_Skill02CustomButton;
TitleSkillUI* g_Skill03CustomButton;
TitleSkillUI* g_Skill04CustomButton;
TitleSkillUI* g_Skill05CustomButton;
TitleSkillUI* g_Skill06CustomButton;
TitleSkillUI* g_Skill07CustomButton;
TitleSkillUI* g_Skill08CustomButton;
TitleSkillUI* g_Skill09CustomButton;
TitleSkillUIEvent* g_SkillEvent;
SettingUI* g_BGMButton;
SettingUI* g_SEButton;

void Title::Load()
{
	ModelRenderer::Load();
	AnimModelManager::Load();
	SwordTrail::Load();
	LoadingScene::SetLoadFinish(true);
}

void Title::Init()
{
	// グローバル変数の初期化
	InitTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CurTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CurPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//AudioManager::Play("TitleBGM", true);
	AddGameObject<TitleLogo>(Layer_UILayer);
	AddGameObject<PressContinue>(Layer_UILayer);

	WorldCam = AddGameObject<Camera>(Layer_CameraLayer);
	WorldCam->SetTarget(D3DXVECTOR3(0.0f, 1.5f, 0.0f));
	Sky* WorldSky = AddGameObject<Sky>(Layer_ObjectLayer);
	WorldSky->SetPosition(D3DXVECTOR3(0.0f, -4.0f, 0.0f));
	WorldSky->SetScale(D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	AddGameObject<Sea>(Layer_ObjectLayer);

	AddGameObject<TitleIsland>(Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(21.0f, 1.3f, 3.0f), D3DXVECTOR3(0.0f, D3DX_PI * 3, 0.0f));

	m_State = 1;
	m_WaitTime = 0.0f;
	m_Menu = TitleMenu;




	Renderer::SetLightPosition(D3DXVECTOR4(20.0f, 5.0f, 0.0f, 0.0f));
	Renderer::SetLightDirection(D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f));

	Input::SetLockPosition(false);
	MouseCursor::SetVisibility(true);

	AudioManager::PlayBGM("BGMTitleSea", true);
}

void Title::Uninit()
{
	AudioManager::StopBGM("BGMTitleSea");

	Scene::Uninit();
}

void Title::Update()
{
	PressContinue* _PC = GetGameObject<PressContinue>();

	switch (m_Menu)
	{
	case TitleMenu:
		switch (m_State)
		{
		case 1:
			m_WaitTime++;
			if (m_WaitTime > 2.0f * Manager::Time)
			{
				m_State = 2;
				m_WaitTime = 0.0f;
			}
			break;
		case 2:
			if (Input::GetKeyTrigger(VK_LBUTTON))
			{
				GetGameObject<TitleLogo>()->SetTitleEffect(false);
				InitPos = WorldCam->GetPosition();
				InitTarget = WorldCam->GetTargetPos();
				_PC->Disappear();
				// 選ぶキャラクターを追加する
				AddGameObject<TitleCharacter>(Layer_ObjectLayer)->SetPosition(D3DXVECTOR3(19.5f, 1.0f, 3.5f));
				m_State = 3;

				// SEを鳴らす
				AudioManager::PlaySE("SEClick");
			}
			break;
		case 3:
			m_WaitTime++;
			if (m_WaitTime > 3.0f * Manager::Time)
			{
				// UI用背景を追加する
				AddGameObject<TitleUIBackground>(Scene::Layer_UILayer)->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f));

				AddGameObject<TitleEvent>(Layer_UILayer)->SetPosition(D3DXVECTOR3(-700.0f, 150.0f, 0.0f));

				// 第一スロット
				// スタートボタン
				g_StartButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_StartButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_StartButton->LoadInfo(TitleUI::StartGame);
				g_StartButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));

				// ステージボタン
				g_StageButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_StageButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_StageButton->LoadInfo(TitleUI::StageButton);
				g_StageButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));

				// チュートリアルステージボタン
				g_TutorialStageButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_TutorialStageButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_TutorialStageButton->LoadInfo(TitleUI::TutorialStage);
				g_TutorialStageButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));

				// スキルスロット１
				g_Skill01Button = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_Skill01Button->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill01Button->LoadInfo(TitleUI::Skill01);
				g_Skill01Button->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));

				// BGMUIボタン
				g_BGMButton = AddGameObject<SettingUI>(Scene::Layer_UILayer);
				g_BGMButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_BGMButton->SetUIType<SettingUI_Type_BGM>();
				g_BGMButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));

				// 第二スロット
				// 設定ボタン
				g_SettingButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_SettingButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));
				g_SettingButton->LoadInfo(TitleUI::Setting);
				g_SettingButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));

				// スキルボタン
				g_SkillButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_SkillButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));
				g_SkillButton->LoadInfo(TitleUI::SkillButton);
				g_SkillButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));

				// ステージ１ボタン
				g_Stage2Button = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_Stage2Button->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));
				g_Stage2Button->LoadInfo(TitleUI::Stage01);
				g_Stage2Button->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));

				// スキルスロット２
				g_Skill02Button = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_Skill02Button->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));
				g_Skill02Button->LoadInfo(TitleUI::Skill02);
				g_Skill02Button->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));

				// SE設置ボタン
				g_SEButton = AddGameObject<SettingUI>(Scene::Layer_UILayer);
				g_SEButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));
				g_SEButton->SetUIType<SettingUI_Type_SE>();
				g_SEButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2, 0.0f));

				// 第三スロット
				// 退出ボタン
				g_QuitButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_QuitButton->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));
				g_QuitButton->LoadInfo(TitleUI::QuitGame);
				g_QuitButton->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));


				// スキルスロット３			
				g_Skill03Button = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_Skill03Button->SetPosition(D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));
				g_Skill03Button->LoadInfo(TitleUI::Skill03);
				g_Skill03Button->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(-SCREEN_WIDTH / 4 + 50.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));


				// 戻るボタン
				g_BackButton = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_BackButton->SetPosition(D3DXVECTOR3(100.0f, SCREEN_HEIGHT + 50.0f, 0.0f));
				g_BackButton->LoadInfo(TitleUI::BackButton);
				g_BackButton->SetAppearPos(D3DXVECTOR3(100.0f, SCREEN_HEIGHT - 75.0f, 0.0f), D3DXVECTOR3(100.0f, SCREEN_HEIGHT + 50.0f, 0.0f));

				// モード選択
				g_ModeSelectUI = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_ModeSelectUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, -200.0f, 0.0f));
				g_ModeSelectUI->LoadInfo(TitleUI::ModeSelect);
				g_ModeSelectUI->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, 75.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, -200.0f, 0.0f));

				// ステージ選択
				g_StageSelectUI = AddGameObject<TitleUI>(Scene::Layer_UILayer);
				g_StageSelectUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, -200.0f, 0.0f));
				g_StageSelectUI->LoadInfo(TitleUI::StageSelect);
				g_StageSelectUI->SetAppearPos(D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, 75.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 4 - 50.0f, -200.0f, 0.0f));

				// スキルカスタムの座標や設置
				// スキル０１
				g_Skill01CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill01CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill01CustomButton->SetSkillType<TitleSkillUISkill01>();
				g_Skill01CustomButton->SetHide(true);
				// スキル０２
				g_Skill02CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill02CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill02CustomButton->SetSkillType<TitleSkillUISkill02>();
				g_Skill02CustomButton->SetHide(true);
				// スキル０３
				g_Skill03CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill03CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill03CustomButton->SetSkillType<TitleSkillUISkill03>();
				g_Skill03CustomButton->SetHide(true);
				// スキル０４
				g_Skill04CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill04CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill04CustomButton->SetSkillType<TitleSkillUISkill04>();
				g_Skill04CustomButton->SetHide(true);
				// スキル０５
				g_Skill05CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill05CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill05CustomButton->SetSkillType<TitleSkillUISkill05>();
				g_Skill05CustomButton->SetHide(true);
				// スキル０６
				g_Skill06CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill06CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill06CustomButton->SetSkillType<TitleSkillUISkill06>();
				g_Skill06CustomButton->SetHide(true);
				// スキル０７
				g_Skill07CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill07CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill07CustomButton->SetSkillType<TitleSkillUISkill07>();
				g_Skill07CustomButton->SetHide(true);
				// スキル０８
				g_Skill08CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill08CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill08CustomButton->SetSkillType<TitleSkillUISkill08>();
				g_Skill08CustomButton->SetHide(true);
				// スキル０９
				g_Skill09CustomButton = AddGameObject<TitleSkillUI>(Layer_UILayer);
				g_Skill09CustomButton->SetPosition(D3DXVECTOR3(-500.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
				g_Skill09CustomButton->SetSkillType<TitleSkillUISkill09>();
				g_Skill09CustomButton->SetHide(true);

				g_SkillEvent = AddGameObject<TitleSkillUIEvent>(Layer_UILayer);
				g_SkillEvent->SetPosition(D3DXVECTOR3(-500.0f, 0.0f, 0.0f));

				m_State = 1;
				m_Menu = MainMenu;
				m_WaitTime = 0.0f;
				break;
			}
			else
			{
				float T = m_WaitTime / (3.0f * Manager::Time);

				D3DXVec3Lerp(&CurPos, &InitPos, &TargetPos, T);
				D3DXVec3Lerp(&CurTarget, &InitTarget, &NextTarget, T);

				WorldCam->SetPosition(CurPos);
				WorldCam->SetTarget(CurTarget);
			}
			break;
		}
		break;
	case MainMenu:
		switch (m_State)
		{
		case 1:
			{
				TitleUIBackground* TUB = GetGameObject<TitleUIBackground>();
				if (TUB->GetReady())
				{
					m_State = 2;
					break;
				}
			}
			break;
		case 2:
			g_StartButton->SetAppear(true);
			g_SettingButton->SetAppear(true);
			g_QuitButton->SetAppear(true);
			if (g_BackButton->GetAppear())
			{
				g_BackButton->SetAppear(false);
			}
			if (g_ModeSelectUI->GetAppear())
			{
				g_ModeSelectUI->SetAppear(false);
			}
			
			m_State = 3;
			break;
		case 3:
			MouseEvent();
			break;
		case 4:
			m_Menu = ModeSelect;
			g_StartButton->SetAppear(false);
			g_SettingButton->SetAppear(false);
			g_QuitButton->SetAppear(false);

			g_BackButton->SetAppear(true);

			m_State = 1;
			break;
		case 5:
			m_Menu = Settings;
			g_StartButton->SetAppear(false);
			g_SettingButton->SetAppear(false);
			g_QuitButton->SetAppear(false);

			g_BackButton->SetAppear(true);

			m_State = 1;
			break;
		}
		break;
	case ModeSelect:
		switch (m_State)
		{
		case 1:
			g_ModeSelectUI->SetAppear(true);
			g_StageButton->SetAppear(true);
			g_SkillButton->SetAppear(true);

			m_State = 2;

			break;
		case 2:
			MouseEvent();
			break;
		case 3:
			m_Menu = MainMenu;
			g_ModeSelectUI->SetAppear(false);
			g_StageButton->SetAppear(false);
			g_SkillButton->SetAppear(false);

			m_State = 1;

			break;
		case 4:
			m_Menu = StageSelect;
			g_ModeSelectUI->SetAppear(false);
			g_StageButton->SetAppear(false);
			g_SkillButton->SetAppear(false);

			m_State = 1;

			break;
		case 5:
			m_Menu = SkillCustom;

			g_ModeSelectUI->SetAppear(false);
			g_StageButton->SetAppear(false);
			g_SkillButton->SetAppear(false);

			m_State = 1;
			break;
		}
		break;
	case StageSelect:
		switch (m_State)
		{
		case 1:
			g_StageSelectUI->SetAppear(true);
			g_TutorialStageButton->SetAppear(true);
			g_Stage2Button->SetAppear(true);

			m_State = 2;
			break;
		case 2:
			MouseEvent();
			break;
		case 3:
			m_Menu = ModeSelect;
			g_StageSelectUI->SetAppear(false);
			g_TutorialStageButton->SetAppear(false);
			g_Stage2Button->SetAppear(false);

			m_State = 1;
			break;
		case 4:
			LoadStartGame();
			m_State = 5;
			break;
		case 5:
			{
				TitleCharacter* _TC = GetGameObject<TitleCharacter>();
				if (_TC->CheckFinish())
				{
					m_State = 1;
					m_WaitTime = 0.0f;
					m_Menu = TitleMenu;

					LoadingScene::SetNextScene<LoadingType_Tutorial>();
					Fade::SetFade<FadeSceneType_Loading>();
				}
			}
			break;
		case 6:
			LoadStartGame();
			m_State = 7;
			break;
		case 7:
			{
				TitleCharacter* _TC = GetGameObject<TitleCharacter>();
				if (_TC->CheckFinish())
				{
					m_State = 1;
					m_WaitTime = 0.0f;
					m_Menu = TitleMenu;

					LoadingScene::SetNextScene<LoadingType_Game>();
					Fade::SetFade<FadeSceneType_Loading>();
				}
			}
			break;
		}
		break;
	case SkillCustom:
		switch (m_State)
		{
		case 1:
			g_Skill01Button->SetAppear(true);
			g_Skill02Button->SetAppear(true);
			g_Skill03Button->SetAppear(true);

			m_State = 2;
			break;
		case 2:
			MouseEvent();
			break;
		case 3:
			m_Menu = ModeSelect;
			g_Skill01Button->SetAppear(false);
			g_Skill02Button->SetAppear(false);
			g_Skill03Button->SetAppear(false);
			g_Skill01CustomButton->SetHide(true);
			g_Skill02CustomButton->SetHide(true);
			g_Skill03CustomButton->SetHide(true);
			g_Skill04CustomButton->SetHide(true);
			g_Skill05CustomButton->SetHide(true);
			g_Skill06CustomButton->SetHide(true);
			g_Skill07CustomButton->SetHide(true);
			g_Skill08CustomButton->SetHide(true);
			g_Skill09CustomButton->SetHide(true);

			m_State = 1;
			break;
		case 4:
			// スキル０１、０２、０３を表示する
			g_Skill01CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 400.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
			g_Skill01CustomButton->SetHide(false);
			g_Skill02CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 550.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
			g_Skill02CustomButton->SetHide(false);
			g_Skill03CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 700.0f, SCREEN_HEIGHT / 2 - 200.0f, 0.0f));
			g_Skill03CustomButton->SetHide(false);

			// 他は隠す
			g_Skill04CustomButton->SetHide(true);
			g_Skill05CustomButton->SetHide(true);
			g_Skill06CustomButton->SetHide(true);
			g_Skill07CustomButton->SetHide(true);
			g_Skill08CustomButton->SetHide(true);
			g_Skill09CustomButton->SetHide(true);

			m_SkillSlotNumber = 0;

			m_State = 7;

			break;
		case 5:
			// スキル０４、０５、０６を表示
			g_Skill04CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 400.0f, SCREEN_HEIGHT / 2 , 0.0f));
			g_Skill04CustomButton->SetHide(false);
			g_Skill05CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 550.0f, SCREEN_HEIGHT / 2 , 0.0f));
			g_Skill05CustomButton->SetHide(false);
			g_Skill06CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 700.0f, SCREEN_HEIGHT / 2 , 0.0f));
			g_Skill06CustomButton->SetHide(false);

			// 他は隠す
			g_Skill01CustomButton->SetHide(true);
			g_Skill02CustomButton->SetHide(true);
			g_Skill03CustomButton->SetHide(true);
			g_Skill07CustomButton->SetHide(true);
			g_Skill08CustomButton->SetHide(true);
			g_Skill09CustomButton->SetHide(true);

			m_SkillSlotNumber = 1;

			m_State = 7;

			break;
		case 6:
			// スキル０７、０８、０９を表示
			g_Skill07CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 400.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));
			g_Skill07CustomButton->SetHide(false);														
			g_Skill08CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 550.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));
			g_Skill08CustomButton->SetHide(false);														
			g_Skill09CustomButton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 4 + 700.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));
			g_Skill09CustomButton->SetHide(false);														
			
			// 他は隠す
			g_Skill01CustomButton->SetHide(true);
			g_Skill02CustomButton->SetHide(true);
			g_Skill03CustomButton->SetHide(true);
			g_Skill04CustomButton->SetHide(true);
			g_Skill05CustomButton->SetHide(true);
			g_Skill06CustomButton->SetHide(true);

			m_SkillSlotNumber = 2;

			m_State = 7;

			break;
		case 7:
			MouseEvent();
			MouseSkillEvent();
			break;
		}
		break;
	case Settings:
		switch (m_State)
		{
		case 1:
			// BGMやSEの設置ボタンを出現させる
			g_BGMButton->SetAppear(true);
			g_SEButton->SetAppear(true);
			
			m_State = 2;
			break;
		case 2:
			MouseEvent();
			break;
		case 3:
			m_Menu = MainMenu;
			// BGMやSEの設置ボタンを出現させる
			g_BGMButton->SetAppear(false);
			g_SEButton->SetAppear(false);

			m_State = 1;
			break;
		}
		break;
	}


	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		// SEを鳴らす
		AudioManager::PlaySE("SEClickButton");
	}

	Scene::Update();
}

void Title::LoadStartGame()
{
	TitleCharacter* _TC = GetGameObject<TitleCharacter>();
	_TC->Chosen();
}

// マウスの当たり判定
void Title::MouseEvent()
{
	PhysicsCast* _Phy;
	_Phy = PhysicsCast::MouseRayCast<TitleUI>(Input::GetWindowMousePos());

	if (_Phy != NULL)
	{
		std::vector<TitleUI*> ButtonList = GetGameObjects<TitleUI>();
		for (auto B : ButtonList)
		{
			if (B == _Phy->GetColldeObj() && !B->GetCantChoose())
			{
				B->SetChosen(true);
			}
			else
			{
				B->SetChosen(false);
			}

		}
	}
	else
	{
		std::vector<TitleUI*> ButtonList = GetGameObjects<TitleUI>();
		for (auto B : ButtonList)
		{
			B->SetChosen(false);
		}
	}

	// マウスが選択しているかどうか
	D3DXVECTOR2 MousePos = Input::GetWindowMousePos();
	MousePos.y -= 25.0f;
	PhysicsCast* _PhyMouse = PhysicsCast::MouseRayCast<SettingAdjustButton>(MousePos);
	if (_PhyMouse != NULL)
	{
		std::vector<SettingAdjustButton*> AdjustList = GetGameObjects<SettingAdjustButton>();
		for (auto A : AdjustList)
		{
			if (A == _PhyMouse->GetColldeObj())
			{
				A->SetChosen(true);
			}
			else
			{
				A->SetChosen(false);
			}
		}
	}
	else
	{
		std::vector<SettingAdjustButton*> AdjustList = GetGameObjects<SettingAdjustButton>();
		for (auto A : AdjustList)
		{
			A->SetChosen(false);
		}
	}

}

void Title::MouseSkillEvent()
{
	PhysicsCast* _Phy;
	D3DXVECTOR2 MousePos = Input::GetWindowMousePos();
	MousePos.y -= 25.0f;

	_Phy = PhysicsCast::MouseRayCast<TitleSkillUI>(MousePos);

	if (_Phy != NULL)
	{
		std::vector<TitleSkillUI*> ButtonList = GetGameObjects<TitleSkillUI>();
		for (auto B : ButtonList)
		{
			if (B == _Phy->GetColldeObj() && !B->GetJustForShow())
			{
				B->SetChosen(true);
			}
			else
			{
				B->SetChosen(false);
			}

		}
	}
	else
	{
		std::vector<TitleSkillUI*> ButtonList = GetGameObjects<TitleSkillUI>();
		for (auto B : ButtonList)
		{
			B->SetChosen(false);
		}
	}

}
