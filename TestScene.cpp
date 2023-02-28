#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "Camera.h"
#include "MeshField.h"
#include "EmptyObject.h"
#include "TitleIsland.h"

#include "input.h"
#include "TestScene.h"
#include "TitleCharacter.h"
#include "Game.h"
#include "Sword.h"
#include "Player.h"
#include "Sky.h"
#include "Minion.h"
#include "Boss.h"

#include "PhysicsCast.h"
#include "MouseCursor.h"
#include "Sea.h"
#include "Fade.h"
#include "LimitWall.h"

#include "PauseMenuBackground.h"
#include "PauseMenuUI.h"

Camera* g_Cam;
EmptyObject* g_ControlObj;

void TestScene::Init()
{
	g_Cam = AddGameObject<Camera>(Layer_CameraLayer);

	AddGameObject<Sky>(Layer_ObjectLayer);

	AddGameObject<Sea>(Layer_ObjectLayer);

	AddGameObject<MeshField>(Layer_ObjectLayer);
	Player* _Player = AddGameObject<Player>(Layer_ObjectLayer);
	_Player->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -40.0f));

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

	//AddGameObject<Boss>(Layer_ObjectLayer)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	//AddGameObject<EmptyObject>(Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//// 選ぶキャラクターを追加する
	//AddGameObject<TitleCharacter>(Layer_ObjectLayer)->SetPosition(D3DXVECTOR3(20.0f, 1.5f, 5.0f));

	//g_ControlObj = AddGameObject<EmptyObject>(Layer_ObjectLayer);
	//g_ControlObj->SetPosition(D3DXVECTOR3(5.0f, 5.0f, 0.0f));

	//AddGameObject<Sword>(Layer_ObjectLayer)->SetPosition(D3DXVECTOR3(22.0f, 1.5f, 5.0f));
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


	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);
}

void TestScene::Uninit()
{
	Scene::Uninit();

	Game::Unload();
}

void TestScene::Update()
{
	if (Input::GetKeyTrigger(VK_ESCAPE))
	{
		// フェードしていない時だけポーズできる
		if (!Fade::GetisFade())
		{
			if (Manager::GetPause())
			{
				Input::SetLockPosition(true);
				MouseCursor::SetVisibility(false);

				Manager::Pause(false);
			}
			else
			{
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

	Scene::Update();
}

void TestScene::Draw()
{
	Scene::Draw();
	// ポーズ状態だとポーズメニューUIを描画する
	if (Manager::GetPause())
	{
		Scene::DrawPauseUI();
	}
}
