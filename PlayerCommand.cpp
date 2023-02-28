#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "PlayerCommand.h"

#include "Player.h"
#include "Math.h"

void PlayerCommand::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CommandType = Command_Logo;
	m_Chosen = false;
	m_WaitTime = m_TotalTime;

	// �T�C�Y�w��
	m_Size = D3DXVECTOR3(m_NormalSize, 40.0f, 0.0f);
	// �X�v���C�g������
	m_ChosenSprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_Sprite = AddComponent<SpriteComponent>(GameObject::FirstPri);
}

void PlayerCommand::Update()
{
	GameObject::Update();

	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �v���C���[�擾
	Player* _Player = _Scene->GetGameObject<Player>();

	// ���S���ƍX�V�����s��Ȃ�
	if (m_CommandType == Command_Logo) return;

	if (m_CommandType == Command_Ult)
	{
		if (_Player != NULL)
		{
			if (_Player->GetCurDp() < m_UseDp)
			{
				m_ChosenSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f));
				m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f));
			}
			else
			{
				m_ChosenSprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
				m_Sprite->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}

	// �I�΂ꂽ��
	if (m_Chosen)
	{
		// �I�΂ꂽ�e�N�X�`����\�����A�ҋ@��Ԃ̃e�N�X�`�����B��
		m_ChosenSprite->SetVisibility(true);
		m_Sprite->SetVisibility(false);

		// �A�j���[�V����
		if (m_WaitTime < m_TotalTime)
		{
			m_WaitTime++;
			float T = m_WaitTime / m_TotalTime;

			m_Size.x = Math::FloatLerp(m_NormalSize, m_ChosenSize, T);
		}
		else
		{
			m_Size.x = m_ChosenSize;
		}
	}
	else
	{
		// �ҋ@��Ԃ̃e�N�X�`����\�����A�I�΂ꂽ�e�N�X�`�����B��
		m_ChosenSprite->SetVisibility(false);
		m_Sprite->SetVisibility(true);

		// �A�j���[�V����
		if (m_WaitTime < m_TotalTime)
		{
			m_WaitTime++;
			float T = m_WaitTime / m_TotalTime;

			m_Size.x = Math::FloatLerp(m_ChosenSize, m_NormalSize, T);
		}
		else
		{
			m_Size.x = m_NormalSize;
		}
	}
}

void PlayerCommand::SetCommandType(CommandType _CT)
{
	// �R�}���h�^�C�v���w�肷��
	m_CommandType = _CT;

	// �R�}���h�̑ҋ@��ԃe�N�X�`����I�΂ꂽ�e�N�X�`����ݒ肷��
	switch (m_CommandType)
	{
	case Command_Logo:
		m_ChosenSprite->LoadInfo("CommandLogo", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
		m_ChosenSprite->SetVisibility(false);
		m_ChosenSprite->SetNormalTexture("CommandChosenNoise");
		m_Sprite->LoadInfo("CommandLogo", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->SetVisibility(true);

		break;
	case Command_Attack:
		m_ChosenSprite->LoadInfo("CommandAttackChosen", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
		m_ChosenSprite->SetVisibility(false);
		m_ChosenSprite->SetNormalTexture("CommandChosenNoise");
		m_Sprite->LoadInfo("CommandAttack", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->SetVisibility(true);
		
		break;

	case Command_Ult:
		m_ChosenSprite->LoadInfo("CommandUltChosen", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
		m_ChosenSprite->SetVisibility(false);
		m_ChosenSprite->SetNormalTexture("CommandChosenNoise");
		m_Sprite->LoadInfo("CommandUlt", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
		m_Sprite->SetVisibility(true);
		
		break;
	}
}
