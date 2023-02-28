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
	std::list<GameObject*> m_GameObject[LayerMask::Layer_MAX]; // STL�̃��X�g�\��
	std::list<GameObject*> m_PauseUI;

public:

	Scene() {}
	virtual ~Scene() {}
	
	virtual void Init() = 0; // �������z�֐�

	template <typename T> // �e���v���[�g�֐�
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
				if (typeid(*object) == typeid(T)) // �^�𒲂ׂ�iRTTI���I�^���j
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
		std::vector<T*> objects; // STL�̔z��
		// ���S�Ȃ���
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

		// �댯�Ȃ��� GetGameObjects(int Layer)
		// m_GameObject[Layer]
		// ���ꂾ�ƈႤLayer�ɂ����瓖���蔻�肪������Ȃ�	
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
			for (GameObject* object : m_GameObject[i]) // �͈�for���[�v
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object)
				{ return object->Destroy(); });
			// �����_��
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
			// Z�\�[�g
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