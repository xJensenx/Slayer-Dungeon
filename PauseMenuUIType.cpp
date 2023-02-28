#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PauseMenuUI.h"
#include "PauseMenuUIType.h"
#include "Fade.h"
#include "input.h"
#include "MouseCursor.h"


void PauseMenuUIResume::Init()
{
	SpriteComponent* _Sprite = m_PauseMenuUI->GetSprite();
	SpriteComponent* _NS = m_PauseMenuUI->GetNSSprite();

	_Sprite->LoadInfo("PauseMenuResume", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_Sprite->SetVisibility(false);
	_NS->LoadInfo("PauseMenuResumeNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void PauseMenuUIResume::Press()
{
	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);
	Manager::Pause(false);
}

void PauseMenuUITitle::Init()
{
	SpriteComponent* _Sprite = m_PauseMenuUI->GetSprite();
	SpriteComponent* _NS = m_PauseMenuUI->GetNSSprite();

	_Sprite->LoadInfo("PauseMenuTitle", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_Sprite->SetVisibility(false);
	_NS->LoadInfo("PauseMenuTitleNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void PauseMenuUITitle::Press()
{
	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);
	Manager::Pause(false);
	
	Fade::SetFade<FadeSceneType_Title>();
}

void PauseMenuUIQuit::Init()
{
	SpriteComponent* _Sprite = m_PauseMenuUI->GetSprite();
	SpriteComponent* _NS = m_PauseMenuUI->GetNSSprite();

	_Sprite->LoadInfo("PauseMenuQuit", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_Sprite->SetVisibility(false);
	_NS->LoadInfo("PauseMenuQuitNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void PauseMenuUIQuit::Press()
{
	Input::SetLockPosition(true);
	MouseCursor::SetVisibility(false);
	Manager::Pause(false);

	Fade::SetFade<FadeSceneType_Quit>();
}
