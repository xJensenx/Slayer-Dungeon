#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PauseMenuUI.h"
#include "PhysicsCast.h"
#include "input.h"

void PauseMenuUI::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(500.0f, 100.0f, 0.0f);

	// �X�v���C�g�ǉ�
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NSSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);

	m_Chosen = false;
}

void PauseMenuUI::Update()
{
	// �I�΂�Ă�����
	if (m_Chosen)
	{
		m_Sprite->SetVisibility(true);
		m_NSSprite->SetVisibility(false);

		// ���N���b�N�����
		if (Input::GetKeyTrigger(VK_LBUTTON))
		{
			// ��ނɂ���ď������ς��
			m_UIType->Press();
		}
	}
	else
	{
		m_Sprite->SetVisibility(false);
		m_NSSprite->SetVisibility(true);
	}

	GameObject::Update();
}
