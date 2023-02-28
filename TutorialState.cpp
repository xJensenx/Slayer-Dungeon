#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Tutorial.h"
#include "TutorialState.h"
#include "Player.h"
#include "Minion.h"
#include "TutorialUI.h"
#include "input.h"

void TutorialState_Mission01::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �~�b�V�����O�P��ǉ����ʒu����
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission01>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission01Hint>();
		
		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UI�̖ڕW���W
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UI�̏������W
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;
			// UI�pLerp�ϐ�
			D3DXVECTOR3 LerpUI;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// ���W�X�V
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
			// �{�^�������ꂽ��bool��������
			for (int i = 0; i < 4; i++)
			{
				m_PushButton[i] = false;
			}
			// �`���[�g���A�������̏�����
			m_Finish = false;
		}
		break;
	case 2:
		// �ړ��L�[�S�������ꂽ�ꍇ���̃X�e�b�v�i��
		if (Input::GetKeyTrigger('W'))
		{
			m_PushButton[0] = true;
		}

		if (Input::GetKeyTrigger('A'))
		{
			m_PushButton[1] = true;
		}

		if (Input::GetKeyTrigger('S'))
		{
			m_PushButton[2] = true;
		}

		if (Input::GetKeyTrigger('D'))
		{
			m_PushButton[3] = true;
		}

		// �S���{�^�������ꂽ�̊m�F
		m_Finish = true;
		for (int i = 0; i < 4; i++)
		{
			// �܂�false�������Finish��false�ɂ���
			if (!m_PushButton[i]) m_Finish = false;
		}

		// �{�^�����S�������ꂽ�玟�̃X�e�b�v
		if (m_Finish)
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �`���[�g���A��UI���N���A��Ԃɂ���
			m_MissionUI->SetFinish();
			// ���̃X�e�b�v
			m_State = 3;
		}
		break;
	case 3:
		// �Q�b�҂��Ă���`���[�g���A���ύX
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���̃X�e�b�v
			m_State = 4;
			return;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// �X�e�[�g�ύX
			m_Tutorial->ChangeState<TutorialState_Mission02>();
		}
		break;
	}
}

void TutorialState_Mission02::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �~�b�V�����O�P��ǉ����ʒu����
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission02>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission02Hint>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UI�̖ڕW���W
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UI�̏������W
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;
			// UI�pLerp�ϐ�
			D3DXVECTOR3 LerpUI;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// ���W�X�V
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
			// �`���[�g���A�������̏�����
			m_Finish = false;
		}
		break;
	case 2:
		// �{�^�����S�������ꂽ�玟�̃X�e�b�v
		if (m_Finish)
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �`���[�g���A��UI���N���A��Ԃɂ���
			m_MissionUI->SetFinish();
			// ���̃X�e�b�v
			m_State = 3;
		}
		break;
	case 3:
		// �Q�b�҂��Ă���`���[�g���A���ύX
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���̃X�e�b�v
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// �X�e�[�g�ύX
			m_Tutorial->ChangeState<TutorialState_Mission03>();
		}
		break;
	}

}

void TutorialState_Mission03::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �~�b�V�����O�P��ǉ����ʒu����
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission03>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission03Hint>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UI�̖ڕW���W
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UI�̏������W
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;
			// UI�pLerp�ϐ�
			D3DXVECTOR3 LerpUI;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// ���W�X�V
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
			// �`���[�g���A�������̏�����
			m_Finish = false;
		}
		break;
	case 2:
		// �{�^�����S�������ꂽ�玟�̃X�e�b�v
		if (m_Finish)
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �`���[�g���A��UI���N���A��Ԃɂ���
			m_MissionUI->SetFinish();
			// ���̃X�e�b�v
			m_State = 3;
		}
		break;
	case 3:
		// �Q�b�҂��Ă���`���[�g���A���ύX
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���̃X�e�b�v
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// �X�e�[�g�ύX
			m_Tutorial->ChangeState<TutorialState_Mission04>();
		}
		break;
	}
}

void TutorialState_Mission04::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �~�b�V�����O�P��ǉ����ʒu����
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission04>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission04Hint>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UI�̖ڕW���W
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UI�̏������W
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;
			// UI�pLerp�ϐ�
			D3DXVECTOR3 LerpUI;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// ���W�X�V
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
			// �`���[�g���A�������̏�����
			m_Finish = false;

			// Minion���U���ł���悤�ɂ���
			m_Tutorial->GetMinion()->ChangeBehavior<MinionBehaviorTree_Chase>();
		}
		break;
	case 2:
		// �{�^�����S�������ꂽ�玟�̃X�e�b�v
		if (m_Finish)
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �`���[�g���A��UI���N���A��Ԃɂ���
			m_MissionUI->SetFinish();
			// ���̃X�e�b�v
			m_State = 3;
		}
		break;
	case 3:
		// �Q�b�҂��Ă���`���[�g���A���ύX
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���̃X�e�b�v
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// �X�e�[�g�ύX
			m_Tutorial->ChangeState<TutorialState_Mission05>();
		}
		break;
	}
}

void TutorialState_Mission05::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �v���C���[��Mp��S��
		m_Tutorial->GetPlayer()->SetCurMp(m_Tutorial->GetPlayer()->GetMaxMp());

		// Minion���~�߂�
		m_Tutorial->GetMinion()->ChangeBehavior<MinionBehaviorTree_Idle>();

		// �~�b�V�����O�P��ǉ����ʒu����
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission05>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission05Hint>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UI�̖ڕW���W
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UI�̏������W
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;
			// UI�pLerp�ϐ�
			D3DXVECTOR3 LerpUI;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// ���W�X�V
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
			// �`���[�g���A�������̏�����
			m_Finish = false;
			for (int i = 0; i < 3; i++)
			{
				m_PushButton[i] = false;
			}
		}
		break;
	case 2:
		m_Finish = true;
		for (int i = 0; i < 3; i++)
		{
			if (!m_PushButton[i]) m_Finish = false;
		}

		// �{�^�����S�������ꂽ�玟�̃X�e�b�v
		if (m_Finish)
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �`���[�g���A��UI���N���A��Ԃɂ���
			m_MissionUI->SetFinish();
			// ���̃X�e�b�v
			m_State = 3;
		}
		break;
	case 3:
		// �Q�b�҂��Ă���`���[�g���A���ύX
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���̃X�e�b�v
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// �X�e�[�g�ύX
			m_Tutorial->ChangeState<TutorialState_Mission06>();
		}
		break;
	}
}

void TutorialState_Mission06::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �v���C���[��Mp��S��
		m_Tutorial->GetPlayer()->SetCurDp(m_Tutorial->GetPlayer()->GetMaxDp());

		// �~�b�V�����O�P��ǉ����ʒu����
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission06>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission06Hint>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UI�̖ڕW���W
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UI�̏������W
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;
			// UI�pLerp�ϐ�
			D3DXVECTOR3 LerpUI;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// ���W�X�V
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
			// �`���[�g���A�������̏�����
			m_Finish = false;
		}
		break;
	case 2:
		// �{�^�����S�������ꂽ�玟�̃X�e�b�v
		if (m_Finish)
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �`���[�g���A��UI���N���A��Ԃɂ���
			m_MissionUI->SetFinish();
			// ���̃X�e�b�v
			m_State = 3;
		}
		break;
	case 3:
		// �Q�b�҂��Ă���`���[�g���A���ύX
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;

			// ���̃X�e�b�v
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// �X�e�[�g�ύX
			m_Tutorial->ChangeState<TutorialState_TutorialFinish>();
		}
		break;
	}
}

void TutorialState_TutorialFinish::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �v���C���[��Mp��S��
		m_Tutorial->GetPlayer()->SetCurMp(m_Tutorial->GetPlayer()->GetMaxMp());
		// �v���C���[��Dp��S��
		m_Tutorial->GetPlayer()->SetCurDp(m_Tutorial->GetPlayer()->GetMaxDp());

		// �`���[�g���A��������ݒu
		m_Tutorial->SetFinish();

		// Minion���U���ł���悤�ɂ���
		m_Tutorial->GetMinion()->ChangeBehavior<MinionBehaviorTree_Chase>();

		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_TutorialFinish>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
		}
		break;
	case 2:
		// �Q�b�ԑ҂��Ă��玟�̃X�e�b�v�i��
		if (m_CurTime < 2.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �X�e�b�v������
			m_State = 3;
			return;
		}
		break;
	case 3:
		// UI����ɖ߂�
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			m_State = 4;
		}
		break;
	}

}

void TutorialState_Greeting::Update()
{
	// ���Ԃɐi��
	switch (m_State)
	{
	case 0:
		// �~�b�V�����O�P�̃q���g��ǉ�����
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_GreetingHint>();

		// �^�C��������
		m_CurTime = 0.0f;

		// ���̃X�e�[�g�ɐi��
		m_State = 1;
		break;
	case 1:
		// UI���ړ�������
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// ���̃X�e�b�v
			m_State = 2;
		}
		break;
	case 2:
		// �Q�b�ԑ҂��Ă��玟�̃X�e�b�v�i��
		if (m_CurTime < 2.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ���ԏ�����
			m_CurTime = 0.0f;
			// �X�e�b�v������
			m_State = 3;
			return;
		}
		break;
	case 3:
		// UI����ɖ߂�
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// �q���g�̖ڕW���W
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// �q���g�̏������W
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// �q���g�pLerp�ϐ�
			D3DXVECTOR3 LerpHint;

			// ���`���
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// ���W�X�V
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// �~�b�V�����P�ɐi��
			m_Tutorial->ChangeState<TutorialState_Mission01>();
		}
		break;
	}
}
