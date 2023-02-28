#pragma once
#include "GameObject.h"

class Camera: public GameObject
{
public:
	enum BlendType
	{
		Lerp = 0,
		Hermite
	};
private:
	D3DXMATRIX	m_ViewMatrix;
	D3DXMATRIX	m_ProjectionMatrix;
	bool		m_PilotMode = false;

	// �u�����h�̎��
	BlendType m_BlendType;

	// ������]�O�̍��W
	D3DXVECTOR3 m_BeforeRotation;

	// �����I�ɑO�ɉ�]���鎞��
	const float m_TotalRotateTime = 1.5f * Manager::Time;

	// ���̉�]���Ă��鎞�̎���
	float m_CurRotateTime;

	// ������]����܂ŉ��b�҂��܂�
	const float m_TotalWaitTime = 4.0f * Manager::Time;
	// ��]�������I�Ƀv���C���[�̑O�ɉ�]������̑҂�����
	float m_WaitTime;
	// �O�̃t���[����Rotation�l
	D3DXVECTOR3 m_OldRotation;

	// �J�����V�F�[�N�p
	D3DXVECTOR3 m_Magnitude;
	// �J�����V�F�[�N�p
	D3DXVECTOR3 m_Amplitude;
	// �J�����V�F�[�N��
	bool m_Shaking;
	// �J�����V�F�[�N�̎���
	float m_ShakeTime;
	// ��������
	float m_RecoverTime;
	// ���v��������
	const float m_TotalRecoverTime = 1.5f * Manager::Time;
	// ����Magnitude
	D3DXVECTOR3 m_InitMagnitude;

	// �J�b�g�V�[���p�u�����h�^�[�Q�b�g�ƃ|�W�V����
	D3DXVECTOR3 m_BeforePos;
	D3DXVECTOR3 m_AfterPos;
	D3DXVECTOR3 m_BeforeTarget;
	D3DXVECTOR3 m_AfterTarget;
	D3DXVECTOR3 m_BeforeTan;
	D3DXVECTOR3 m_AfterTan;

	// �J�b�g�V�[���p����
	float m_BlendTime;
	float m_TotalBlendTime = 3.0f * Manager::Time;

	// �u�����h���Ă��邩�ǂ���
	bool m_isBlend;

	// �^�[�Q�b�g�̃u�����h���Ă��邩
	bool m_isTargetBlend;

	// �^�[�Q�b�g�u�����h����
	float m_TargetBlendTime;

	// ���̃^�[�Q�b�g
	D3DXVECTOR3 m_NewTargetPos;

	// �u�����h�O�̃^�[�Q�b�g
	D3DXVECTOR3 m_OldTargetPos;
	
	// �u�����h�O�̃|�W�V����
	D3DXVECTOR3 m_OldPos;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }

	bool CheckView(D3DXVECTOR3 Position, float Size);
	bool GetIsBlend() { return m_isBlend; }

	// �f�o�b�O�p
	void SetPilotMode(bool Pilot)
	{
		m_PilotMode = Pilot;
	}

	// �J�����V�F�[�N�iMag�̒l��0.1�`���x�X�g�j
	void ShakeCam(D3DXVECTOR3 Mag, float Time);

	// ���̏ꏊ�ɖ߂�
	void BlendBack(float TotalBlendTime);

	// �J�����u�����h
	void BlendTo(D3DXVECTOR3 Pos, D3DXVECTOR3 Tar, float BlendTime)
	{
		if (!m_Cinematic) return;

		m_BlendType = Lerp;
		m_BlendTime = 0.0f;
		m_BeforePos = m_Position;
		m_BeforeTarget = m_Target;
		m_AfterPos = Pos;
		m_AfterTarget = Tar;
		m_TotalBlendTime = BlendTime * Manager::Time;
		m_isBlend = true;
	}

	// �J�����u�����h�i�G���~�[�g�j
	void HermiteBlendTo(D3DXVECTOR3 Pos, D3DXVECTOR3 Tar, D3DXVECTOR3 Tan1, D3DXVECTOR3 Tan2, float BlendTime)
	{
		if (!m_Cinematic) return;

		m_BlendType = Hermite;
		m_BlendTime = 0.0f;
		m_BeforePos = m_Position;
		m_BeforeTarget = m_Target;
		m_AfterPos = Pos;
		m_AfterTarget = Tar;
		m_TotalBlendTime = BlendTime * Manager::Time;
		m_isBlend = true;
		m_BeforeTan = Tan1;
		m_AfterTan = Tan2;
	}

	// Cinematic���[�h�̎����ڍ��W���Z�b�g����
	void SetOldPosTar(D3DXVECTOR3 Pos, D3DXVECTOR3 Tar) { m_OldPos = Pos, m_OldTargetPos = Tar; }

	void InitOldPos()
	{
		m_OldPos = m_Position;
		m_OldTargetPos = m_Target;
	}
};

