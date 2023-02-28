#pragma once
#include "GameObject.h"
class LockTarget :
    public GameObject
{
private:
    // ロックしているターゲット
    GameObject* m_LockOnTarget = NULL;
public:
    void Init() override;
    void Update() override;

    // ロックターゲットを設置する
    void SetLockTarget(GameObject* Target) { m_LockOnTarget = Target; }
    // ロックオンしてるか
    bool GetLockOn()
    {
        if (m_LockOnTarget != NULL)
        {
            return true;
        }
        
        return false;
    }

    // ロックしているターゲットをゲットする
    GameObject* GetLockOnTarget() { return m_LockOnTarget; }
};

