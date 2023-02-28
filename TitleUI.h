#pragma once
#include "GameObject.h"
class TitleUI :
    public GameObject
{
public:
    enum UIType
    {
        StartGame = 0,
        Setting,
        QuitGame,
        ChooseFile,
        BackButton,
        StageSelect,
        ModeSelect,
        StageButton,
        StatusButton,
        SkillButton,
        TutorialStage,
        Stage01,
        LockStage,
        Skill01,
        Skill02,
        Skill03,
    };
private:
    // UI�̎��
    UIType m_UIType;
    // �I������Ă��Ȃ�����SpriteComponent
    class SpriteComponent* m_NSSprite;
    // �I������Ă��鎞��SpriteComponent
    class SpriteComponent* m_Sprite;
    // �X�L���\���p
    class TitleSkillUI* m_ShowSkill;
    // �\���p�X�L���ɓo�^���Ă���ԍ�
    int m_SkillNumber;

    // Number
    class Number* m_SkillPoint;
    // �I������Ă��邩�ǂ���
    bool m_Chosen = false;
    // ���b�N����Ă邩�ǂ���
    bool m_isLock = false;
    // �o��
    bool m_Appear = false;
    // �X�N���[���ɏo�Ă鎞�̍��W
    D3DXVECTOR3 m_ScreenPos;
    // �o�Ԃ���Ȃ����̍��W
    D3DXVECTOR3 m_HidePos;
    // �ړ��p�^�C��
    float m_MoveTime;
    // �I���ł��Ȃ�
    bool m_CantChoose = false;
    // �ړ�����
    const float m_TotalMoveTime = 0.5f * Manager::Time;

public:
    void Init() override;
    void Update() override;
    // SpriteComponent�Ȃǂ̏�����
    void LoadInfo(UIType UIType);
    // �I������Ă��邩�ǂ����̃Z�b�^�[
    void SetChosen(bool Chosen) { m_Chosen = Chosen; }


    // UI�̎�ނ�Ԃ�
    UIType GetType() { return m_UIType; }
    // �I������Ă��邩�ǂ����̃Q�b�^�[
    bool GetChosen() { return m_Chosen; }

    D3DXVECTOR3 GetWorldPosition();
    // �ړ����Ԃ��Q�b�g
    float GetTotalMoveTime() { return m_TotalMoveTime; }
    // �o�Ԃ��擾
    bool GetAppear() { return m_Appear; }
    // �I���ł��Ȃ����擾
    bool GetCantChoose() { return m_CantChoose; }

    // ���b�N���邩�ǂ���
    void SetisLock(bool Lock) { m_isLock = Lock; }

    // ���b�N�̃Q�b�^�[
    bool GetisLock() { return m_isLock; }

    // �o�Ԃ�ݒu
    void SetAppear(bool Appear) 
    {
        m_MoveTime = 0.0f;
        m_Appear = Appear;
    }
    // ���W�ݒu
    void SetAppearPos(D3DXVECTOR3 AppearPos, D3DXVECTOR3 HidePos)
    {
        m_ScreenPos = AppearPos;
        m_HidePos = HidePos;
    }

    // �X�L���|�C���g�̐����Z�b�g
    void SetSkillPointNum(int Num);
};

