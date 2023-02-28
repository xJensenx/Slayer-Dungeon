#pragma once
#include "Component.h"
#include "ModelRenderer.h"

class ParticleSystem : public Component
{
private:
	// �p�[�e�B�N���̐�
	int m_ParticleNum;
	// �p�[�e�B�N���̃T�C�Y
	D3DXVECTOR3 m_ParticleSize;
	// �p�[�e�B�N���̉�]�̉����x
	D3DXVECTOR3 m_ParticleAccRot;
	// �����蔻��ݒ�
	bool m_ParticleCol;
	// �F�̐ݒ�
	D3DXCOLOR m_ParticleColor;
	// Emission�ݒ�
	D3DXCOLOR m_ParticleEmission;
	// Ambient�ݒ�
	D3DXCOLOR m_ParticleAmbient;
	// TitleEffect��t���邩�ǂ���
	bool m_TitleEffect;
	// �}�e���A����ݒu���邩�ǂ���
	bool m_UseMaterial;
	// �V�F�[�_�[�̐ݒu
	ModelRenderer::LightningType m_ShaderType;
	// 2D�̐ݒ�
	bool m_Particle2D;
	// Particle�̎g���Ă��郂�f�����e�N�X�`���̖��O
	std::string m_ParticleName;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �p�[�e�B�N���𐶐�����
	void SpawnEmitter(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, D3DXVECTOR3 Acc, float Dur);
	
	// �p�[�e�B�N���̐���ݒu����
	void SetParticleNum(int Num) { m_ParticleNum = Num; }
	// �p�[�e�B�N���̃T�C�Y��ݒu����
	void SetParticleSize(D3DXVECTOR3 Size) { m_ParticleSize = Size; }
	// �p�[�e�B�N���̓����蔻���ݒu����
	void SetParticleCol(bool Col) { m_ParticleCol = Col; }
	// �p�[�e�B�N���̐F�ݒ�
	void SetParticleColor(D3DXCOLOR Color) { m_ParticleColor = Color; }
	// �p�[�e�B�N����Ambient�ݒ�
	void SetParticleAmbient(D3DXCOLOR Ambient) { m_ParticleAmbient = Ambient; }
	// �p�[�e�B�N����Emission�ݒ�
	void SetParticleEmission(D3DXCOLOR Emission) { m_ParticleEmission = Emission; }
	// �^�C�g���G�t�F�N�g��t����
	void SetTitleEffect() { m_TitleEffect = true; }
	// �}�e���A����ݒu����
	void SetParticleMaterial(bool useMaterial) { m_UseMaterial = useMaterial; }
	// �V�F�[�_�[�̐ݒu
	void SetParticleShader(ModelRenderer::LightningType Shader) { m_ShaderType = Shader; }
	// 2D�̐ݒu
	void SetParticle2D(bool is2D) { m_Particle2D = is2D; }
	// �e�N�X�`���̐ݒ�
	void SetParticleName(std::string Name) { m_ParticleName = Name; }
	// �p�[�e�B�N���̉�]�̉����x���Z�b�g
	void SetParticleAccRotation(D3DXVECTOR3 Rotation) { m_ParticleAccRot = Rotation; }
	
	// �p�[�e�B�N���̐����Q�b�g����
	int GetParticleNum() { return m_ParticleNum; }


};

