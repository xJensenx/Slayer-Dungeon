#pragma once
#include "AnimationManager.h"

#include "MinionAnimationState.h"
class MinionAnimation :
    public AnimationManager
{
private:
    // Minion�̏��ɓ����ϐ�
    class Minion* m_Character = NULL;
    // Minion�̃A�j���[�V�����X�e�[�g�@
    class MinionAnimationState* m_AnimationState;
    // Minion�̑O�̃A�j���[�V�����X�e�[�g
    class MinionAnimationState* m_PrevAnimationState;

public:
    void Init() override;
    void Uninit() override;
    void Update() override;

    // Minion�̏����Z�b�g����
    void SetCharacter(Minion* Character) { m_Character = Character; }

    // �X�e�[�g��ς��鏈��
    template <typename T>
    void ChangeState()
    {
        // ���ɃX�e�[�g�����݂��Ă���ꍇ
        if (m_AnimationState != NULL)
        {
            // �O�̃A�j���[�V�����X�e�[�g�����݂��Ă���ꍇ�͏����܂�
            if (m_PrevAnimationState != NULL)
            {
                delete m_PrevAnimationState;
                m_PrevAnimationState = NULL;
            }
            // ���̃X�e�[�g��O�̃A�j���[�V�����X�e�[�g�ɓ���܂�
            m_PrevAnimationState = m_AnimationState;
            // �O�̓��[�v���Ă��邩�ǂ������Q�b�g
            m_CurLoop = m_AnimationState->GetLoop();
            m_PrevPlayRate = m_AnimationState->GetPlayRate();
            m_AnimationState = NULL;
        }

        m_PrevFrame = m_CurFrame;	// �O�̃t���[���������݂̃t���[�����ɍX�V����
        m_CurFrame = 0.0f;			// ���݂̃t���[�������O�ɂ���i�ŏ�����n�߂�j
        m_BlendRate = 0.0f;			// �u�����h���[�g���O�ɂ���
        m_PrevLoop = m_CurLoop;		// �O��̃��[�v��Ԃ��X�V����
        m_PrevAnimationName = m_CurAnimationName;

        // �V�����X�e�[�g�쐬
        T* State = new T();
        State->SetCharacter(m_Character);
        State->SetAnimationTree(this);
        State->Init();
        m_AnimationState = State;


        m_AnimModel->LoadAnimation(m_PrevAnimationName, m_CurAnimationName);
    }

    // ���݂̃A�j���[�V�����X�e�[�g���擾
    template <typename T>
    bool GetCurAnimationState()
    {
        // �X�e�[�g���Ȃ���false��return
        if (m_AnimationState == NULL) return false;

        // ������ނȂ�return����
        if (typeid(*m_AnimationState) == typeid(T)) return true;

        return false;
    }
    
    // �O�̃A�j���[�V�����X�e�[�g���擾
    template <typename T>
    bool GetPreAnimationState()
    {
        // �X�e�[�g���Ȃ���false��return
        if (m_PrevAnimationState == NULL) return false;

        // ������ނȂ�return true����
        if (typeid(*m_PrevAnimationState) == typeid(T)) return true;

        return false;
    }
};


