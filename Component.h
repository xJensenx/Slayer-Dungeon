#pragma once
class Component
{
protected:
	class GameObject* m_GameObject = nullptr;
public:
	Component() {}
	virtual ~Component() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetGameObject(GameObject* _GameObject)
	{
		m_GameObject = _GameObject;
	}
};

