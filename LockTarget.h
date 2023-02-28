#pragma once
#include "GameObject.h"
class LockTarget :
    public GameObject
{
private:
    // ���b�N���Ă���^�[�Q�b�g
    GameObject* m_LockOnTarget = NULL;
public:
    void Init() override;
    void Update() override;

    // ���b�N�^�[�Q�b�g��ݒu����
    void SetLockTarget(GameObject* Target) { m_LockOnTarget = Target; }
    // ���b�N�I�����Ă邩
    bool GetLockOn()
    {
        if (m_LockOnTarget != NULL)
        {
            return true;
        }
        
        return false;
    }

    // ���b�N���Ă���^�[�Q�b�g���Q�b�g����
    GameObject* GetLockOnTarget() { return m_LockOnTarget; }
};

