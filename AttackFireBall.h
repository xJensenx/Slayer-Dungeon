#pragma once
#include "GameObject.h"

#include "AttackFireBall_Type.h"
class AttackFireBall :
    public GameObject
{
private:
    // �t�@�C�A�{�[���̃^�C�v�̃N���X
    class AttackFireBall_Type* m_FireBallType;
    // �ڕW�I�u�W�F�N�g
    class GameObject* m_TargetObj;
    // �G���~�[�g�pTan
    D3DXVECTOR3 m_ShootTan;
    // �����p�x
    float m_InitAngle;
public:
    void Init() override;
    void Update() override;

    // �^�C�v�̐ݒu
    template <typename T>
    void SetType()
    {
        // ���ɑ��݂��Ă���Ə����܂�
        if (m_FireBallType != NULL)
        {
            delete m_FireBallType;
            m_FireBallType = NULL;
        }

        // �V�����^�C�v��錾�����������܂�
        T* Type = new T();
        Type->SetCharacter(this);
        Type->SetTarget(m_TargetObj);
        Type->Init();
        // �^�C�v�������̃^�C�v�ɒǉ�����
        m_FireBallType = Type;
    }

    // �G���~�[�g�pTan��ݒu
    void SetHermiteTan(D3DXVECTOR3 _Tan) { m_ShootTan = _Tan; }

    // �^�[�Q�b�g�I�u�W�F�N�g���Z�b�g
    void SetTargetObj(class GameObject* Obj) { m_TargetObj = Obj; }

    // �����p�x��ݒu
    void SetInitAngle(float Angle) { m_InitAngle = Angle; }

    // �����p�x���擾
    float GetInitAngle() { return m_InitAngle; }

    // �G���~�[�g�pTan���擾
    D3DXVECTOR3 GetHermiteTan() { return m_ShootTan; }
};

