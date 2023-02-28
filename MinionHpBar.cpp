#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "Minion.h"

#include "MinionHpBar.h"

// �O���[�o���ϐ�
SpriteComponent* g_FullHpBar;

void MinionHpBar::Init()
{
	// ������
	m_Position = m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(3.0f, 0.4f, 0.0f);

	// �X�v���C�g�R���|�[�l���g
	SpriteComponent* NoHpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	NoHpBar->LoadInfo("MinionNoHp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	NoHpBar->SetSpriteType(SpriteComponent::ProgressBarBilBoard);
	g_FullHpBar = AddComponent<SpriteComponent>(GameObject::FirstPri);
	g_FullHpBar->LoadInfo("MinionFullHp", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	g_FullHpBar->SetSpriteType(SpriteComponent::ProgressBarBilBoard);

	// ProgressBar��ǉ�����
	ProgressBar* _PB = AddComponent<ProgressBar>(GameObject::ThirdPri);
	_PB->SetProgressBar(NoHpBar, g_FullHpBar);
}

void MinionHpBar::Update()
{
	if (m_Character != NULL)
	{
		// ProgressBar�Ɏ�����Hp��ő�Hp���X�V����
		ProgressBar* _PB = GetComponent<ProgressBar>();

		// ���W����
		D3DXVECTOR3 MinionPos = m_Character->GetPosition();
		D3DXVECTOR3 MinionRight = m_Character->GetRight();
		MinionPos.x -= MinionRight.x * (m_Size.x / 2);
		MinionPos.z -= MinionRight.z * (m_Size.x / 2);
		MinionPos.y += 3.0f;
		m_Position = MinionPos;

		float FullHpOffSetX = m_Size.x * (_PB->GetProgressValue() - 1.0f);

		g_FullHpBar->SetSizeOffset(D3DXVECTOR3(FullHpOffSetX, 0.0f, 0.0f));
		

		// Minion�̍ő�Hp
		float FullHp = m_Character->GetMaxHp();
		// Minion�̌���Hp
		float CurHp = m_Character->GetCurrentHp();

		// ProgressBar���X�V����
		_PB->SetMaxValue(FullHp);
		_PB->SetCurrentValue(CurHp);
	}
	else
	{
		SetDestroy();
		return;
	}
	

	GameObject::Update();
}
