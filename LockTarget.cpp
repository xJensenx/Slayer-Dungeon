#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "LockTarget.h"
#include "Camera.h"

void LockTarget::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �T�C�Y�w��
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	
	// �X�v���C�g�R���|�[�l���g�ǉ�
	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("LockTarget", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_SC->SetSpriteType(SpriteComponent::BilBoard);
	_SC->SetVisibility(false);
}

void LockTarget::Update()
{
	// �V�[���擾
	Scene* _Scene = Manager::GetScene();
	// SpriteComponent���擾
	SpriteComponent* _SC = GetComponent<SpriteComponent>();
	// �J�����擾
	Camera* _Cam = _Scene->GetGameObject<Camera>();

	// ���b�N���Ă���ڕW�����݂��Ă����
	if (m_LockOnTarget != NULL)
	{
		// ������悤�ɂ���
		_SC->SetVisibility(true);

		// �J������Backward�擾
		D3DXVECTOR3 CamBackward = _Cam->GetForward() * -1;

		// ���b�N���Ă���ڕW�̍��W�����
		D3DXVECTOR3 _LockPos = m_LockOnTarget->GetPosition();
		// �A�j���[�V�������f���̍��W�͑��̕���������Y�𒲐����܂�
		_LockPos.y = m_LockOnTarget->GetPosition().y + m_LockOnTarget->GetSize().y / 2;
		// �G���O�ɏo��
		_LockPos.x += CamBackward.x * 0.5f;
		_LockPos.z += CamBackward.z * 0.5f;

		// ���W�𒲐����܂�
		m_Position = _LockPos;
	}
	else
	{
		// ���b�N���Ă��鑊�肪���Ȃ����͌����Ȃ��悤�ɂ���
		_SC->SetVisibility(false);
	}

	GameObject::Update();
}
