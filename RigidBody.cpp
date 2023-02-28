#include "main.h"
#include "manager.h"
#include "RigidBody.h"

// ����������
void RigidBody::Init()
{
	m_RigidType = Dynamic;
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Mass = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Gravity = 0.0f;
}

// �I������
void RigidBody::Uninit()
{
}

// �X�V����
void RigidBody::Update()
{
	// �Q�[���I�u�W�F�N�g�̍��W�𑬓x�ŉ��Z���Ă��܂�
	m_GameObject->SetInformation(m_GameObject->GetPosition() + m_Velocity);

	// ���x�����񂾂񌸂�܂�
	if (!m_IgnoreMass)
	{
		m_Velocity.x -= m_Velocity.x * m_Mass.x;
		m_Velocity.y -= m_Velocity.y * m_Mass.y;
		m_Velocity.z -= m_Velocity.z * m_Mass.z;
	}
	
	// �����x��ǉ�����
	m_Velocity.x += m_Accelerate.x;
	m_Velocity.y += m_Accelerate.y;
	m_Velocity.z += m_Accelerate.z;
	
	// Y�̑��x���d�͂Ō���܂�
	if (!m_IgnoreGrav) m_Velocity.y -= m_Gravity;
}
