#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "input.h"
#include "AudioManager.h"
#include "Fade.h"
#include "Camera.h"
#include "model.h"
#include "Sky.h"
#include "Player.h"
#include "EmptyObject.h"
#include "Polygon2D.h"
#include "ModelRenderer.h"
#include "Result.h"
#include "Game.h"
#include "Sea.h"
#include "MeshField.h"
#include "Boss.h"
#include "CinematicBorder.h"
#include "Minion.h"
#include "LoadingScene.h"
#include "PlayerHpBar.h"
#include "GameUI.h"

#include "Math.h"
#include "MouseCursor.h"
#include "BossBehaviorTree.h"
#include "PauseMenuBackground.h"
#include "PauseMenuUI.h"
#include "LimitWall.h"
#include "Castle.h"


CinematicBorder* g_TopBorder;
CinematicBorder* g_BotBorder;
Player* g_Player;
Camera* g_MainCam;
Boss* g_Boss;
Minion* g_Minion;
GameUI* g_TutorialPic;
GameUI* g_CharacterPic;
GameUI* g_MoveOrAttackPic;

void Game::Load()
{
	// スプライトコンポーネントやモデルやアニメーションなどのロード
	ModelRenderer::LoadGameAsset();
	AnimModelManager::LoadGameAsset();
	LoadingScene::SetLoadFinish(true);
}

void Game::Unload()
{
	AnimModelManager::UnloadGameAsset();
	ModelRenderer::UnloadGameAsset();
}

void Game::Init()
{
	// メッシュフィールドをゲーム用に切り替える
	MeshField::SetMeshType(1);

	//ModelManager::Init();

	g_MainCam = AddGameObject<Camera>(Layer_CameraLayer);
	g_MainCam->SetInformation(D3DXVECTOR3(0.0f, 15.0f, -43.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_MainCam->SetTarget(D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	g_MainCam->InitOldPos();
	AddGameObject<Sky>(Layer_ObjectLayer);
	AddGameObject<Sea>(Layer_ObjectLayer);
	AddGameObject<MeshField>(Layer_ObjectLayer);

	g_Player = AddGameObject<Player>(Layer_ObjectLayer);
	g_Player->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -40.0f));

	// Minionを追加する
	g_Minion = AddGameObject<Minion>(Layer_ObjectLayer);
	g_Minion->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	g_TopBorder = AddGameObject<CinematicBorder>(Layer_UILayer);
	g_TopBorder->SetPosType(CinematicBorder::Top);

	g_BotBorder = AddGameObject<CinematicBorder>(Layer_UILayer);
	g_BotBorder->SetPosType(CinematicBorder::Bot);
	m_isMinionDead = false;

	g_TutorialPic = AddGameObject<GameUI>(Layer_UILayer);
	g_TutorialPic->LoadInfo(GameUI::TutorialPic);
	g_TutorialPic->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250.0f, 200.0f, 0.0f));
	g_TutorialPic->SetAppearPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250.0f, 200.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 + 250.0f, -200.0f, 0.0f));

	g_CharacterPic = AddGameObject<GameUI>(Layer_UILayer);
	g_CharacterPic->LoadInfo(GameUI::CharacterTutorial);
	g_CharacterPic->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250.0f, 200.0f, 0.0f));
	g_CharacterPic->SetAppearPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250.0f, 200.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 250.0f, -200.0f, 0.0f));

	g_MoveOrAttackPic = AddGameObject<GameUI>(Layer_UILayer);
	g_MoveOrAttackPic->LoadInfo(GameUI::MoveOrAttack);
	g_MoveOrAttackPic->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f));
	g_MoveOrAttackPic->SetAppearPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));

	
	// 初期化処理
	m_Cinematic = true;
	m_Cutscene = FirstCutscene;
	m_State = 1;
	m_WaitTime = 0.0f;

	if (m_Cinematic)
	{
		g_Minion->ChangeBehavior<MinionBehaviorTree_Idle>();
		g_TopBorder->SetCutscene(true);
		g_BotBorder->SetCutscene(true);
		g_MainCam->SetCinematicMode(true);
		g_Player->SetCinematicMode(true);
		g_Minion->SetCinematicMode(true);
	}
	// 限界壁
	LimitWall* _L1 = AddGameObject<LimitWall>(Scene::Layer_ObjectLayer);
	_L1->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	_L1->SetScale(D3DXVECTOR3(1.0f, 50.0f, 50.0f));
	LimitWall* _L2 = AddGameObject<LimitWall>(Scene::Layer_ObjectLayer);
	_L2->SetPosition(D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
	_L2->SetScale(D3DXVECTOR3(1.0f, 50.0f, 50.0f));
	LimitWall* _L3 = AddGameObject<LimitWall>(Scene::Layer_ObjectLayer);
	_L3->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
	_L3->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	_L3->SetScale(D3DXVECTOR3(1.0f, 50.0f, 50.0f));
	LimitWall* _L4 = AddGameObject<LimitWall>(Scene::Layer_ObjectLayer);
	_L4->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	_L4->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	_L4->SetScale(D3DXVECTOR3(1.0f, 50.0f, 50.0f));

	// ポーズメニューのオブジェクト
	AddPauseUI<PauseMenuBackground>();
	// ゲーム再開ボタン
	PauseMenuUI* _Resume = AddPauseUI<PauseMenuUI>();
	_Resume->SetType<PauseMenuUIResume>();
	_Resume->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150.0f, 0.0f));
	// タイトルボタン
	PauseMenuUI* _Title = AddPauseUI<PauseMenuUI>();
	_Title->SetType<PauseMenuUITitle>();
	_Title->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	// ゲーム退出ボタン
	PauseMenuUI* _Quit = AddPauseUI<PauseMenuUI>();
	_Quit->SetType<PauseMenuUIQuit>();
	_Quit->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150.0f, 0.0f));

	// 周りの背景オブジェクト
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, 40.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, -40.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, 40.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, -40.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(00.0f, -3.0f, -80.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(6.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(00.0f, -3.0f, 80.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(6.0f, 3.0f, 3.0f));


	// BGMを鳴らす
	AudioManager::PlayBGM("BGMMinion", true);

	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);
}

void Game::Uninit()
{
	// BGMを止まる
	AudioManager::StopBGM("BGMMinion");
	AudioManager::StopBGM("BGMBoss");
	Scene::Uninit();

	Unload();
}

void Game::Update()
{
	// ポーズボタン
	if (Input::GetKeyTrigger(VK_ESCAPE))
	{
		// フェードしていない時だけポーズできる
		if (!Fade::GetisFade())
		{
			// ポーズしているとゲーム再開します
			// ポーズしていないとゲームポーズする
			if (Manager::GetPause())
			{				
				// 音を鳴らす
				AudioManager::PlaySE("SEPauseButton");

				Input::SetLockPosition(true);
				MouseCursor::SetVisibility(false);

				Manager::Pause(false);
			}
			else
			{				
				// 音を鳴らす
				AudioManager::PlaySE("SEPauseButton");


				Input::SetLockPosition(false);
				MouseCursor::SetVisibility(true);

				Manager::Pause(true);
			}
		}
	}
	// ポーズ状態だとPauseUIのオブジェクトだけ更新処理
	if (Manager::GetPause())
	{
		Scene::UpdatePauseUI();
		return;
	}

	Player* _Player = GetGameObject<Player>();
	Camera* _Camera = GetGameObject<Camera>();

	if (_Player != NULL)
	{
		D3DXVECTOR3 PlayerPos = _Player->GetPosition();
		D3DXVECTOR3 CameraFor = _Camera->GetForward();
		Renderer::SetLightPosition(D3DXVECTOR4(PlayerPos.x + 5.0f, PlayerPos.y + 5.0f, PlayerPos.z, 0.0f));
		Renderer::SetLightDirection(D3DXVECTOR4(CameraFor.x, -1.0f, CameraFor.z, 0.0f));
	}

	if (m_isMinionDead)
	{
		if (!g_Player->GetisUlt())
		{
			m_isMinionDead = false;
			m_Cutscene = SecondCutscene;
		}
	}

	// カットシーン
	switch (m_Cutscene)
	{
	case FirstCutscene:
		switch (m_State)
		{
		case 1:
			m_WaitTime++;
			if (m_WaitTime > 2.0f * Manager::Time)
			{
				m_State = 2;
			}
			break;
		case 2:
			{
				D3DXVECTOR3 CameraPos = g_Minion->GetPosition();
				CameraPos.y += 1.5f;
				CameraPos.z -= 2.0f;
				D3DXVECTOR3 TargetPos = g_Minion->GetPosition();
				TargetPos.y += 1.5f;

				g_MainCam->BlendTo(CameraPos, TargetPos, 3.0f);
				m_WaitTime = 0.0f;
				m_State = 3;
			}
			break;
		case 3:
			m_WaitTime++;
			if (m_WaitTime > 3.0f * Manager::Time)
			{
				g_Minion->ChangeBehavior<MinionBehaviorTree_Show>();
				m_WaitTime = 0.0f;
				m_State = 4;
			}
			break;
		case 4:
			m_WaitTime++;
			if (m_WaitTime > 1.5f * Manager::Time)
			{
				g_TopBorder->SetCutscene(false);
				g_BotBorder->SetCutscene(false);
				g_MainCam->BlendBack(3.0f);
				m_WaitTime = 0.0f;
				m_State = 5;
			}
			break;
		case 5:
			m_WaitTime++;
			if (m_WaitTime > 3.0f * Manager::Time)
			{
				g_Player->SetCinematicMode(false);
				g_Minion->SetCinematicMode(false);
				g_Minion->ChangeBehavior<MinionBehaviorTree_Chase>();
				g_MainCam->SetCinematicMode(false);
				m_WaitTime = 0.0f;
				m_State = 6;
			}
			break;
		case 6:
			m_Cutscene = None;
			m_State = 1;
			break;
		}
		break;
	case SecondCutscene:
		switch (m_State)
		{
		case 1:
			// MinionのBGMを止まる
			AudioManager::StopBGM("BGMMinion");

			g_TopBorder->SetCutscene(true);
			g_BotBorder->SetCutscene(true);
			g_MainCam->SetCinematicMode(true);
			g_Player->SetCinematicMode(true);
			g_Player->BackToIdle();
			m_WaitTime = 0.0f;
			m_State = 2;
			break;
		case 2:
			m_WaitTime++;
			if (m_WaitTime > 3.0f * Manager::Time)
			{
				m_WaitTime = 0.0f;
				m_State = 3;
			}
			break;
		case 3:
			// ボスのBGMを鳴らす
			AudioManager::PlayBGM("BGMBoss", true);

			// ボスを追加する
			g_Boss = AddGameObject<Boss>(Layer_ObjectLayer);
			g_Boss->SetPosition(D3DXVECTOR3(0.0f, 70.0f, 40.0f));
			g_Boss->SetCinematicMode(true);
			{
				RigidBody* _RBBoss = g_Boss->GetComponent<RigidBody>();
				_RBBoss->SetIgnoreGrav(true);
				_RBBoss->SetIgnoreMass(true);
			}
			
			g_MainCam->BlendTo(D3DXVECTOR3(0.0f, 5.0f, 30.0f), D3DXVECTOR3(0.0f, 7.5f, 40.0f), 1.0f);

			m_WaitTime = 0.0f;
			m_State = 4;

			break;
		case 4:
			m_WaitTime++;
			if (m_WaitTime > 1.0f * Manager::Time)
			{
				m_WaitTime = 0.0f;
				m_State = 5;
				g_Boss->ChangeBehaviorTree<BossShow>();
			}
			break;
		case 5:
			{
				D3DXVECTOR3 BossInitPos = D3DXVECTOR3(0.0f, 70.0f, 40.0f);
				D3DXVECTOR3 BossTarPos = D3DXVECTOR3(0.0f, -1.0f, 40.0f);

				m_WaitTime++;
				if (m_WaitTime < 2.0f * Manager::Time)
				{
					if (m_WaitTime > 1.7f * Manager::Time)
					{
						g_Boss->SetAlmostJumpFinish();
					}

					float T = m_WaitTime / (2.0f * Manager::Time);
					
					D3DXVECTOR3 LerpPos;

					D3DXVec3Lerp(&LerpPos, &BossInitPos, &BossTarPos, T);

					g_Boss->SetPosition(LerpPos);
				}
				else
				{
					AudioManager::PlaySE("SEBossLand");
					g_MainCam->ShakeCam(D3DXVECTOR3(0.1f, 0.1f, 0.0f), 0.5f);
					m_WaitTime = 0.0f;
					m_State = 6;
				}
			}
			break;

		case 6:
			m_WaitTime++;
			if (m_WaitTime > 0.5f * Manager::Time)
			{
				AudioManager::PlaySE("SEBossScream");

				g_MainCam->ShakeCam(D3DXVECTOR3(0.1f, 0.1f, 0.0f), 2.25f);
				
				m_WaitTime = 0.0f;
				m_State = 7;
			}
			break;
		case 7:
			m_WaitTime++;
			if (m_WaitTime > 162.0f)
			{
				g_TopBorder->SetCutscene(false);
				g_BotBorder->SetCutscene(false);
				g_MainCam->BlendBack(3.0f);
				m_WaitTime = 0.0f;
				m_State = 8;
			}
			break;
		case 8:
			m_WaitTime++;
			if (m_WaitTime > 3.0f * Manager::Time)
			{
				g_Player->SetCinematicMode(false);
				g_Boss->SetCinematicMode(false);
				{
					RigidBody* _RBBoss = g_Boss->GetComponent<RigidBody>();
					_RBBoss->SetIgnoreGrav(false);
					_RBBoss->SetIgnoreMass(false);
				}
				g_MainCam->SetCinematicMode(false);
				m_Cutscene = None;
				m_WaitTime = 0.0f;
				m_State = 1;
			}
			break;
			
		}
		break;
	default:
		break;
	}

	Scene::Update();
}

void Game::Draw()
{
	Scene::Draw();

	// ポーズ状態だとポーズメニューUIを描画する
	if (Manager::GetPause())
	{
		Scene::DrawPauseUI();
	}

}
