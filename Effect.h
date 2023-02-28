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

    // �G�t�F�N�g�̃^�C�v��ݒu
    template <typename T>
    void SetEffectType()
    {
        T* Type = new T();
        Type->SetEffect(this);
        Type->Init();

        m_EffectType = Type;
    }
};

