#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Boss_JumpAtkEffect.h"
#include "Math.h"

void Boss_JumpAtkEffect::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���ݎ���
	m_Duration = 2.0f * Manager::Time;
	m_CurTime = 0.0f;

	// ���f���ǉ�
	ModelRenderer* _MR = AddComponent<ModelRenderer>(GameObject::FirstPri);
	//_MR->SetQuaternion(true);
	_MR->SetTexture("StoneGroundNormal");
	_MR->SetModel("Rock", ModelRenderer::TitleGroundType);
	
}

void Boss_JumpAtkEffect::Update()
{
	// ���ݎ��Ԃ��߂���Ǝ����I�ɔj�󂳂�܂�
	if (m_Duration < 0.0f)
	{
		SetDestroy();
		return;
	}

	// ���ݎ��ԍX�V
	m_Duration--;

	// �X�P�[���X�V
	if (m_CurTime < m_TotalTime)
	{
		m_CurTime++;

		// ���`��ԗp
		float T = m_CurTime / m_TotalTime;

		// �����X�P�[���l
		D3DXVECTOR3 InitScale = D3DXVECTOR3(7.5f, 0.0f, 7.5f);
		// �ڕW�X�P�[���l
		D3DXVECTOR3 TargetScale = D3DXVECTOR3(7.5f, 7.5f, 7.5f);
		// ���`��ԗp�ϐ�
		D3DXVECTOR3 LerpScale;
		// �ړ�����
		float MoveAmt = 2.0f;


		// ���`���
		D3DXVec3Lerp(&LerpScale, &InitScale, &TargetScale, T);
		float PlusAmt = Math::FloatLerp(0.0f, MoveAmt, T);
		
		// ���W�X�V
		m_Position.y = m_InitPosY + PlusAmt;

		// �X�P�[���X�V
		m_Scale = LerpScale;
	}
	else
	{
		// �X�P�[���͖ڕW�X�P�[���l�ɂ���
		m_Scale = D3DXVECTOR3(7.5f, 7.5f, 7.5f);
		// ���W�X�V
		m_Position.y = m_InitPosY + 2.0f;
	}
	

	// �R���|�[�l���g�̍X�V����
	GameObject::Update();
}
