#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "ProgressBar.h"
#include "Math.h"

void ProgressBar::Init()
{
	// ������
	m_MaxValue = m_CurValue = m_NexValue = m_CurBlendTime = m_oldValue = 0.0f;
	m_isBlend = false;
	m_ProgressType = RightToLeft;
}

void ProgressBar::Update()
{
	// ���̏�Ԃ����̏�ԂƈႤ�l�̎�
	if (m_NexValue != m_CurValue)
	{
		// �u�����h�n�܂鎞��񏉊������܂�
		if (!m_isBlend)
		{
			m_isBlend = true;
			m_CurBlendTime = 0.0f;
			m_oldValue = m_CurValue;
		}

		if (m_CurBlendTime < m_MaxBlendTime)
		{
			m_CurBlendTime++;
			float T = m_CurBlendTime / m_MaxBlendTime;

			m_CurValue = Math::FloatLerp(m_oldValue, m_NexValue, T);
		}
		else
		{
			m_CurValue = m_NexValue;
		}
	}
	else
	{
		m_isBlend = false;
	}

	m_Value = m_CurValue / m_MaxValue;

	switch (m_ProgressType)
	{
	case RightToLeft:
		m_FullProgress->SetUV(D3DXVECTOR2(m_Value, 1.0f));
		break;
	case TopToDown:
		break;
	case LeftToRight:
		m_FullProgress->SetTexCoord(D3DXVECTOR2((m_Value + 1.0f) - m_Value, 1.0f));
		break;
	case DownToTop:
		m_FullProgress->SetUV(D3DXVECTOR2(1.0f, m_Value));
		break;
	}
	

}
