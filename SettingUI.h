#pragma once
#include "GameObject.h"

#include "SettingUI_Type.h"
class SettingUI :
    public GameObject
{
private:
    // UI�̎��
    class SettingUI_Type* m_UIType;
    // �o�����Ă��邩�ǂ���
    bool m_Appear;
    // �ړ�����
    float m_MoveTime;
    // �B���Ă�����W
    D3DXVECTOR3 m_HidePos;
    // �o�Ă�����W
    D3DXVECTOR3 m_ScreenPos;
public:
    void Init() override;
    void Uninit() override;
    void Update() override;

    // �o�Ԃ�ݒu
    void SetAppear(bool Appear)
    {
        m_MoveTime = 0.0f;
        m_Appear = Appear;
    }
    // ���W�ݒu
    void SetAppearPos(D3DXVECTOR3 AppearPos, D3DXVECTOR3 HidePos)
    {
        m_ScreenPos = AppearPos;
        m_HidePos = HidePos;
    }

    // UI�̎�ނ��Z�b�g
    template <typename T>
    void SetUIType()
    {
        // ���ɑ��݂��Ă���ꍇ�͏����܂�
        if (m_UIType != NULL)
        {
            delete m_UIType;
            m_UIType = NULL;
        }

        T* Type = new T();
        Type->SetSettingUI(this);
        Type->Init();
        m_UIType = Type;
    }
};

