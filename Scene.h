#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "GameObject.h"

//bool Z_Sort(GameObject* V1, GameObject* V2)
//{
//	D3DXVECTOR3 V1Pos = V1->GetPosition();
//	D3DXVECTOR3 V2Pos = V2->GetPosition();
//
//	if (V1Pos.z > V2Pos.z)
//	{
//		return true;
//	}
//
//	return false;
//}

class Scene
{
public:
	enum LayerMask {
		Layer_CameraLayer = 0,
		Layer_ObjectLayer,
		Layer_EffectLayer,
		Layer_UILayer,
		Layer_AboveUILayer,
		Layer_MAX,
	};

protected:
	std::list<GameObject*> m_GameObject[LayerMask::Layer_MAX]; // STLのリスト構造
	std::list<GameObject*> m_PauseUI;

public:

	Scene() {}
	virtual ~Scene() {}
	
	virtual void Init() = 0; // 純粋仮想関数

	template <typename T> // テンプレート関数
	T* AddGameObject(LayerMask _Layer)
	{
		T* GameObject = new T();
		GameObject->Init();
		m_GameObject[_Layer].push_back(GameObject);

		return GameObject;
	}

	template <typename T>
	T* AddPauseUI()
	{
		T* PauseUI = new T();
		PauseUI->Init();
		m_PauseUI.push_back(PauseUI);

		return PauseUI;
	}

	template <typename T>
	T* GetGameObject()
	{
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T)) // 型を調べる（RTTI動的型情報）
				{
					return (T*)object;
				}
			}
		}
		return NULL;
	}

	template <typename T>
	T* GetPauseUI()
	{
		for (GameObject* object : m_PauseUI)
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}

		return NULL;
	}

	template <typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects; // STLの配列
		// 安全なやり方
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))
				{
					objects.push_back((T*)object);
				}
			}
		}
		return objects;

		// 危険なやり方 GetGameObjects(int Layer)
		// m_GameObject[Layer]
		// これだと違うLayerにしたら当たり判定が当たらない	
	}

	template <typename T>
	std::vector<T*> GetAllPauseUI()
	{
		std::vector<T*> PauseUI;
		for (GameObject* P : m_PauseUI)
		{
			if (typeid(*P) == typeid(T))
			{
				PauseUI.push_back((T*)P);
			}
		}

		return PauseUI;
	}

	template<typename T>
	std::vector<GameObject*> GetGameObjectsWithComponent()
	{
		std::vector<GameObject*> objects;
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				Component* component = object->GetComponent<T>();
				if (component != NULL)
				{
					objects.push_back((GameObject*)object);
				}
			}
		}
		return objects;
	}

	virtual void Uninit()
	{

		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}

		for (GameObject* pauseUI : m_PauseUI)
		{
			pauseUI->Uninit();
			delete pauseUI;
		}

		m_PauseUI.clear();
	}

	virtual void UpdatePauseUI()
	{
		for (GameObject* pauseUI : m_PauseUI)
		{
			pauseUI->Update();
		}

		m_PauseUI.remove_if([](GameObject* pauseUI)
		{ return pauseUI->Destroy(); });

	}

	virtual void Update()
	{
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i]) // 範囲forループ
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object)
				{ return object->Destroy(); });
			// ランダ式
		}
	}
	virtual void DrawPauseUI()
	{
		for (GameObject* pauseUI : m_PauseUI)
		{
			pauseUI->Draw();
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			// Zソート
			//m_GameObject[i].sort(Z_Sort);

			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}

	}
	virtual void DrawShadow()
	{
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (object->GetShadowDepth())
				{
					object->Draw();
				}
			}
		}
	}

	void PauseGame(bool Pause)
	{
		for (int i = 0; i < LayerMask::Layer_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->SetPause(Pause);
			}
		}
	}
};