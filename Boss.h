#pragma once
#include "GameObject.h"

class Boss :
    public GameObject
{
public:
    enum BossPhase
    {
        NormalPhase = 0,
        RagePhase
    };

    enum AttackType
    {
        HeavyAtk = 0,
        JumpAtk,
        JumpAtkSec,
        KnockBackAtk
    };
private:

    // �A�j���[�V�����}�l�[�W���[
    class BossAnimation* m_BossAnimation;

    class BossBehaviorTree* m_BehaviorTree;

    // �f�o�b�O�p
    bool m_Debug = false;
    
    // �{�X��AI�p�ϐ�
    bool m_PlayerFound = false;                 // �v���C���[�������������ǂ���
    bool m_Attackable = false;                  // �U���ł��邩�ǂ���
    D3DXVECTOR3 m_TargetPos;                    // �ǂ��^�[�Q�b�g�̍��W
    float m_ChaseSpd;                           // �v���C���[��ǂ��X�s�[�h
    float m_CDTime = 3.0f * Manager::Time;// �W�����v�U���̃N�[���_�E��
    bool m_CoolDown = false;                    // �W�����v�U�����N�[���_�E�������ǂ���
    bool m_isAttacking = false;                 // �U�����Ă��邩�ǂ���
    float m_CurHp;                              // �{�X�̌��݂�Hp
    float m_MaxHp;                              // �{�X�̃t����Hp
    bool m_isDead;                              // �{�X������ł��邩�ǂ���
    bool m_HalfHp = false;                      // �{�X��������Hp�܂ōs�������i�s������QTE�𔭐����܂��j
    BossPhase m_BossPhase;                      // �{�X�̒i�K
    float m_BossJumpCurTime;                    // 
    D3DXVECTOR3 m_JumpStartPosition;            // 
    D3DXVECTOR3 m_JumpEndPosition;              // 
    const float m_BossJumpMaxTime = 3.0f * Manager::Time;    // �ڕW�܂Ŏ��鎞�ԁi���`��ԗp�j

    // QTE�p
    int m_QTEState;                             // QTE�̃X�e�[�g�i���ԁj
    bool m_QTEFinish = false;                   // QTE�C�x���g�������������ǂ���
    float m_QTETime;                            // QTE�p�^�C��
    D3DXVECTOR3 m_QTEInitPos;                   // QTE�p�������W
    D3DXVECTOR3 m_QTETarPos;                    // QTE�p�ړI���W
    D3DXVECTOR3 m_QTECamTar;                    // QTE�p�J�����^�[�Q�b�g
    class Meteor* m_Meteor[3];                  // QTE��覐΍U��
    class Sword* m_PlayerSword;                 // QTE�̃v���C���[�̃\�[�h
    class QTEButton* m_QTEButton;               // QTE�p�{�^��


public:
    // �r�w�C�r�A�c���[�ǉ�
    template<typename T>
    void ChangeBehaviorTree()
    {
        if (m_BehaviorTree != NULL)
        {
            delete m_BehaviorTree;
        }

        T* Behavior = new T();
        Behavior->SetCharacter(this);
        Behavior->SetAnimationTree(m_BossAnimation);
        Behavior->Init();
        m_BehaviorTree = Behavior;
    }

    // �r�w�C�r�A�c���[�`�F�b�N
    template<typename T>
    T* GetBehaviorTree()
    {
        if (typeid(*m_BehaviorTree) == typeid(T))
        {
            return (T*)m_BehaviorTree;
        }

        return NULL;
    }

    void Init() override;
    void Uninit() override;
    void Update() override;
    void DealDamage(float damage) override;
    
    //// �U���ʒm�p�C�x���g
    //void AttackEvent(AttackType AtkType);

    // �U���ʒm�p�C�x���g
    template <typename T>
    void AttackEvent()
    {
        T* Attack = new T();
        Attack->SetCharacter(this);
        Attack->DamageEvent();
        delete Attack;
    }

    // �W�����v�̃A�j���[�V�����ĊJ�ł���
    void SetAlmostJumpFinish();

    // �U�����I��鎞�̏���
    void StartCoolDown();

    // �W�����v�U���ɂ���ăG�t�F�N�g
    void JumpAtkEffect();

    // 覐Ώ����֐�
    void SummonMeteor();
    
    // �v���C���[�̎���ɉ񂷃t�@�C�A�{�[������������
    void ShootSpinningFireBall();

    // �t�@�C�A�{�[���������֐�
    void ShootFireBall();

    // �t�@�C�A�{�[���������i�G���~�[�g�j
    void ShootHermiteBall();

    // �{�X��QTE�C�x���g
    void BossQuickTimeEvent();

    // �N�[���_�E�����Z�b�g
    void SetCoolDown(bool CD) { m_CoolDown = CD; }

    // �U�������Z�b�g
    void SetisAttacking(bool isAttack) { m_isAttacking = isAttack; }

    // ������Hp�̃Z�b�^�[
    void SetHalfHp(bool HalfHp) { m_HalfHp = HalfHp; }

    // �{�X��QTE�X�e�[�g��ς���
    void SetQTEState(int State) { m_QTEState = State; }

    // QTEFinish���Z�b�g
    void SetQTEFinish(bool Finish) { m_QTEFinish = Finish; }

    // �{�X�̒i�K���Z�b�g
    void SetBossPhase(BossPhase Phase) { m_BossPhase = Phase; }

    void SetBossJumpCurTime(float Time) { m_BossJumpCurTime = Time; }

    void SetBossJumpStartPosition(D3DXVECTOR3 Pos) { m_JumpStartPosition = Pos; }

    void SetBossJumpEndPosition(D3DXVECTOR3 Pos) { m_JumpEndPosition = Pos; }

    float GetBossJumpCurTime() { return m_BossJumpCurTime; }

    D3DXVECTOR3 GetBossJumpStartPos() { return m_JumpStartPosition; }

    D3DXVECTOR3 GetBossJumpEndPos() { return m_JumpEndPosition; }

    float GetBossJumpMaxTime() { return m_BossJumpMaxTime; }
    // �^�[�Q�b�gPos���擾
    D3DXVECTOR3 GetTargetPos() { return m_TargetPos; }

    // �N�[���_�E��
    bool GetCoolDown() { return m_CoolDown; }

    // ������Hp���擾
    bool GetHalfHp() { return m_HalfHp; }

    // ���݂�Hp���擾
    float GetCurHp() { return m_CurHp; }

    // �t����Hp���擾
    float GetMaxHp() { return m_MaxHp; }

    // ����ł��Ԃ��擾
    bool GetIsDead() { return m_isDead; }

    // ChaseSpd���擾
    float GetChaseSpd() { return m_ChaseSpd; }

    // ���݂̒i�K���Q�b�g����
    BossPhase GetBossPhase() { return m_BossPhase; }

    // ������������������������������������������������������������������������������������
    // �\����Ԃ̃X�L��

    // �\����Ԃ�覐Ώ���
    void RageSummonMeteor(int Cnt);
    // ������������������������������������������������������������������������������������
};

