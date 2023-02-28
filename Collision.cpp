#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "RigidBody.h"
#include "Collision.h"

// ������
void Collision::Init()
{
	m_OffSet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isTrigger = false;
	isCollision = false;
}

// �I������
void Collision::Uninit()
{
	m_CollideObjects = NULL;
}

// �X�V����
void Collision::Update()
{
	// �e�V�[���̏�����ɓ����
	Scene* _Scene = Manager::GetScene();
	// �e�Q�[���I�u�W�F�N�g��RigidBody�̏�����ɓ����
	RigidBody* _Rigid = m_GameObject->GetComponent<RigidBody>();

	// IsTrigger���I���ɂ�����A�����o�������s��Ȃ��i�����蔻��܂����s���Ă��܂��j
	if (isTrigger)
	{
		return;
	}

	// �V�[���̒���Collision�̃R���|�l���g�t���Ă�Q�[���I�u�W�F�N�g�̏�����ɓ����
	std::vector<GameObject*> _GameObject = _Scene->GetGameObjectsWithComponent<Collision>();

	// ���n�ʂ̍����i�������j
	float GroundHeight = 0.5f;

	for (GameObject* gameobject : _GameObject)
	{
		// �����̃Q�[���I�u�W�F�N�g�Ɠ����������玟�̃��[�v�ɐi��
		if (gameobject == m_GameObject || gameobject->GetComponent<Collision>()->isTrigger)
		{
			continue;
		}

		// �Q�[���I�u�W�F�N�g�̃|�W�V���������
		D3DXVECTOR3 Pos = gameobject->GetPosition();
		// �Q�[���I�u�W�F�N�g�̃T�C�Y�����
		D3DXVECTOR3 Size = gameobject->GetSize();
		// �Q�[���I�u�W�F�N�g�̃X�P�[�������
		D3DXVECTOR3 Scale = gameobject->GetScale();
		// �����̃Q�[���I�u�W�F�N�g�̃|�W�V���������
		D3DXVECTOR3 SelfPos = m_GameObject->GetPosition();
		// �����̃Q�[���I�u�W�F�N�g�̃T�C�Y�����
		D3DXVECTOR3 SelfSize = m_GameObject->GetSize();
		// �����̃Q�[���I�u�W�F�N�g�̑O�̃t���[���̃|�W�V���������
		D3DXVECTOR3 SelfPrevPos = m_GameObject->GetPrevPos();
		// �����̃Q�[���I�u�W�F�N�g�̃X�P�[�������
		D3DXVECTOR3 SelfScale = m_GameObject->GetScale();

		// �����Ƒ���̃x�N�g�������
		D3DXVECTOR3 Dir = SelfPos - Pos;
		// �x�����O�ɂ���i�w�Ƃy�̋������v�Z���邽�߁j
		Dir.y = 0.0f;
		// �������v�Z����
		float Length = D3DXVec3Length(&Dir);

		// 
		if (Length < Scale.x)
		{
			if (_Rigid != NULL)
			{
				if (_Rigid->GetRigidType() == RigidBody::Dynamic)
				{
					if (SelfPos.y < Pos.y + (Scale.y * Size.y) - (Size.y / 2) + m_OffSet.y)
					{
						m_GameObject->SetInformation(
							D3DXVECTOR3(m_GameObject->GetPrevPos().x,
								m_GameObject->GetPosition().y,
								m_GameObject->GetPrevPos().z));
					}
					else
					{
						GroundHeight = Pos.y + (Scale.y * Size.y) - (Size.y / 2) + m_OffSet.y;
					}
				}
			}
		}
	}

	// �f�o�b�O�p�����蔻��
	if (_Rigid != NULL)
	{
		if (m_GameObject->GetPosition().y < GroundHeight + (m_GameObject->GetSize().y / 2) + m_OffSet.y && _Rigid->GetVelocity().y < 0.0f)
		{
			m_GameObject->SetInformation(D3DXVECTOR3(m_GameObject->GetPosition().x,
				GroundHeight + (m_GameObject->GetSize().y / 2) + m_OffSet.y, m_GameObject->GetPosition().z));

			_Rigid->SetVelocity(D3DXVECTOR3(_Rigid->GetVelocity().x, 0.0f, _Rigid->GetVelocity().z));
		}
	}
}

// �����̂̓����蔻��
bool Collision::CollisionBlock
(	D3DXVECTOR3 _SelfPos,		// �����̃|�W�V���� 
	D3DXVECTOR3 _SelfSize,		// �����̃T�C�Y
	D3DXVECTOR3 _SelfScale,		// �����̃X�P�[��
	D3DXVECTOR3 _ColPos, 		// ����̃|�W�V����
	D3DXVECTOR3 _ColSize,		// ����̃T�C�Y
	D3DXVECTOR3 _ColScale)		// ����̃X�P�[��
{
	float AxMax = _SelfPos.x + _SelfSize.x / 2;
	float AxMin = _SelfPos.x - _SelfSize.x / 2;
	float AyMax = _SelfPos.y + _SelfSize.y / 2;
	float AyMin = _SelfPos.y - _SelfSize.y / 2;
	float AzMax = _SelfPos.z + _SelfSize.z / 2;
	float AzMin = _SelfPos.z - _SelfSize.z / 2;

	float BxMax = _ColPos.x + _ColSize.x / 2;
	float BxMin = _ColPos.x - _ColSize.x / 2;
	float ByMax = _ColPos.y + _ColSize.y / 2;
	float ByMin = _ColPos.y - _ColSize.y / 2;
	float BzMax = _ColPos.z + _ColSize.z / 2;
	float BzMin = _ColPos.z - _ColSize.z / 2;

		// ��
	if ((AxMin < BxMax) &&
		// �E
		(AxMax > BxMin) &&
		// ��
		(AyMin < ByMax) &&
		// ��
		(AyMax > ByMin) &&
		// ���
		(AzMin < BzMax) &&
		// �O
		(AzMax > BzMin))
	{
		return true;
	}

	return false;
}

template<typename T>
inline bool Collision::isCollision2DBox()
{
	Scene* _Scene = Manager::GetScene();
	std::vector<T*> _CollideObj = _Scene->GetGameObjects<T>();

	for (auto object : _CollideObj)
	{
		auto C = object->GetComponent<Collision>();
		if (C != NULL)
		{
			D3DXVECTOR3 ObjectPos = object->GetPosition();
			D3DXVECTOR3 ObjectSize = object->GetSize();

			D3DXVECTOR3 SelfPos = m_GameObject->GetPosition();
			D3DXVECTOR3 SelfSize = m_GameObject->GetSize();

			float AxMax = SelfPos.x + (SelfSize.x / 2);
			float AxMin = SelfPos.x - (SelfSize.x / 2);
			float AyMax = SelfPos.y + (SelfSize.y / 2);
			float AyMin = SelfPos.y - (SelfSize.y / 2);

			float BxMax = ObjectPos.x + (ObjectSize.x / 2);
			float BxMin = ObjectPos.x - (ObjectSize.x / 2);
			float ByMax = ObjectPos.y + (ObjectSize.y / 2);
			float ByMin = ObjectPos.y - (ObjectSize.y / 2);

			if ((AxMin < BxMax) &&
				(AxMax > BxMin) &&
				(AyMin < ByMax) &&
				(AyMax > ByMin))
			{
				return true;
			}
		}
	}

	return false;
}