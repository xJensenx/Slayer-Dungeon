#pragma once
#include "GameObject.h"
class PlayerStatusWarning :
    public GameObject
{
private:
    // �X�e�[�^�X�̃X�v���C�g
    class SpriteComponent* m_DmgTakenSprite;
    class SpriteComponent* m_BlockSprite;

    // �_���[�W�󂯂��p�ϐ�
    float m_DmgTime;
    bool m_isDmg;
    int m_DmgState;
public:
    void Init() override;
    void Update() override;

    // DmgTaken
    void DmgTaken();
};

