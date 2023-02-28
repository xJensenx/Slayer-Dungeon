#pragma once
#include <vector>


// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// ���f���\����
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

	// �S�Ă̒��_���W���擾����Q�b�^�[
	std::vector<D3DXVECTOR3> GetAllVertexPosition() { return m_VertexPosition; }
};