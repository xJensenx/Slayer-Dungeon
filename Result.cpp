#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "AudioManager.h"
#include "ComponentInclude.h"

#include "Fade.h"
#include "input.h"
#include "Title.h"
#include "Result.h"
#include "PressContinue.h"

#include "ResultLogo.h"
#include "MouseCursor.h"

void Result::Init()
{
	AddGameObject<ResultLogo>(Layer_UILayer);
	AddGameObject<PressContinue>(Layer_UILayer);

	Input::SetLockPosition(false);
	MouseCursor::SetVisibility(true);

}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN) || Input::GetKeyTrigger(VK_LBUTTON))
	{
		Fade::SetFade<FadeSceneType_Title>();
	}
}
