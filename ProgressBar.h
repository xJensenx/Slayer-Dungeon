#pragma once
#include "Component.h"
class ProgressBar :
    public Component
{
public:
    enum ProgressType
    {
        RightToLeft = 0,
        LeftToRight,
        TopToDown,
        DownToTop
    };
private:
    // �󔒏�Ԃ̎��i���ɒu���܂��j
    class SpriteComponent* m_BlankProgress = NULL;
    // �t����Ԃ̎��i�O�ɒu���܂��j
    class SpriteComponent* m_FullProgress = NULL;
    // �t����Ԃ̒l
    float m_MaxValue;
    // ���ݏ�Ԃ̒l
    float m_CurValue;
    // ���̏�Ԃ̒l
    float m_NexValue;

    // ���̏�Ԃ܂ł̃u�����h����
    const float m_MaxBlendTime = 0.5f * Manager::Time;
    // ���݂̃u�����h����
    float m_CurBlendTime;
    // �u�����h���Ă��邩�ǂ���
    bool m_isBlend;
    // �u�����h�O�̒l
    float m_oldValue;
    // Progress�̒l
    float m_Value;
    // �v���O���X�̌����Ă����
    ProgressType m_ProgressType;
public:
    void Init() override;
    void Uninit() override {}
    void Update() override;
    void Draw() override {}

    // �o�[��ݒu���܂�
    void SetProgressBar(class SpriteComponent* Blank, class SpriteComponent* Full)
    {
        m_BlankProgress = Blank;
        m_FullProgress = Full;
    }
    
    // �t����Ԃ̒l�ݒu
    void SetMaxValue(float Val) { m_MaxValue = Val; }

    // ���ݏ�Ԃ̒l�ݒu
    void SetCurrentValue(float Val) { m_NexValue = Val; }

    // Progress�̌�����ݒu
    void SetProgressType(ProgressType PT) { m_ProgressType = PT; }

    // Progress�̒l�̃Z�b�^�[
    float GetProgressValue() { return m_Value; }
};

