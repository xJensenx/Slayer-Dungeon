#pragma once
#include <list>
#include "FadeSceneType.h"

class Fade
{
public:
	//enum SceneType
	//{
	//	NoScene = 0,
	//	TitleScene,
	//	GameScene,
	//	ResultScene,
	//	Test,
	//	Loading,
	//	Quit,
	//	LoadingTitle,
	//	MaxScene
	//};

	void Init();
	void Uninit();
	void Update();
	void Draw();

	template <typename T>
	static void SetFade()
	{
		if (m_isFade)
		{
			return;
		}
		m_isFade = true;
		m_Fade = 0.0f;
		if (m_SceneType != NULL)
		{
			delete m_SceneType;
			m_SceneType = NULL;
		}

		T* NextScene = new T();
		m_SceneType = NextScene;
	}
	static float GetFade()
	{
		return m_Fade;
	}

	static bool GetisFade()
	{
		return m_isFade;
	}

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

	static float m_Fade;
	static bool m_isFade;
	static class FadeSceneType* m_SceneType;
	//static SceneType m_SceneType;
};