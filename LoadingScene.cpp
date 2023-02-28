#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "LoadingScene.h"
#include "LoadingLogo.h"

#include "Game.h"

#include "Fade.h"

#include <thread>

bool LoadingScene::m_LoadFinish = false;
LoadingType* LoadingScene::m_LoadNext = NULL;

void LoadingScene::Init()
{
	SetLoadFinish(false);
	AddGameObject<LoadingLogo>(Layer_UILayer);
	m_LoadNext->LoadAsset();

}

void LoadingScene::Uninit()
{
	Scene::Uninit();

	m_LoadFinish = false;
}

void LoadingScene::Update()
{
	Scene::Update();

	if (GetLoadFinish()) 
	{
		m_LoadNext->LoadScene();
	}
}

void LoadingType_Title::LoadAsset()
{
	std::thread th(Title::Load);
	th.detach();
}

void LoadingType_Title::LoadScene()
{
	Fade::SetFade<FadeSceneType_Title>();
}

void LoadingType_Game::LoadAsset()
{
	std::thread th(Game::Load);
	th.detach();
}

void LoadingType_Game::LoadScene()
{
	Fade::SetFade<FadeSceneType_Game>();
}

void LoadingType_Tutorial::LoadAsset()
{
	std::thread th(Tutorial::Load);
	th.detach();
}

void LoadingType_Tutorial::LoadScene()
{
	Fade::SetFade<FadeSceneType_Tutorial>();
}
