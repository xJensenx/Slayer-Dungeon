#pragma once
#include "Component.h"
class SpriteComponent :
    public Component
{
public:
	enum SpriteType
	{
		None = 0,
		BilBoard,
		AnimationBilBoard,
		ProgressBarBilBoard,
		ProgressBar,
		WarningBilBoard
	};
private:
	// ���_�o�b�t�@
	ID3D11Buffer* m_VertexBuffer = NULL;

	// �e�N�X�`�����O�iunordered_map�p�j
	std::string m_Name;
	// �V�F�[�_�[���O�iunordered_map�p�j
	std::string m_ShaderName;
	// �m�[�}���e�N�X�`�����O�iunordered_map�p�j
	std::string m_NormalName;
	

	// �F
	D3DXVECTOR4 m_Color;
	// �e�N�X�`�����W
	D3DXVECTOR2 m_TexCoord;
	// �e�N�X�`����UV
	D3DXVECTOR2 m_UV;

	// �I�t�Z�b�g
	D3DXVECTOR3 m_Offset;

	// �T�C�YOffset
	D3DXVECTOR3 m_SizeOffset;

	// �e�N�X�`��
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;
	// �m�[�}���e�N�X�`��
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_NormalTexture;

	// ���_�V�F�[�_�[
	static std::unordered_map<std::string, ID3D11VertexShader*> m_VertexShader;
	// �s�N�Z���V�F�[�_�[
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShader;
	// ���_���C�A�E�g
	static std::unordered_map<std::string, ID3D11InputLayout*> m_VertexLayout;

	ID3D11Buffer* m_PositionBuffer;
	ID3D11ShaderResourceView* m_PositionSRV;

	// �X�v���C�g�̎��
	SpriteType m_SpriteType;

	// �����邩�ǂ���
	bool m_Visible = true;

	// �m�[�}���e�N�X�`��UV�l
	D3DXVECTOR4 m_NormalUV;

public:
	// �e�N�X�`����V�F�[�_�[�̃��[�h
	static void Load();
	// �e�N�X�`����V�F�[�_�[�̉��
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	// ���_�Ȃǂ̏�����
	void LoadInfo(std::string Name, std::string Shader, D3DXVECTOR2 UV);
	// �F�̒���
	void SetColor(D3DXVECTOR4 Color)
	{
		m_Color = Color;
	}
	// �X�v���C�g�̎�ނ�ݒu����
	void SetSpriteType(SpriteType ST)
	{
		m_SpriteType = ST;
	}
	// ���̐ݒu
	void SetVisibility(bool Visible) { m_Visible = Visible; }
	// UV�l�̐ݒu
	void SetUV(D3DXVECTOR2 UV) { m_UV = UV; }
	// �e�N�X�`�����W�̐ݒu
	void SetTexCoord(D3DXVECTOR2 TexCo) { m_TexCoord = TexCo; }
	// Offset�̃Z�b�^�[
	void SetOffSet(D3DXVECTOR3 Offset) { m_Offset = Offset; }
	// SizeOffset�̃Z�b�^�[
	void SetSizeOffset(D3DXVECTOR3 SizeOffset) { m_SizeOffset = SizeOffset; }
	// �m�[�}�����Z�b�g����
	void SetNormalTexture(std::string NormalName);


	// �F�̃Q�b�^�[
	D3DXVECTOR4 GetColor() { return m_Color; }
};

