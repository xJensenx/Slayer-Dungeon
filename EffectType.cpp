#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Effect.h"
#include "EffectType.h"

void EffectType::Update()
{
	// �X�v���C�g���擾
	SpriteComponent* _SC = m_Effect->GetComponent<SpriteComponent>();
	
	// �X�V����
	m_Cnt++;
	// �Ō�܂ōs������폜���܂�
	if (m_Cnt > m_Yoko * m_Tate)
	{
		m_Effect->SetDestroy();
		return;
	}

	// ���Əc�̌v�Z��
	float x = m_Cnt % m_Yoko * (1.0f / m_Yoko);
	float y = m_Cnt / m_Yoko * (1.0f / m_Tate);
	// �X�v���C�g��TexCoord�𒲐�
	_SC->SetTexCoord(D3DXVECTOR2(x, y));

}

void EffectType_Block::Init()
{
	// �c�Ɖ��̐ݒu
	m_Tate = 4;
	m_Yoko = 5;

	// �X�v���C�g
	SpriteComponent* _SC = m_Effect->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SC->LoadInfo("BlockCounterEffect", "Unlit", D3DXVECTOR2(0.2f, 0.25f));

	// ������
	m_Cnt = 0;
}

void EffectType_AttackHit::Init()
{
	// �c�Ɖ��̐ݒu
	m_Tate = 4;
	m_Yoko = 5;

	// �X�v���C�g
	SpriteComponent* _SC = m_Effect->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SC->LoadInfo("AttackHitEffect", "Unlit", D3DXVECTOR2(0.2f, 0.25f));

	// ������
	m_Cnt = 0;
}

void EffectType_BossMeteor::Init()
{
	// �c�Ɖ��̐ݒu
	m_Tate = 2;
	m_Yoko = 5;

	// �X�v���C�g
	SpriteComponent* _SC = m_Effect->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->SetSpriteType(SpriteComponent::AnimationBilBoard);
	_SC->LoadInfo("MeteorHitEffect", "Unlit", D3DXVECTOR2(0.2f, 0.5f));

	// ������
	m_Cnt = 0;
}
