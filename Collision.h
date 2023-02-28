#pragma once
#include <list>
#include "manager.h"
#include "Component.h"
class Collision : public Component
{
public:
	enum ColliderType
	{
		BoxCollider = 0,
		SphereCollider
	};
	GameObject* m_CollideObjects = NULL;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() {}

	bool CollisionBlock(D3DXVECTOR3 _SelfPos, D3DXVECTOR3 _SelfSize,D3DXVECTOR3 _SelfScale, D3DXVECTOR3 _ColPos, D3DXVECTOR3 _ColSize,D3DXVECTOR3 _ColScale);

	void SetColliderType(ColliderType _Collider) { m_Collider = _Collider; }
	void SetTrigger(bool _Trigger) { isTrigger = _Trigger; }
	void SetOffSet(D3DXVECTOR3 _OffSet) { m_OffSet = _OffSet; }

	template <typename T>
	bool isCollisionWith()
	{
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> _CollideObj = _Scene->GetGameObjects<T>();

		for (auto object : _CollideObj)
		{
			auto C = object->GetComponent<Collision>();
			if (C != NULL)
			{
				D3DXVECTOR3 Pos = object->GetPosition();
				D3DXVECTOR3 Size = object->GetSize();
				D3DXVECTOR3 SelfPos = m_GameObject->GetPosition();
				D3DXVECTOR3 SelfSize = m_GameObject->GetSize();
				D3DXVECTOR3 Direction = SelfPos - Pos;
				float Length = D3DXVec3Length(&Direction);
				if (Length < 2.0f)
				{
					m_CollideObjects = object;
					return true;
				}
				//if (CollisionBlock(SelfPos, SelfSize, Pos, Size))
				//{
				//	m_CollideObjects = object;
				//	return true;
				//}

			}
		}
		return false;
	}

	template <typename T>
	bool isCollision2DBox();

private:
	D3DXVECTOR3 m_OffSet;
	bool isTrigger;
	bool isCollision;
	ColliderType m_Collider = BoxCollider;
};
