#pragma once
#include <list>
#include "Component.h"
#include "AnimationManager.h"

class GameObject
{
public:
	// �D��x
	enum Priority
	{
		FirstPri,
		SecondPri,
		ThirdPri,
		MaxPri
	};
protected:// �A�N�Z�X�w��q
	bool m_Destroy = false;				// �j�󂳂ꂽ���ǂ���
	D3DXVECTOR3 m_Position;				// ���W
	D3DXVECTOR3 m_PrevPos;				// �O�̍��W
	D3DXVECTOR3 m_Rotation;				// ��]
	D3DXVECTOR3 m_LocalPos;				// ���[�J�����W
	D3DXVECTOR3 m_LocalRot;				// ���[�J����]
	D3DXVECTOR3 m_LocalSca;				// ���[�J���X�P�[��
	D3DXQUATERNION m_Quaternion;		// 
	D3DXVECTOR3 m_Scale;				// �X�P�[��
	D3DXVECTOR3 m_Size;					// �T�C�Y
	D3DXVECTOR3 m_Target;				// �^�[�Q�b�g�i�J�����p�j
	bool m_ShadowDepth = false;			// �V���h�E�����邩�ǂ���
	bool m_isDamaged = false;			// �_���[�W���ꂽ���ǂ���
	bool m_Cinematic = false;			// �J�b�g�V�[�������ǂ���
	bool m_Pause = false;				// �|�[�Y���Ă��邩�ǂ���
	bool m_IgnorePause = false;			// �|�[�Y�𖳎����ē����邩�ǂ���

	// �e
	class GameObject* m_Parent = NULL;

	// �R���|�l���g
	std::list<class Component*> m_Component[MaxPri];
	// �q
	std::list<class GameObject*> m_Child;
	// �A�j���[�V�����}�l�[�W���[�i�A�j���[�V�������Ǘ�����j
	class AnimationManager* m_AnimationManager = NULL;
public:
	GameObject() {}				// �R���g���N�^
	virtual ~GameObject() {}	// �f�X�g���N�^�i���z�֐��j

	// ����������
	virtual void Init() = 0; // �������z�֐�

	// �_���[�W��^����ꂽ
	virtual void DealDamage(float Dmg)
	{
		if (m_isDamaged) return;

		m_isDamaged = true;
	}
	// �m�b�N�o�b�N�_���[�W��^����ꂽ
	virtual void KnockBackDamage(float Dmg, D3DXVECTOR3 Dir) {}

	// �I������
	virtual void Uninit()
	{
		for (int i = 0; i < MaxPri; i++)
		{
			for (auto c : m_Component[i])
			{
				c->Uninit();
				delete c;
			}
			// list�̒��g���������
			m_Component[i].clear();
		}
		for (auto c : m_Child)
		{
			c->Uninit();
			delete c;
		}
		m_Child.clear();

		if (m_AnimationManager != NULL)
		{
			m_AnimationManager->Uninit();
		}
	}
	// �X�V����
	virtual void Update()
	{
		if (m_AnimationManager != NULL)
		{
			m_AnimationManager->Update();
		}
		for (int i = 0; i < MaxPri; i++)
		{
			for (auto c : m_Component[i])
			{
				c->Update();
			}
		}
		for (auto c : m_Child)
		{
			c->Update();
		}

		if (m_Parent != NULL)
		{
			m_Position = m_Parent->m_Position + m_LocalPos;
			m_Rotation = m_Parent->m_Rotation + m_LocalRot;
		}

		m_PrevPos = m_Position;
	}
	// �`�揈��
	virtual void Draw()
	{
		for (int i = 0; i < MaxPri; i++)
		{
			for (auto c : m_Component[i])
			{
				c->Draw();
			}
		}
		for (auto c : m_Child)
		{
			c->Draw();
		}
	}

	// �R���|�[�l���g��ǉ�
	template<typename T>
	T* AddComponent(Priority _Pri)
	{
		T* _Component = new T();
		_Component->SetGameObject(this);
		_Component->Init();
		m_Component[_Pri].push_back(_Component);

		return _Component;
	}

	// �A�j���[�V�����}�l�[�W���[��ǉ�
	template<typename T>
	T* AddAnimationManager()
	{
		T* _AnimationManager = new T();
		_AnimationManager->SetGameObject(this);
		AnimModelManager* GameObjectAnim = GetComponent<AnimModelManager>();
		_AnimationManager->SetAnimModel(GameObjectAnim);
		_AnimationManager->Init();
		m_AnimationManager = _AnimationManager;

		return _AnimationManager;
	}

	// �A�j���[�V�����}�l�[�W���[���擾
	template<typename T>
	T* GetAnimationManager()
	{
		if (typeid(*m_AnimationManager) == typeid(T))
		{
			return (T*)m_AnimationManager;
		}

		return NULL;
	}

	// �R���|�[�l���g���擾
	template<typename T>
	T* GetComponent()
	{
		for (int i = 0; i < MaxPri; i++)
		{
			for (Component* object : m_Component[i])
			{
				if (typeid(*object) == typeid(T)) // �^�𒲂ׂ�iRTTI���I�^���j
				{
					return (T*)object;
				}
			}
		}
		return NULL;
	}

	// �q��ǉ�
	template<typename T>
	T* AddChild()
	{
		T* _Child = new T();
		_Child->SetParent(this);
		_Child->Init();
		m_Child.push_back(_Child);

		return _Child;
	}
	
	// �q���擾
	template<typename T>
	T* GetChild()
	{
		for (GameObject* object : m_Child)
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	// �j�󂳂�邩�ǂ���
	virtual void SetDestroy() { m_Destroy = true; }

	// YawPitchRoll
	// Forward���擾
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		
		D3DXMatrixRotationYawPitchRoll(&rot, 
			m_Rotation.y, m_Rotation.x, m_Rotation.z);
		
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	// Right���擾
	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, 
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}
	// Up���擾
	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, 
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
	}

	// Quaternion
	// Forward���擾
	D3DXVECTOR3 GetQuaternionForward()
	{
		D3DXMATRIX rot;

		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 Forward;
		Forward.x = rot._31;
		Forward.y = rot._32;
		Forward.z = rot._33;

		return Forward;
	}
	// Right���擾
	D3DXVECTOR3 GetQuaternionRight()
	{
		D3DXMATRIX rot;

		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 Right;
		Right.x = rot._11;
		Right.y = rot._12;
		Right.z = rot._13;

		return Right;
	}
	// Up���擾
	D3DXVECTOR3 GetQuaternionUp()
	{
		D3DXMATRIX rot;

		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 Up;
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;

		return Up;
	}

	// �j�󂳂�邩�ǂ����̏���
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else 
		{
			return false;
		}
	}

	// �j�󂳂ꂽ���擾
	bool GetDestroy() { return m_Destroy; }
	// Cinematic���[�h�ɓ����Ă邩�ǂ���
	bool GetCinematicMode() { return m_Cinematic; }
	// �e���Ă��邩�ǂ���
	bool GetShadowDepth() { return m_ShadowDepth; }
	// �O�̍��W���擾
	D3DXVECTOR3 GetPrevPos() { return m_PrevPos; }
	// ���̍��W���擾
	D3DXVECTOR3 GetPosition() { return m_Position; }
	// ��]���擾
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	// �^�[�Q�b�g���擾
	D3DXVECTOR3 GetTargetPos() { return m_Target; }
	// �N�H�[�^�j�I�����擾
	D3DXQUATERNION GetQuaternion() { return m_Quaternion; }
	// �X�P�[�����擾
	D3DXVECTOR3 GetScale() { return m_Scale; }
	// �T�C�Y���擾
	D3DXVECTOR3 GetSize() { return m_Size; }
	// X��OBB���擾
	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		if (m_Size.x > 0.0f)
		{
			return vx * (m_Size.x / 2);
		}
		else
		{
			return vx * 0.5f;
		}
	}
	// Y��OBB���擾
	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vy;
		vy.x = world._21;
		vy.y = world._22;
		vy.z = world._23;

		if (m_Size.y > 0.0f)
		{
			return vy * (m_Size.y / 2);
		}
		else
		{
			return vy * 0.5f;
		}
	}
	// Z��OBB���擾
	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		if (m_Size.z > 0.0f)
		{
			return vz * (m_Size.z / 2);
		}
		else
		{
			return vz * 0.5f;
		}
	}

	// �|�W�V����
	void SetInformation(D3DXVECTOR3 Pos) { m_Position = Pos; }
	// �|�W�V�����A��]
	void SetInformation(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot) { m_Position = Pos, m_Rotation = Rot; }
	// �|�W�V�����A��]�A�X�P�[��
	void SetInformation(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Sca) { m_Position = Pos, m_Rotation = Rot, m_Scale = Sca; }

	// ���W��ݒu
	void SetPosition(D3DXVECTOR3 Pos) { m_Position = Pos; }
	// ��]��ݒu�iYaw,Pitch,Roll�̂��߁AMath::PI() = 180���j
	void SetRotation(D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	// �X�P�[����ݒu
	void SetScale(D3DXVECTOR3 Sca) { m_Scale = Sca; }
	// �T�C�Y��ݒu
	void SetSize(D3DXVECTOR3 Siz) { m_Size = Siz; }

	// �q�I�u�W�F�N�g�̂��߁i�f�o�b�O���j
	void SetLocalPos(D3DXVECTOR3 Pos) { m_LocalPos = Pos; }
	void SetLocalRot(D3DXVECTOR3 Rot) { m_LocalRot = Rot; }

	// �e�I�u�W�F�N�g��ݒu�i�f�o�b�O���j
	void SetParent(GameObject* Parent) { m_Parent = Parent; }
	// �J�����̃^�[�Q�b�g�̐ݒu
	void SetTarget(D3DXVECTOR3 Tar) { m_Target = Tar; }
	// �e�����邩�ǂ���
	void SetShadowDepth(bool ShadowDepth) { m_ShadowDepth = ShadowDepth; }	
	// �J�b�g�V�[���ɓ����Ă���̏�Ԃ�ݒu
	void SetCinematicMode(bool Mode) { m_Cinematic = Mode; }
	// �|�[�Y����
	void SetPause(bool Pause) { m_Pause = Pause; }
	// �|�[�Y�𖳎�����̂��Z�b�g����
	void SetIgnorePause(bool Ignore) { m_IgnorePause = Ignore; }
	// Quaternion���Z�b�g
	void SetQuaternion(D3DXQUATERNION Qua) { m_Quaternion = Qua; }
	// isDamaged���Z�b�g
	void SetisDamaged(bool Damage) { m_isDamaged = Damage; }
	

};