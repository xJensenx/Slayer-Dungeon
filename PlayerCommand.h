#pragma once
#include "GameObject.h"
class PlayerCommand :
    public GameObject
{
public:
    enum CommandType
    {
        Command_Logo = 0,
        Command_Attack,
        Command_Ult
    };

private:
    // �R�}���h�̎��
    CommandType m_CommandType;
    // �I�΂�Ă��邩�ǂ���
    bool m_Chosen;

    // �ҋ@��ԃe�N�X�`��
    class SpriteComponent* m_Sprite;

    // �I�΂ꂽ�e�N�X�`��
    class SpriteComponent* m_ChosenSprite;

    // �A�j���[�V��������
    float m_WaitTime;

    // �A�j���[�V�����̎w�莞��
    const float m_TotalTime = 0.1f * Manager::Time;

    // �I�΂�Ă��Ȃ�����X�T�C�Y
    const float m_NormalSize = 350.0f;

    // �I�΂�Ă��鎞��X�T�C�Y
    const float m_ChosenSize = 450.0f;

    // �g��DP��
    float m_UseDp;

public:
    void Init() override;
    void Update() override;
   
    // �R�}���h�̎�ނ�ݒ肷��
    void SetCommandType(CommandType _CT);

    // �R�}���h��I�ԏ��
    void SetChosen(bool _C)
    {
        m_Chosen = _C;
        if (m_WaitTime >= m_TotalTime)
        {
            m_WaitTime = 0.0f;
        }
    }

    // �g��DP���Z�b�g
    void SetUseDp(float Dp) { m_UseDp = Dp; }


    // �R�}���h���I�΂�Ă��邩�ǂ����̃Q�b�^�[
    bool GetChosen() { return m_Chosen; }

    // �R�}���h�̎�ނ��Q�b�g����
    CommandType GetCommandType() { return m_CommandType; }
};

