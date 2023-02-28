#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PauseMenuBackground.h"
#include "PhysicsCast.h"
#include "PauseMenuUI.h"
#include "input.h"

void PauseMenuBackground::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// スプライト追加
	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("PauseMenuBackground", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void PauseMenuBackground::Update()
{
	D3DXVECTOR2 MousePos = Input::GetWindowMousePos();
	MousePos.y -= 25.0f;

	PhysicsCast* _Phy = PhysicsCast::MouseRayCastPauseUI<PauseMenuUI>(MousePos);

	std::vector<PauseMenuUI*> PauseMenuUIList = Manager::GetScene()->GetAllPauseUI<PauseMenuUI>();

	if (_Phy != NULL)
	{
		for (auto P : PauseMenuUIList)
		{
			if (P == _Phy->GetColldeObj())
			{
				P->SetChosen(true);
			}
			else
			{
				P->SetChosen(false);
			}
		}
	}
	else
	{
		for (auto P : PauseMenuUIList)
		{
			P->SetChosen(false);
		}
	}

	GameObject::Update();
}
