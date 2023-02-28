#pragma once
#include "GameObject.h"
class CinematicBorder :
    public GameObject
{
public:
    enum PositionType
    {
        Top = 0,
        Bot
    };
private:
    // �J�b�g�V�[���ł͂Ȃ����̏�̍��W
    const D3DXVECTOR3 m_TopHidePos = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 16, 0.0f);
    // �J�b�g�V�[���ł͂Ȃ����̉��̍��W
    const D3DXVECTOR3 m_BotHidePos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT + (SCREEN_HEIGHT / 16), 0.0f);
    // ��̍��W
    const D3DXVECTOR3 m_TopPosition = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 16, 0.0f);
    // ���̍��W
    const D3DXVECTOR3 m_BotPosition = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 16), 0.0f);
    // �|�W�V�����^�C�v
    PositionType m_PosType;
    // �J�b�g�V�[���p����
    float m_CurTime;
    const float m_TotalTime = 3.0f * Manager::Time;

public:
    void Init() override;
    void Update() override;

    // �|�W�V�����^�C�v�̃Z�b�^�[
    void SetPosType(PositionType PT);
    // �J�b�g�V�[���̔���
    void SetCutscene(bool CutScene)
    {
        m_CurTime = 0.0f;
        m_Cinematic = CutScene;
    }
};

