#pragma once
#include "GameObject.h"
class DebugColliderBox :
    public GameObject
{
private:
    float m_Duration = 2.0f * Manager::Time;
    
    ID3D11Buffer* m_VertexBuffer = NULL;

public:
    void Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;
    void LoadInfo();

    void SetDuration(float Dur)
    {
        m_Duration = Dur * Manager::Time;
    }
};

