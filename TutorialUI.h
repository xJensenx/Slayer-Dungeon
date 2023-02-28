#pragma once
#include "GameObject.h"
#include "TutorialUIType.h"
class TutorialUI :
    public GameObject
{
private:
    // ��ނ̃N���X
    class TutorialUIType* m_UIType;
public:
    void Init() override;
    void Update() override;

    // ��ނ�ݒu
    template <typename T>
    void SetUIType()
    {
        // ���ɐݒu���Ă���ꍇ�͍폜����
        if (m_UIType != NULL)
        {
            delete m_UIType;
            m_UIType = NULL;
        }

        T* Type = new T();
        Type->SetCharacter(this);
        Type->Init();

        m_UIType = Type;
    }

    // �N���A�����֐�
    void SetFinish() { m_UIType->TutorialClear(); }
};

