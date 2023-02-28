#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "SettingUI.h"
#include "SettingAdjustButton.h"
#include "PhysicsCast.h"
#include "input.h"
#include "Math.h"

void SettingAdjustButton::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(20.0f, 50.0f, 0.0f);

	// �X�v���C�g�ǉ�
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite->LoadInfo("UIAdjustButton", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_Sprite->SetVisibility(false);
	m_NSSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_NSSprite->LoadInfo("UIAdjustButtonNS", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

	// �l�̏�����
	m_Value = 0.0f;
}

void SettingAdjustButton::Update()
{
	// �I������Ă���ƃe�N�X�`�����ς��
	if (m_Chosen)
	{
		m_Sprite->SetVisibility(true);
		m_NSSprite->SetVisibility(false);
	}
	else
	{
		if (m_isClick)
		{
			m_Sprite->SetVisibility(true);
			m_NSSprite->SetVisibility(false);
		}
		else
		{
			m_Sprite->SetVisibility(false);
			m_NSSprite->SetVisibility(true);
		}
	}

	if (Input::GetKeyTrigger(VK_LBUTTON))
	{
		if (m_Chosen)
		{
			m_isClick = true;
		}
	}

	if (Input::GetKeyRelease(VK_LBUTTON))
	{
		m_isClick = false;
	}

	// �ړ�����
	if (m_isClick)
	{
		// �}�E�X��X���擾
		float MousePosX = Input::GetWindowMousePos().x;
		// �l�����߂�
		m_Value = Math::GetLerpTime(m_InitPos.x, m_TarPos.x, MousePosX);
	}

	// �O�ȏ��P�ȉ��𐧌�����
	if (m_Value < 0.0f)
	{
		m_Value = 0.0f;
	}
	if (m_Value > 1.0f)
	{
		m_Value = 1.0f;
	}

	// ���`��ԗp
	D3DXVECTOR3 LerpPos;
	// ���`���
	D3DXVec3Lerp(&LerpPos, &m_InitPos, &m_TarPos, m_Value);
	// ���W�ݒu
	m_Position = LerpPos;

	GameObject::Update();
}
