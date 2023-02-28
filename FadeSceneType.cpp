#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Title.h"
#include "Game.h"
#include "LoadingScene.h"
#include "Result.h"
#include "Tutorial.h"
#include "TestScene.h"
#include "FadeSceneType.h"

void FadeSceneType_Title::SetScene()
{
	Manager::SetScene<Title>();
}

void FadeSceneType_Game::SetScene()
{
	Manager::SetScene<Game>();
}

void FadeSceneType_Loading::SetScene()
{
	Manager::SetScene<LoadingScene>();
}

void FadeSceneType_Result::SetScene()
{
	Manager::SetScene<Result>();
}

void FadeSceneType_Tutorial::SetScene()
{
	Manager::SetScene<Tutorial>();
}

void FadeSceneType_Quit::SetScene()
{
	QuitGame();
}

void FadeSceneType_Test::SetScene()
{
	Manager::SetScene<TestScene>();
}
