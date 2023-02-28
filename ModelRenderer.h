#pragma once
#include <unordered_map>
#include "Component.h"
class ModelRenderer : public Component
{
public:
	enum LightningType
	{
		UnlitType = 0,
		LitType,
		FogType,
		ShadowType,
		ToonType,
		EnvType,
		ParticleEnvType,
		RimType,
		TitleGroundType,
		FireBallType
	};
private:
	LightningType m_LightningType = UnlitType;

	std::string m_Name;
	std::string m_ShaderName;
	std::string m_NormalTextureName;
	// �����邩�ǂ���
	bool m_Visibility = true;

	// �m�[�}���e�N�X�`���g���Ă��邩�ǂ���
	bool m_UseNormal = false;

	// �}�e���A�����㏑�����܂���
	bool m_ChangeMaterial = false;

	// Quaternion�g�p���Ă��邩�ǂ���
	bool m_UseQuaternion;

	// Parameter
	D3DXVECTOR4 m_Parameter;
	
	// �}�e���A���p
	D3DXCOLOR m_Ambient;
	D3DXCOLOR m_Emission;
	D3DXCOLOR m_Diffuse;

	// ���f��
	static std::unordered_map<std::string, class Model*>m_Model;
	// ���O�Ƀ��[�h����e�N�X�`��
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_LoadTexture;
	// ���f���̃T�C�Y
	static std::unordered_map<std::string, D3DXVECTOR3> m_ModelSize;

	// ���_�V�F�[�_�[
	static std::unordered_map<std::string, ID3D11VertexShader*> m_VertexShader;
	// �s�N�Z���V�F�[�_�[
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShader;
	// ���_���C�A�E�g
	static std::unordered_map<std::string, ID3D11InputLayout*> m_VertexLayout;

	// �S�Ă̒��_�̍��W
	std::vector<D3DXVECTOR3> m_VertexPosition;

public:
	// ���f����e�N�X�`�������[�h����
	static void Load();
	// ���f����e�N�X�`�����A�����[�h����
	static void Unload();
	// �Q�[�����̃��f����e�N�X�`�������[�h����
	static void LoadGameAsset();
	// �Q�[�����̃��f����e�N�X�`�����A�����[�h����
	static void UnloadGameAsset();
	// ����������
	void Init() override;
	// �I������
	void Uninit() override;
	// �X�V����
	void Update() override;
	// �`�揈��
	void Draw() override;
	// ���f�����Z�b�g����
	void SetModel(std::string _Name, LightningType _Type);
	// Ambient���Z�b�g����
	void SetAmbient(D3DXCOLOR Ambient) { m_Ambient = Ambient; }
	// Emission���Z�b�g����
	void SetEmission(D3DXCOLOR Emission) { m_Emission = Emission; }
	// Diffuse���Z�b�g����
	void SetDiffuse(D3DXCOLOR Diffuse) { m_Diffuse = Diffuse; }
	// Material�g���Ă���̂��Z�b�g����
	void SetUseMaterial(bool useMaterial) { m_ChangeMaterial = useMaterial; }
	// �m�[�}���e�N�X�`�����Z�b�g����
	void SetTexture(std::string Name) { m_NormalTextureName = Name; m_UseNormal = true; }
	// �����邩�ǂ������Z�b�g����
	void SetVisibility(bool Visible) { m_Visibility = Visible; }
	// Quaternion�g���Ă��邩�ǂ���
	void SetQuaternion(bool Qua) { m_UseQuaternion = Qua; }
	// Parameter���Z�b�g
	void SetParameter(D3DXVECTOR4 Par) { m_Parameter = Par; }
	// ���f���T�C�Y���擾
	D3DXVECTOR3 GetModelSize(std::string _Name) { return m_ModelSize[_Name]; }
	// �S���̒��_���W���擾
	std::vector<D3DXVECTOR3> GetVertexPosition() { return m_VertexPosition; }
	// Parameter���擾
	D3DXVECTOR4 GetParameter() { return m_Parameter; }


};