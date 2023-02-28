#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Boss_AttackWarning.h"
#include "MeshField.h"

void Boss_AttackWarning::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �ŏ��̃T�C�Y�͑S��0.0f
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �X�v���C�g�ǉ�
	SpriteComponent* _SR = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SR->SetSpriteType(SpriteComponent::WarningBilBoard);
	_SR->LoadInfo("BossAtkWarning", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
}

void Boss_AttackWarning::Update()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();

	// ���b�V���t�B�[���h���擾
	MeshField* _MeshField = _Scene->GetGameObject<MeshField>();

	// �����͏�Ƀ��b�V���t�B�[���h�̏�ɂ���
	if (_MeshField != NULL)
	{
		m_Position.y = _MeshField->GetHeight(m_Position) + 0.5f;
	}

	GameObject::Update();
}
