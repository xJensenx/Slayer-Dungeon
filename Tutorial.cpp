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
	// �X�v���C�g�R���|�[�l���g�⃂�f����A�j���[�V�����Ȃǂ̃��[�h
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
	// ���b�V���t�B�[���h���`���[�g���A���p�ɐ؂�ւ���
	MeshField::SetMeshType(0);

	// �`���[�g���A���܂��������ĂȂ��̂��Z�b�g
	m_TutorialFinish = false;

	// �X�e�[�g���ŏ�����n�܂�
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

	// ���E��
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

	// ����̔w�i�I�u�W�F�N�g
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, 40.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(-80.0f, -3.0f, -40.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, 40.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(80.0f, -3.0f, -40.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(00.0f, -3.0f, -80.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(6.0f, 3.0f, 3.0f));
	AddGameObject<Castle>(Scene::Layer_ObjectLayer)->SetInformation(D3DXVECTOR3(00.0f, -3.0f, 80.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(6.0f, 3.0f, 3.0f));

	// �|�[�Y���j���[�̃I�u�W�F�N�g
	AddPauseUI<PauseMenuBackground>();
	// �Q�[���ĊJ�{�^��
	PauseMenuUI* _Resume = AddPauseUI<PauseMenuUI>();
	_Resume->SetType<PauseMenuUIResume>();
	_Resume->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150.0f, 0.0f));
	// �^�C�g���{�^��
	PauseMenuUI* _Title = AddPauseUI<PauseMenuUI>();
	_Title->SetType<PauseMenuUITitle>();
	_Title->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	// �Q�[���ޏo�{�^��
	PauseMenuUI* _Quit = AddPauseUI<PauseMenuUI>();
	_Quit->SetType<PauseMenuUIQuit>();
	_Quit->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150.0f, 0.0f));

	// BGM��炷
	AudioManager::PlayBGM("BGMMinion", true);

	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);

	// �`���[�g���A���̃X�e�[�g���ŏ�����n�܂�
	ChangeState<TutorialState_Greeting>();
}

void Tutorial::Uninit()
{
	// BGM���~�܂�
	AudioManager::StopBGM("BGMMinion");

	Scene::Uninit();

	Unload();
}

void Tutorial::Update()
{
	// �|�[�Y�{�^��
	if (Input::GetKeyTrigger(VK_ESCAPE))
	{
		// �t�F�[�h���Ă��Ȃ��������|�[�Y�ł���
		if (!Fade::GetisFade())
		{
			// �|�[�Y���Ă���ƃQ�[���ĊJ���܂�
			// �|�[�Y���Ă��Ȃ��ƃQ�[���|�[�Y����
			if (Manager::GetPause())
			{
				// ����炷
				AudioManager::PlaySE("SEPauseButton");

				Input::SetLockPosition(true);
				MouseCursor::SetVisibility(false);

				Manager::Pause(false);
			}
			else
			{
				// ����炷
				AudioManager::PlaySE("SEPauseButton");

				Input::SetLockPosition(false);
				MouseCursor::SetVisibility(true);

				Manager::Pause(true);
			}
		}
	}
	// �|�[�Y��Ԃ���PauseUI�̃I�u�W�F�N�g�����X�V����
	if (Manager::GetPause())
	{
		Scene::UpdatePauseUI();
		return;
	}

	// �`���[�g���A��
	m_TutorialState->Update();

	Scene::Update();
}

void Tutorial::Draw()
{
	Scene::Draw();

	// �|�[�Y��Ԃ��ƃ|�[�Y���j���[UI��`�悷��
	if (Manager::GetPause())
	{
		Scene::DrawPauseUI();
	}
}
