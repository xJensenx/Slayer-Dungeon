#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "PlayerMpBar.h"
#include "Player.h"


void PlayerMpBar::Init()
{
	// ������
	m_Position = D3DXVECTOR3(10.0f, SCREEN_HEIGHT - 50.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Size = D3DXVECTOR3(400.0f, 40.0f, 0.0f);

	m_Insufficient = false;

	// �X�v���C�g�R���|�[�l���g
	m_PlayerNoMpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_PlayerNoMpBar->SetSpriteType(SpriteComponent::ProgressBar);
	m_PlayerNoMpBar->LoadInfo("PlayerNoMp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	m_PlayerFullMpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	m_PlayerFullMpBar->SetSpriteType(SpriteComponent::ProgressBar);
	m_PlayerFullMpBar->LoadInfo("PlayerFullMp", "HpBar", D3DXVECTOR2(1.0f, 1.0f));
	m_PlayerFullMpBar->SetNormalTexture("HpBarNoise");

	// ProgressBar��ǉ�����
	ProgressBar* _PB = AddComponent<ProgressBar>(GameObject::ThirdPri);
	_PB->SetProgressBar(m_PlayerNoMpBar, m_PlayerFullMpBar);
}

void PlayerMpBar::Update()
{
	if (m_Character != NULL)
	{
		if (m_Character->GetDestroy())
		{
			SetDestroy();
			return;
		}
		// ����Ȃ����̕\���G�t�F�N�g
		if (m_Insufficient)
		{
			if (m_InsufficientTime < (0.5f * Manager::Time))
			{
				m_InsufficientTime++;
			}
			else
			{
				m_Insufficient = false;		
			}
		}
		else
		{
			if (m_InsufficientTime > 0.0f)
			{
				m_InsufficientTime--;
			}
			else
			{
				m_InsufficientTime = 0.0f;
			}
		}
		
		float T = m_InsufficientTime / (0.5f * Manager::Time);

		// �w��F
		D3DXVECTOR4 RedColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

		// �����F
		D3DXVECTOR4 NormalColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		// Lerp�p�ϐ�
		D3DXVECTOR4 LerpColor;

		// �F��Lerp
		D3DXVec4Lerp(&LerpColor, &NormalColor, &RedColor, T);

		// �F�̐ݒu
		m_PlayerFullMpBar->SetColor(LerpColor);
		m_PlayerNoMpBar->SetColor(LerpColor);



		// ProgressBar�Ɏ�����Hp��ő�Hp���X�V����
		ProgressBar* _PB = GetComponent<ProgressBar>();

		float FullMpOffSetX = m_Size.x * (_PB->GetProgressValue() - 1.0f);

		m_PlayerFullMpBar->SetSizeOffset(D3DXVECTOR3(FullMpOffSetX, 0.0f, 0.0f));

		// �v���C���[�̍ő�Mp
		float FullMp = m_Character->GetMaxMp();
		// �v���C���[�̌���Mp
		float CurMp = m_Character->GetCurMp();

		// ProgressBar���X�V����
		_PB->SetMaxValue(FullMp);
		_PB->SetCurrentValue(CurMp);
	}

	GameObject::Update();
}
