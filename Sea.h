#pragma once
#include "Component.h"
class Sea : public GameObject
{
private:
	static const int m_Horizontal = 21;
	static const int m_Vertical = 21;
	
	D3DXVECTOR2 m_Direction;
	float m_Amplitude;
	float m_WaveLength;

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11Buffer*				m_IndexBuffer = NULL;
	static ID3D11ShaderResourceView*	m_Texture;		// テキスチャー
	static ID3D11ShaderResourceView* m_TextureNormal;	// ノーマルテキスチャー
	static ID3D11ShaderResourceView* m_SecondNormal;

	VERTEX_3D					m_Vertex[m_Horizontal][m_Vertical];
	float						m_Time[m_Horizontal][m_Vertical];

	static ID3D11VertexShader*			m_VertexShader;
	static ID3D11PixelShader*			m_PixelShader;
	static ID3D11InputLayout*			m_VertexLayout;

public:
	static void Load();
	static void Unload();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	float GetHeight(D3DXVECTOR3 Position);
};

