#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Camera.h"
#include "Player.h"
#include "Scene.h"
#include "LockTarget.h"
#include "Math.h"

void Camera::Init()
{
	// ������
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -3.5f);
	m_NewTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Amplitude = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Shaking = false;
	m_ShakeTime = 0.0f;
	m_Cinematic = false;
	m_BeforePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_AfterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BeforeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_AfterTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TotalBlendTime = 3.0f * Manager::Time;
	m_BlendTime = 3.0f * Manager::Time;
	m_isBlend = false;
	m_isTargetBlend = false;
	m_TargetBlendTime = 0.0f;
	m_OldTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BlendType = Lerp;
}

void Camera::Uninit()
{
	GameObject::Uninit();
}

void Camera::Update()
{
	if (m_Pause && !m_IgnorePause) return;

	// �V�[���擾
	Scene* scene = Manager::GetScene();
	
	// �v���C���[�擾
	Player* PlayerObj = scene->GetGameObject<Player>();
	D3DXVECTOR3 PlayerPos;
	if (PlayerObj != NULL)
	{
		PlayerPos = PlayerObj->GetPosition();
	}
	D3DXVECTOR3 CamRot = GetForward();

	// �J�����V�F�[�N���Ă��鎞
	if (m_Shaking)
	{
		// �J�����V�F�[�N���Ԓ����ƃ����_���̒l�ŗh���悤��
		if (m_ShakeTime > 0.0f)
		{
			m_ShakeTime--;

			m_Amplitude.x = Math::FloatRandBetween(-1.0f, 1.0f) * m_Magnitude.x;
			m_Amplitude.y = Math::FloatRandBetween(-1.0f, 1.0f) * m_Magnitude.y;
			m_InitMagnitude = m_Magnitude;
			m_RecoverTime = 0.0f;
		}
		else
		{
			// �J�����V�F�[�N�I�������������h��Ă��Ȃ���Ԃɖ߂�
			if (m_RecoverTime < m_TotalRecoverTime)
			{
				m_RecoverTime++;

				float T = m_RecoverTime / m_TotalRecoverTime;

				D3DXVECTOR3 LerpVec;
				D3DXVECTOR3 NoMagnitude = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				D3DXVec3Lerp(&LerpVec, &m_InitMagnitude, &NoMagnitude, T);

				m_Magnitude = LerpVec;
				m_Amplitude.x = Math::FloatRandBetween(-1.0f, 1.0f) * m_Magnitude.x;
				m_Amplitude.y = Math::FloatRandBetween(-1.0f, 1.0f) * m_Magnitude.y;
			}
			else
			{
				m_Amplitude.x = 0.0f;
				m_Amplitude.y = 0.0f;
				m_Shaking = false;
			}
		}
	}


	if (!m_Cinematic)
	{
		if (PlayerObj != NULL)
		{
			m_isTargetBlend = false;

			m_Rotation.y += (Input::GetMousePos().x - SCREEN_WIDTH / 2) * 0.003f;
			m_Rotation.x += (Input::GetMousePos().y - SCREEN_HEIGHT / 2) * 0.003f;

			// �J�����̐���
			if (m_Rotation.x <= -D3DX_PI / 6)
			{
				m_Rotation.x = -D3DX_PI / 6;
			}
			if (m_Rotation.x >= D3DX_PI / 6)
			{
				m_Rotation.x = D3DX_PI / 6;
			}


			m_Target = D3DXVECTOR3(PlayerPos.x + m_Amplitude.x, PlayerPos.y + 2.0f + m_Amplitude.y, PlayerPos.z);
			m_Position = PlayerPos - CamRot * 3.5f + D3DXVECTOR3(m_Amplitude.x, 2.0f + m_Amplitude.y, 0.0f);

			//// �O�̉�]�������ꍇ�͑҂����Ԃ��ǂ�ǂ�X�V��
			//// ���̎��Ԍo�����玩����]���s��
			//if (m_OldRotation == m_Rotation)
			//{
			//	if (m_WaitTime < m_TotalWaitTime)
			//	{
			//		m_WaitTime++;
			//		m_BeforeRotation = m_Rotation;
			//	}
			//	else
			//	{
			//		if (m_CurRotateTime < m_TotalRotateTime)
			//		{
			//			m_CurRotateTime++;
			//			D3DXVECTOR3 PlayerRot = D3DXVECTOR3(PlayerObj->GetRotation().x + Math::PI(), PlayerObj->GetRotation().y + Math::PI(), PlayerObj->GetRotation().z + Math::PI());
			//			D3DXVECTOR3 LerpRot;
			//			float T = m_CurRotateTime / m_TotalRotateTime;
			//			D3DXVec3Lerp(&LerpRot, &m_BeforeRotation, &PlayerRot, T);
			//			LerpRot.z = m_Rotation.z;
			//			m_Rotation = LerpRot;
			//			m_OldRotation = m_Rotation;
			//		}
			//		
			//	}
			//}
			//else // �O�̉�]���Ⴄ�ꍇ�͈ړ����Ă���Ƃ�������
			//{
			//	m_CurRotateTime = 0.0f;
			//	m_WaitTime = 0.0f;
			//	m_OldRotation = m_Rotation;
			//}

			//// �g�b�v�r���[
			//m_Target = PlayerPos;
			//m_Position = PlayerPos + D3DXVECTOR3(0.0f, 2.0f, -5.0f);

			//// �t�@�[�X�g�p�[�\���r���[
			//m_Target = PlayerPos + CamRot;
			//m_Position = PlayerPos;
		}
	}
	else
	{
		if (m_BlendTime < m_TotalBlendTime)
		{
			m_BlendTime++;

			float T = m_BlendTime / m_TotalBlendTime;

			D3DXVECTOR3 LerpTarget;
			D3DXVec3Lerp(&LerpTarget, &m_BeforeTarget, &m_AfterTarget, T);
			m_Target = LerpTarget + m_Amplitude;
			m_OldTargetPos = m_Target;
			
			if (m_BlendType == Lerp)
			{
				D3DXVECTOR3 LerpPos;
				D3DXVec3Lerp(&LerpPos, &m_BeforePos, &m_AfterPos, T);
				m_Position = LerpPos + m_Amplitude;
				m_OldPos = m_Position;
			}
			else if(m_BlendType == Hermite)
			{
				D3DXVECTOR3 HermitePos;
				D3DXVec3Hermite(&HermitePos, &m_BeforePos, &m_BeforeTan, &m_AfterPos, &m_AfterTan, T);
				m_Position = HermitePos + m_Amplitude;
				m_OldPos = m_Position;
			}

			m_isBlend = true;
		}
		else
		{
			m_Target = m_OldTargetPos + m_Amplitude;
			m_Position = m_OldPos + m_Amplitude;

			m_isBlend = false;
		}
	}


	// �f�o�b�O�p
	if (m_PilotMode)
	{
		if (Input::GetKeyPress('W'))
		{
			m_Position += GetForward() * 0.05f;
		}
		if (Input::GetKeyPress('S'))
		{
			m_Position += GetForward() * -0.05f;
		}
		if (Input::GetKeyPress('A'))
		{
			m_Position += GetRight() * -0.05f;
		}
		if (Input::GetKeyPress('D'))
		{
			m_Position += GetRight() * 0.05f;
		}
		if (Input::GetKeyPress('Q'))
		{
			m_Position += GetUp() * -0.05f;
		}
		if (Input::GetKeyPress('E'))
		{
			m_Position += GetUp() * 0.05f;
		}

		m_Rotation.y -= (SCREEN_WIDTH / 2 - Input::GetMousePos().x) * (0.3f / 60.0f);
		m_Rotation.x -= (SCREEN_HEIGHT / 2 - Input::GetMousePos().y) * (0.3f / 60.0f);

		m_Target = m_Position + GetForward();
	}

	GameObject::Update();
}

void Camera::Draw()
{
	GameObject::Draw();
	// �r���[�}�g���N�X�ݒ�
	//D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	
	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

	Renderer::SetCameraPosition(m_Position);
	
}

bool Camera::CheckView(D3DXVECTOR3 Position, float Size)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	// ���ʔ���
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Size)
		{
			return false;
		}
	}

	// �E�ʔ���
	{
		v1 = wpos[1] - m_Position;
		v2 = wpos[3] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) > Size)
		{
			return false;
		}
	}

	// ��ʔ���
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[1] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) > Size)
		{
			return false;
		}
	}

	// ���ʔ���
	{
		v1 = wpos[2] - m_Position;
		v2 = wpos[3] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Size)
		{
			return false;
		}
	}

	// �O�㔻��
	{
		if (D3DXVec3Length(&v) > 500.0f)
		{
			return false;
		}
	}
	return true;
}

void Camera::ShakeCam(D3DXVECTOR3 Mag, float Time)
{
	m_Magnitude = Mag;
	m_ShakeTime = Time * Manager::Time;
	m_Shaking = true;
}

void Camera::BlendBack(float TotalBlendTime)
{
	// �V�[���擾
	Scene* scene = Manager::GetScene();

	// �v���C���[�擾
	Player* PlayerObj = scene->GetGameObject<Player>();
	D3DXVECTOR3 PlayerPos = PlayerObj->GetPosition();
	D3DXVECTOR3 CamRot = GetForward();

	D3DXVECTOR3 OriginalPos = PlayerPos - CamRot * 3.5f + D3DXVECTOR3(m_Amplitude.x, 2.0f + m_Amplitude.y, 0.0f);
	D3DXVECTOR3 OriginalTarget = D3DXVECTOR3(PlayerPos.x + m_Amplitude.x, PlayerPos.y + 2.0f + m_Amplitude.y, PlayerPos.z);

	m_BlendTime = 0.0f;
	m_BeforePos = m_Position;
	m_BeforeTarget = m_Target;
	m_AfterPos = OriginalPos;
	m_AfterTarget = OriginalTarget;
	m_TotalBlendTime = TotalBlendTime * Manager::Time;
	m_isBlend = true;
	m_BlendType = Lerp;
}

