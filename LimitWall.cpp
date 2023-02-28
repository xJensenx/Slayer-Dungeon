#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "LimitWall.h"
#include "Player.h"

void LimitWall::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(5.0f, 20.0f, 20.0f);
	
	// ���f��
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	_MR->SetModel("LimitWall", ModelRenderer::UnlitType);
	m_Size = _MR->GetModelSize("LimitWall");
	m_Size = D3DXVECTOR3(1.0f, 10.0f, 10.0f);
}

void LimitWall::Update()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// �v���C���[�擾
	Player* _Player = _Scene->GetGameObject<Player>();
	// �v���C���[��NULL�̏�Ԃ���return����
	if (_Player == NULL) return;

	// ���E�ǂ̐ݒu
	if (_Player->GetPosition().x < -49.0f)
	{
		_Player->SetPosition(D3DXVECTOR3(-49.0f, _Player->GetPosition().y, _Player->GetPosition().z));
	}
	if (_Player->GetPosition().x > 49.0f)
	{
		_Player->SetPosition(D3DXVECTOR3(49.0f, _Player->GetPosition().y, _Player->GetPosition().z));
	}
	if (_Player->GetPosition().z < -49.0f)
	{
		_Player->SetPosition(D3DXVECTOR3(_Player->GetPosition().x, _Player->GetPosition().y, -49.0f));
	}
	if (_Player->GetPosition().z > 49.0f)
	{
		_Player->SetPosition(D3DXVECTOR3(_Player->GetPosition().x, _Player->GetPosition().y, 49.0f));
	}
	

	GameObject::Update();
}
