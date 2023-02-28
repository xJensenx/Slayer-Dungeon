#pragma once
#include "GameObject.h"

#include "EffectType.h"

class Effect :
    public GameObject
{
private:
    class EffectType* m_EffectType;
public:
    void Init() override;
    void Update() override;

    // エフェクトのタイプを設置
    template <typename T>
    void SetEffectType()
    {
        T* Type = new T();
        Type->SetEffect(this);
        Type->Init();

        m_EffectType = Type;
    }
};

