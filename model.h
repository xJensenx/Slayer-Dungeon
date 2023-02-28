#pragma once
#include <vector>


// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};





class Model
{
private:
	D3DXVECTOR3 m_ModelSize;

	std::vector<D3DXVECTOR3> m_VertexPosition;

	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;

	bool m_WireFrame = false;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

public:

	void Draw(bool isMaterialUse);

	void Load( const char *FileName );
	void Unload();
	D3DXVECTOR3 GetModelSize() { return m_ModelSize; }

	void SetWireFrame(bool WireFrame)
	{
		m_WireFrame = WireFrame;
	}

	// 全ての頂点座標を取得するゲッター
	std::vector<D3DXVECTOR3> GetAllVertexPosition() { return m_VertexPosition; }
};