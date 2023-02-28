#pragma once
#include "GameObject.h"
class MeshField :
    public GameObject
{
private:
	// ���b�V���t�B�[���h�̎��
	// �O�F�`���[�g���A���p�A�P�F�Q�[���p
	static int m_Type;

	static const int m_Horizontal = 21;
	static const int m_Vertical = 21;

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	static ID3D11ShaderResourceView* m_Texture;		// �e�L�X�`���[
	static ID3D11ShaderResourceView* m_NormalTexture; // �m�[�}���e�N�X�`��

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

