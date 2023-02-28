#pragma once
#include "Math.h"

class PhysicsCast
{
private:
	class GameObject* m_CollideObj = NULL;
public:
	PhysicsCast() {}
	~PhysicsCast() {}

	GameObject* GetColldeObj() { return m_CollideObj; }

	template <typename T>
	static PhysicsCast* PhysicRayCast(D3DXVECTOR3 Origin, D3DXVECTOR3 Dir, float Length)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			D3DXVECTOR3 objPos = object->GetPosition();
			D3DXVECTOR3 objRot = object->GetRotation();
			D3DXVECTOR3 objSca = object->GetScale();
			D3DXVECTOR3 objSiz = object->GetSize();
			D3DXVECTOR3 RayLength = Origin + (Dir * Length);
			if (RayLength.x > objPos.x - (objSca.x * objSiz.x) + (objSiz.x / 2) &&
				RayLength.x < objPos.x + (objSca.x * objSiz.x) - (objSiz.x / 2) &&
				RayLength.y > objPos.y - (objSca.y * objSiz.y) + (objSiz.y / 2) &&
				RayLength.y < objPos.y + (objSca.y * objSiz.y) - (objSiz.y / 2) &&
				RayLength.z > objPos.z - (objSca.z * objSiz.z) + (objSiz.z / 2) &&
				RayLength.z < objPos.z + (objSca.z * objSiz.z) - (objSiz.z / 2))
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	// ボックスキャスト
	template <typename T>
	static PhysicsCast* PhysicBoxCast(D3DXVECTOR3 Origin, D3DXVECTOR3 Size)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			D3DXVECTOR3 objPos = object->GetPosition();
			D3DXVECTOR3 objSiz = object->GetSize();

			if ((objPos.x + (objSiz.x / 2) > Origin.x - (Size.x / 2)) &&
				(objPos.x - (objSiz.x / 2) < Origin.x + (Size.x / 2)) &&
				(objPos.y + (objSiz.y / 2) > Origin.y - (Size.y / 2)) &&
				(objPos.y - (objSiz.y / 2) < Origin.y + (Size.y / 2)) &&
				(objPos.z + (objSiz.z / 2) > Origin.z - (Size.z / 2)) &&
				(objPos.z - (objSiz.z / 2) < Origin.z + (Size.z / 2)))
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	// ボックスキャスト
	template <typename T>
	static std::vector<PhysicsCast*> AllPhysicBoxCast(D3DXVECTOR3 Origin, D3DXVECTOR3 Size)
	{
		std::vector<PhysicsCast*> _Phy;
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			D3DXVECTOR3 objPos = object->GetPosition();
			D3DXVECTOR3 objSiz = object->GetSize();

			if ((objPos.x + (objSiz.x / 2) > Origin.x - (Size.x / 2)) &&
				(objPos.x - (objSiz.x / 2) < Origin.x + (Size.x / 2)) &&
				(objPos.y + (objSiz.y / 2) > Origin.y - (Size.y / 2)) &&
				(objPos.y - (objSiz.y / 2) < Origin.y + (Size.y / 2)) &&
				(objPos.z + (objSiz.z / 2) > Origin.z - (Size.z / 2)) &&
				(objPos.z - (objSiz.z / 2) < Origin.z + (Size.z / 2)))
			{
				PhysicsCast* NewPhy = new PhysicsCast();
				NewPhy->m_CollideObj = object;
				_Phy.push_back(NewPhy);
			}
		}

		return _Phy;
	}

	template <typename T>
	static PhysicsCast* PhysicBoxCast(D3DXVECTOR3 Origin, D3DXVECTOR3 Size, GameObject* IgnoreObj)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			if (object == IgnoreObj) { continue; }

			D3DXVECTOR3 objPos = object->GetPosition();
			D3DXVECTOR3 objSiz = object->GetSize();

			if ((objPos.x + (objSiz.x / 2) > Origin.x - (Size.x / 2)) &&
				(objPos.x - (objSiz.x / 2) < Origin.x + (Size.x / 2)) &&
				(objPos.y + (objSiz.y / 2) > Origin.y - (Size.y / 2)) &&
				(objPos.y - (objSiz.y / 2) < Origin.y + (Size.y / 2)) &&
				(objPos.z + (objSiz.z / 2) > Origin.z - (Size.z / 2)) &&
				(objPos.z - (objSiz.z / 2) < Origin.z + (Size.z / 2)))
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	template <typename T>
	static PhysicsCast* PhysicsSphereCast(D3DXVECTOR3 Origin, float Size)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			D3DXVECTOR3 objPos = object->GetPosition();
			float objSize = object->GetSize().x;

			if (Math::Distance(Origin, objPos) <= Size + objSize)
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	template <typename T>
	static PhysicsCast* PhysicsSphereCast(D3DXVECTOR3 Origin, float Size, GameObject* IgnoreObj)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			if (object == IgnoreObj) { continue; }

			D3DXVECTOR3 objPos = object->GetPosition();
			
			if (Math::Distance(Origin, objPos) <= Size)
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	// マウス用
	template <typename T>
	static PhysicsCast* MouseRayCast(D3DXVECTOR2 MousePos)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetGameObjects<T>();

		for (auto object : GameObjects)
		{
			D3DXVECTOR3 objPos = object->GetPosition();
			D3DXVECTOR3 objSiz = object->GetSize();

			if (objPos.x + (objSiz.x / 2) > MousePos.x &&
				objPos.x - (objSiz.x / 2) < MousePos.x &&
				objPos.y + (objSiz.y / 2) > MousePos.y &&
				objPos.y - (objSiz.y / 2) < MousePos.y)
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	// マウス用（ポーズメニュー）
	template <typename T>
	static PhysicsCast* MouseRayCastPauseUI(D3DXVECTOR2 MousePos)
	{
		PhysicsCast* _Phy = new PhysicsCast();
		Scene* _Scene = Manager::GetScene();
		std::vector<T*> GameObjects = _Scene->GetAllPauseUI<T>();

		for (auto object : GameObjects)
		{
			D3DXVECTOR3 objPos = object->GetPosition();
			D3DXVECTOR3 objSiz = object->GetSize();

			if (objPos.x + (objSiz.x / 2) > MousePos.x &&
				objPos.x - (objSiz.x / 2) < MousePos.x &&
				objPos.y + (objSiz.y / 2) > MousePos.y &&
				objPos.y - (objSiz.y / 2) < MousePos.y)
			{
				_Phy->m_CollideObj = object;
				return _Phy;
			}
		}

		return NULL;
	}

	//template <typename T>
	//static PhysicsCast* OBBPhysicBoxCast(D3DXVECTOR3 Origin, D3DXVECTOR3 Size)
	//{
	//	PhysicsCast* _Phy = new PhysicsCast();
	//	Scene* _Scene = Manager::GetScene();
	//	std::vector<T*> _GameObjects = _Scene->GetGameObjects<T>();

	//	for (auto object : _GameObjects)
	//	{
	//		D3DXVECTOR3 Pos = object->GetPosition();
	//		D3DXVECTOR3 Dir = Origin - Pos;

	//		D3DXVECTOR3 ObjectOBBX, ObjectOBBY, ObjectOBBZ;
	//		float ObjectOBBLengthX, ObjectOBBLengthY, ObjectOBBLengthZ;

	//		D3DXVECTOR3 SelfOBBX, SelfOBBY, SelfOBBZ;
	//		float SelfOBBLengthX, SelfOBBLengthY, SelfOBBLengthZ;

	//		ObjectOBBX = object->GetObbX();
	//		ObjectOBBLengthX = D3DXVec3Length(&ObjectOBBX);
	//		ObjectOBBX /= ObjectOBBLengthX;

	//		ObjectOBBY = object->GetObbY();
	//		ObjectOBBLengthY = D3DXVec3Length(&ObjectOBBY);
	//		ObjectOBBY /= ObjectOBBLengthY;

	//		ObjectOBBZ = object->GetObbZ();
	//		ObjectOBBLengthZ = D3DXVec3Length(&ObjectOBBZ);
	//		ObjectOBBZ /= ObjectOBBLengthZ;

	//		SelfOBBX = m_GameObject->GetObbX();
	//		SelfOBBLengthX = D3DXVec3Length(&SelfOBBX);
	//		SelfOBBX /= SelfOBBLengthX;

	//		SelfOBBY = m_GameObject->GetObbY();
	//		SelfOBBLengthY = D3DXVec3Length(&SelfOBBY);
	//		SelfOBBY /= SelfOBBLengthY;

	//		SelfOBBZ = m_GameObject->GetObbZ();
	//		SelfOBBLengthZ = D3DXVec3Length(&SelfOBBZ);
	//		SelfOBBZ /= SelfOBBLengthZ;


	//		float lenX, lenY, lenZ;
	//		lenX = D3DXVec3Dot(&ObjectOBBX, &Dir);
	//		lenY = D3DXVec3Dot(&ObjectOBBY, &Dir);
	//		lenZ = D3DXVec3Dot(&ObjectOBBZ, &Dir);

	//		if (fabs(lenX) < ObjectOBBLengthX + SelfOBBLengthX && fabs(lenY) < ObjectOBBLengthY + SelfOBBLengthY && fabs(lenZ) < ObjectOBBLengthZ + SelfOBBLengthZ)
	//		{
	//			return true;
	//		}

	//	}
	//}


};

