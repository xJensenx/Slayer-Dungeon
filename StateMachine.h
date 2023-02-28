#pragma once
class StateMachine
{
protected:
	class GameObject* m_Character;
	class AnimationManager* m_AnimationManager;

public:
	StateMachine() {}
	~StateMachine() {}

	void SetCharacter(class GameObject* Object) { m_Character = Object; }
	void SetAnimationManager(class AnimationManager* Manager) { m_AnimationManager = Manager; }
};

