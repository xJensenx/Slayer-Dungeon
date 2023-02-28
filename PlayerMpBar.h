#pragma once
#include "GameObject.h"
class PlayerMpBar :
    public GameObject
{
private:
    // �v���C���[�N���X
    class Player* m_Character = NULL;
    // �t���̏�Ԃ̃X�v���C�g
    class SpriteComponent* m_PlayerFullMpBar;
    // �t���̏�Ԃ̃X�v���C�g
    class SpriteComponent* m_PlayerNoMpBar;

    // ����Ȃ����
    bool m_Insufficient;
    // �\������
    float m_InsufficientTime;
public:
    void Init() override;
    void Update() override;

    // �L�����N�^�[�̐ݒu
    void SetCharacter(Player* P) { m_Character = P; }

    // ����Ȃ���Ԃ�ݒu����
    void SetInsufficient() { m_Insufficient = true; m_InsufficientTime = 0.0f; }
};

