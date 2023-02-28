#pragma once
#include "Component.h"
class CollisionOBB : public Component
{
private:
	bool m_Trigger = true;
public:
	GameObject* m_CollideObject = NULL;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	// OBB‚Æ“_‚Ì“–‚½‚è”»’è
	template <typename T>
	bool isCollisionWith()
	{
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> _CollideObj = _Scene->GetGameObjects<T>();

		for (auto object : _CollideObj)
		{
			auto C = object->GetComponent<CollisionOBB>();
			if (C != NULL)
			{
				D3DXVECTOR3 Pos = object->GetPosition();
				D3DXVECTOR3 Dir = m_GameObject->GetPosition() - Pos;

				D3DXVECTOR3 obbX, obbY, obbZ;
				float obbLenX, obbLenY, obbLenZ;

				obbX = object->GetObbX();
				obbLenX = D3DXVec3Length(&obbX);
				obbX /= obbLenX;

				obbY = object->GetObbY();
				obbLenY = D3DXVec3Length(&obbY);
				obbY /= obbLenY;

				obbZ = object->GetObbZ();
				obbLenZ = D3DXVec3Length(&obbZ);
				obbZ /= obbLenZ;

				float lenX, lenY, lenZ;
				lenX = D3DXVec3Dot(&obbX, &Dir);
				lenY = D3DXVec3Dot(&obbY, &Dir);
				lenZ = D3DXVec3Dot(&obbZ, &Dir);

				if (fabs(lenX) < obbLenX && fabs(lenY) < obbLenY && fabs(lenZ) < obbLenZ)
				{
					m_CollideObject = object;
					return true;
				}
			}
		}

		m_CollideObject = NULL;
		return false;
	}

	// OBB‘ÎOBB‚Ì“–‚½‚è”»’è
	template <typename T>
	bool isOBBCollisionWithOBB()
	{
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> _CollideObj = _Scene->GetGameObjects<T>();

		for (auto object : _CollideObj)
		{
			if (object == m_GameObject)
			{
				continue;
			}
			auto C = object->GetComponent<CollisionOBB>();
			if (C != NULL)
			{
				D3DXVECTOR3 Pos = object->GetPosition();
				D3DXVECTOR3 Dir = m_GameObject->GetPosition() - Pos;

				D3DXVECTOR3 ObjectOBBX, ObjectOBBY, ObjectOBBZ;
				float ObjectOBBLengthX, ObjectOBBLengthY, ObjectOBBLengthZ;

				D3DXVECTOR3 SelfOBBX, SelfOBBY, SelfOBBZ;
				float SelfOBBLengthX, SelfOBBLengthY, SelfOBBLengthZ;

				ObjectOBBX = object->GetObbX();
				ObjectOBBLengthX = D3DXVec3Length(&ObjectOBBX);
				ObjectOBBX /= ObjectOBBLengthX;

				ObjectOBBY = object->GetObbY();
				ObjectOBBLengthY = D3DXVec3Length(&ObjectOBBY);
				ObjectOBBY /= ObjectOBBLengthY;

				ObjectOBBZ = object->GetObbZ();
				ObjectOBBLengthZ = D3DXVec3Length(&ObjectOBBZ);
				ObjectOBBZ /= ObjectOBBLengthZ;

				SelfOBBX = m_GameObject->GetObbX();
				SelfOBBLengthX = D3DXVec3Length(&SelfOBBX);
				SelfOBBX /= SelfOBBLengthX;

				SelfOBBY = m_GameObject->GetObbY();
				SelfOBBLengthY = D3DXVec3Length(&SelfOBBY);
				SelfOBBY /= SelfOBBLengthY;

				SelfOBBZ = m_GameObject->GetObbZ();
				SelfOBBLengthZ = D3DXVec3Length(&SelfOBBZ);
				SelfOBBZ /= SelfOBBLengthZ;


				float lenX, lenY, lenZ;
				lenX = D3DXVec3Dot(&ObjectOBBX, &Dir);
				lenY = D3DXVec3Dot(&ObjectOBBY, &Dir);
				lenZ = D3DXVec3Dot(&ObjectOBBZ, &Dir);

				if (fabs(lenX) < ObjectOBBLengthX + SelfOBBLengthX && fabs(lenY) < ObjectOBBLengthY + SelfOBBLengthY && fabs(lenZ) < ObjectOBBLengthZ + SelfOBBLengthZ)
				{
					return true;
				}
			}
		}
		return false;

	}

	void SetTrigger(bool _Trigger) { m_Trigger = _Trigger; }
};

