#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "TitleCharacter.h"
#include "TitlePlayerAnimation.h"

void TitleCharacter::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.012f, 0.012f, 0.012f);

	AddComponent<AnimModelManager>(GameObject::FirstPri)->SetModel("TitleCharacter", AnimModelManager::LitType);

	TitlePlayerAnimation* _TPA = AddAnimationManager<TitlePlayerAnimation>();
	_TPA->SetCharacter(this);
}

void TitleCharacter::Chosen()
{
	TitlePlayerAnimation* _TPA;
	_TPA = GetAnimationManager<TitlePlayerAnimation>();

	_TPA->ChangeState(TitlePlayerAnimation::Chosen);
}

bool TitleCharacter::CheckFinish()
{
	return m_AnimationFinish;
}
