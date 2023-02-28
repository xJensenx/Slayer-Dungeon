#pragma once
#include "GameObject.h"
class GameUI :
    public GameObject
{
public:
    enum UIType
    {
        TutorialPic = 0,
        CharacterTutorial,
        MoveOrAttack
    };
private:
    // UI�̎��
    UIType m_UIType;
    // SpriteComponent�̕ϐ�
    class SpriteComponent* m_SpriteComponent;

    // �B���Ă��邩�ǂ���
    bool m_Appear;
    // �B���Ă�����W
    D3DXVECTOR3 m_HidePos;
    // �o�����Ă�����W
    D3DXVECTOR3 m_ShowPos;

    // �o������ꏊ�܂ł̐��`��ԗp����
    float m_WaitTime;

public:
    void Init() override;
    void Update() override;

    // �o�鏈��
    void SetAppear(bool Appear) 
    { 
        m_WaitTime = 0.0f;
        m_Appear = Appear;
    }

    // �����Z�b�g����
    void LoadInfo(UIType Type);
    //  ���W�ݒu
    void SetAppearPosition(D3DXVECTOR3 AppearPos, D3DXVECTOR3 HidePos)
    {
        m_ShowPos = AppearPos;
        m_HidePos = HidePos;
    }
};

