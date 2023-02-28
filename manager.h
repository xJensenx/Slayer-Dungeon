#pragma once
#include "Scene.h"

class Manager
{
public:
	enum SkillNumber
	{
		NoSkill = 0,
		Skill01 = 1,
		Skill02,
		Skill03,
		Skill04,
		Skill05,
		Skill06,
		Skill07,
		Skill08,
		Skill09
	};
private:
	static class Scene* m_Scene;	// これも前方宣言の一つ
	static class GameObject* m_MouseCursor;

	static bool m_Pause;

	// 制限時間内にポーズするため
	static float m_PauseTime;

	static bool m_LimitedPause;

	// スキル用変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// スキル種類
	static SkillNumber m_SkillType[3];
	// 
	
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝


public:
	static Manager* getInstance() {
		return s_pManager;
	}

	static void Create();
	static void Destroy();


	static void Init();
	static void Uninit();

	static void Update();
	static void Draw();

	static void LimitedPauseEvent();
	
	static void Pause(bool pPause)
	{
		m_Pause = pPause;
	}

	static void PauseGame(bool Pause)
	{
		if (m_Scene)
		{
			m_Scene->PauseGame(Pause);
		}
	}

	static void PauseFor(float PauseTime)
	{
		m_LimitedPause = true;
		m_PauseTime = PauseTime * Time;
		PauseGame(true);
	}

	static void SetSkillType(int No, SkillNumber Type)
	{
		m_SkillType[No] = Type;
	}

	static bool GetPause() { return m_Pause; }

	static SkillNumber GetSkillType(int No)
	{
		return m_SkillType[No];
	}

	static class Scene* GetScene() { return m_Scene; }
	static const int Time = 60;

	template <typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = new T();
		m_Scene->Init();
	}

	template <typename T>
	static bool CheckScene()
	{
		if (m_Scene)
		{
			if (typeid(*m_Scene) == typeid(T))
			{
				return true;
			}
		}

		return false;
	}

	template <typename T>
	static T* GetSceneType()
	{
		if (m_Scene)
		{
			if (typeid(*m_Scene) == typeid(T))
			{
				return (T*)m_Scene;
			}
		}

		return NULL;
	}

protected:
	static Manager *s_pManager;
	static class Fade* m_Fade;
	Manager();
	Manager(const Manager& src);
	Manager& operator = (const Manager& src);
};