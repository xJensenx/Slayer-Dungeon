#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "LoadingScene.h"
#include "Tutorial.h"
#include "Fade.h"
#include "input.h"
#include "MouseCursor.h"

#include "Sky.h"
#include "Sea.h"
#include "MeshField.h"
#include "Camera.h"
#include "Player.h"
#include "Minion.h"
#include "PauseMenuBackground.h"
#include "PauseMenuUI.h"
#include "LimitWall.h"
#include "AudioManager.h"
#include "Castle.h"

void Tutorial::Load()
{
	// スプライトコンポーネントやモデルやアニメーションなどのロード
	ModelRenderer::LoadGameAsset();
	AnimModelManager::LoadGameAsset();
	LoadingScene::SetLoadFinish(true);
}

void Tutorial::Unload()
{
	ModelRenderer::UnloadGameAsset();
	AnimModelManager::UnloadGameAsset();
}

void Tutorial::Init()
{	
	// メッシュフィールドをチュートリアル用に切り替える
	MeshField::SetMeshType(0);

	// チュートリアルまだ完成してないのをセット
	m_TutorialFinish = false;

	// ステートを最初から始まる
	m_TutorialState = 0;

	AddGameObject<Sky>(Layer_ObjectLayer);
	AddGameObject<Sea>(Layer_ObjectLayer);
	AddGameObject<MeshField>(Layer_ObjectLayer);

	Camera* _Cam = AddGameObject<Camera>(Layer_CameraLayer);
	_Cam->SetTarget(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	m_TutorialPlayer = AddGameObject<Player>(Layer_ObjectLayer);
	m_TutorialPlayer->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -40.0f));
	m_TutorialMinion = AddGameObject<Minion>(Layer_ObjectLayer);
	m_TutorialMinion->ChangeBehavior<MinionBehaviorTree_Idle>();
	m_MissionUI = AddGameObject<TutorialUI>(Layer_UILayer);
	m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 60.0f, 0.0f));
	m_MissionUI->SetUIType<TutorialUIType_MissionUI>();

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

	// 周りの背景オブジェクト
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, 40.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, -40.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, 40.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, -40.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(00.0f, -3.0f, -80.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(6.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(00.0f, -3.0f, 80.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(6.0f, 3.0f, 3.0f));

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

	// BGMを鳴らす
	AudioManager::PlayBGM("BGMMinion", true);

	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);

	// チュートリアルのステートを最初から始まる
	ChangeState<TutorialState_Greeting>();
}

void Tutorial::Uninit()
{
	// BGMを止まる
	AudioManager::StopBGM("BGMMinion");

	Scene::Uninit();

	Unload();
}

void Tutorial::Update()
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

	// チュートリアル
	m_TutorialState->Update();

	Scene::Update();
}

void Tutorial::Draw()
{
	Scene::Draw();

	// ポーズ状態だとポーズメニューUIを描画する
	if (Manager::GetPause())
	{
		Scene::DrawPauseUI();
	}
}
