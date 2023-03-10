#pragma once
#include "GameObject.h"
class MeshField :
    public GameObject
{
private:
	// メッシュフィールドの種類
	// ０：チュートリアル用、１：ゲーム用
	static int m_Type;

	static const int m_Horizontal = 21;
	static const int m_Vertical = 21;

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	static ID3D11ShaderResourceView* m_Texture;		// テキスチャー
	static ID3D11ShaderResourceView* m_NormalTexture; // ノーマルテクスチャ

	VERTEX_3D					m_Vertex[m_Horizontal][m_Vertical];

	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;

public:
	static void Load();
	static void Unload();
	static void SetMeshType(int T) { m_Type = T; }

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	float GetHeight(D3DXVECTOR3 Position);

};

