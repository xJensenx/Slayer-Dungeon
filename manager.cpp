#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"
#include "AudioManager.h"
#include "ComponentInclude.h"
#include "Scene.h"
#include "Fade.h"
#include "Title.h"
#include "Game.h"
#include "input.h"
#include "Sea.h"
#include "MeshField.h"
#include "MouseCursor.h"
#include "LoadingScene.h"
#include "SwordTrail.h"

Manager*		Manager::s_pManager = NULL;
Scene*			Manager::m_Scene = NULL;
Fade*			Manager::m_Fade = new Fade();
GameObject*		Manager::m_MouseCursor = NULL;
Manager::SkillNumber  Manager::m_SkillType[3];
bool			Manager::m_Pause = false;
float			Manager::m_PauseTime = 0.0f;
bool			Manager::m_LimitedPause = false;


void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	SpriteComponent::Load();
	SpriteRenderer::Load();
	Sea::Load();
	MeshField::Load();

	AudioManager::Load();

	m_MouseCursor = new MouseCursor();
	m_MouseCursor->Init();

	SetSkillType(0, Skill01);
	SetSkillType(1, Skill04);
	SetSkillType(2, Skill07);

	m_Fade->Init();

	LoadingScene::SetNextScene<LoadingType_Title>();

	m_Fade->SetFade<FadeSceneType_Loading>();
}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	m_Fade->Uninit();
	delete m_Fade;

	m_MouseCursor->Uninit();

	AudioManager::Unload();

	AnimModelManager::Unload();
	ModelRenderer::Unload();
	SpriteRenderer::Unload();
	SpriteComponent::Unload();
	Sea::Unload();
	MeshField::Unload();
	SwordTrail::Unload();

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

Manager::Manager()
{
}

Manager::Manager(const Manager& src)
{
	s_pManager = src.s_pManager;
}

Manager& Manager::operator=(const Manager& src)
{
	s_pManager = src.s_pManager;
	return *this;
}

void Manager::Create()
{
	if (s_pManager == NULL)
	{
		s_pManager = new Manager();
		s_pManager->Init();
	}
}

void Manager::Destroy()
{
	delete s_pManager;

	s_pManager = NULL;
}

void Manager::Update()
{
	// �������ԓ��Ƀ|�[�Y���鏈��
	LimitedPauseEvent();

	m_Fade->Update();

	Input::Update();

	m_MouseCursor->Update();

	if (m_Scene != NULL)
	{
		m_Scene->Update();
	}
}

void Manager::Draw()
{
	Renderer::Begin();

	// �@ �J����
	// �A �t�B�[���h
	// �B 3D�I�u�W�F�N�g
	// �C 2D�I�u�W�F�N�g
	
	//// ���C�g
	//LIGHT light;
	//light.Enable = true;
	//light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	//light.Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	//D3DXVec4Normalize(&light.Direction, &light.Direction);
	//light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);//���̓�����Ȃ������̔��ˌW��
	//light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���̓����镔���̔��ˌW��

	//// ���C�g�J�����̃r���[�s����쐬
	//D3DXVECTOR3 Eye = D3DXVECTOR3(-10.0f, 10.0f, -10.0f);
	//D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//D3DXMatrixLookAtLH(&light.ViewMatrix, &Eye,
	//	&At, &Up);

	//// ���C�g�J�����̃v���W�F�N�V�����s����쐬
	//D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,
	//	(float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 30.0f);

	Renderer::DrawLight();
	LIGHT light = Renderer::GetLight();

	Renderer::SetLight(light);

	// �u1�p�X�ځv�V���h�E�o�b�t�@�̍쐬
	Renderer::BeginDepth();

	// ���C�g�J�����̍s����Z�b�g
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	// �e�𗎂Ƃ������I�u�W�F�N�g��`��
	if (m_Scene != NULL)
	{
		m_Scene->DrawShadow();
	}

	Renderer::Begin();

	if (m_Scene != NULL)
	{
		m_Scene->Draw();
	}

	m_Fade->Draw();

	m_MouseCursor->Draw();

	Renderer::End();
}

void Manager::LimitedPauseEvent()
{
	if (!m_LimitedPause) return;

	m_PauseTime--;

	if (m_PauseTime <= 0.0f)
	{
		Manager::PauseGame(false);
		m_LimitedPause = false;
	}
}
