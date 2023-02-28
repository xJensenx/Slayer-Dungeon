#pragma once
#include "GameObject.h"
#include "ModelRenderer.h"

class ParticleObj :
    public GameObject
{
public:
private:
    // ���݂��鎞��
    float m_Duration;
    // �����蔻�肠�邩�ǂ���
    bool m_Collision;
    // �^�C�g�����S�̃G�t�F�N�g
    bool m_Title;
    // �^�C�g���G�t�F�N�g�̏������W
    D3DXVECTOR3 m_TitlePos;
    // ��]�̉����x
    D3DXVECTOR3 m_AccRotation;
    // �^�C�g���G�t�F�N�g����Lerp�p
    float m_SinValue;
    // �^�C�g���G�t�F�N�g�X�e�[�g
    int m_TitleState;
    // 2D��3D
    bool m_Particle2D;

public:
    void Init() override;
    void Update() override;

    // ���݂��鎞�Ԃ�ݒu����
    void SetDuration(float Duration) { m_Duration = Duration * Manager::Time; }
    // �V�F�[�_�[�̐ݒu
    void SetShader(ModelRenderer::LightningType ShaderType);
    // �}�e���A���̐ݒu
    void SetMaterial(bool On);
    // �����蔻���ݒu����
    void SetCollision(bool Col) { m_Collision = Col; }
    // �F�̐ݒ�
    void SetColor(D3DXCOLOR Color, D3DXCOLOR Ambient, D3DXCOLOR Emission);
    // �^�C�g���G�t�F�N�g��ݒu����
    void SetTitleEffect() { m_Title = true; m_TitlePos = m_Position; }
    // Set2D
    void Set2DParticle();
    // ���O���Z�b�g
    void SetParticleName(std::string Name);
    // ��]�̉����x���Z�b�g
    void SetAccRotation(D3DXVECTOR3 Acc) { m_AccRotation = Acc; }

    // �^�C�g���G�t�F�N�g�̋���
    void TitleEffectMovement();
    

};

