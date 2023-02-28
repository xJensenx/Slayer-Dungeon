#pragma once
#include "GameObject.h"
#include "MinionBehaviorTree.h"

class Minion :
    public GameObject
{
private:
    // Minion�̃r�w�C�r�A�c���[
    class MinionBehaviorTree* m_Behavior;

    // Minion�̃A�j���[�V����
    class MinionAnimation* m_Animation = NULL;

    // Minion�̈ړ��X�s�[�h
    float m_MovementSpd = 0.075f;

    // Minion�̍U���N�[���_�E��
    float m_AttackCD = 3.0f * Manager::Time;

    // �U�����Ă��邩�ǂ���
    bool m_isAttacking;

    // 
    float m_WaitTime;

    // �ő�Hp
    float m_MaxHp = 10.0f;

    // ����Hp
    float m_CurHp;

    // ��������ł邩�ǂ���
    bool m_isDead;

    // HpBar
    class MinionHpBar* m_HpBar;
public:
    void Init() override;       // ����������
    void Update() override;     // �X�V����

    // �r�w�C�r�A�c���[��ύX
    template <typename T>
    void ChangeBehavior()
    {
        // �r�w�C�r�A�c���[���ɂ�����ꍇ�͍폜����
        if (m_Behavior != NULL)
        {
            delete m_Behavior;
            m_Behavior = NULL;
        }

        T* NewBehavior = new T();
        NewBehavior->SetCharacter(this);
        NewBehavior->SetAnimationTree(m_Animation);
        NewBehavior->Init();

        m_Behavior = NewBehavior;
    }

    // �r�w�C�r�A�c���[
    void BehaviorTree();

    // �U���ʒm�p�C�x���g
    void AttackEvent();

    // �U��CD���Z�b�g
    void SetAttackCD(float CD) { m_AttackCD = CD * Manager::Time; }

    // �U�������Z�b�g
    void SetisAttacking(bool Attack) { m_isAttacking = Attack; }

    //// �U����������
    //void SetAttackMode(MinionBehavior MB)
    //{
    //    m_State = MB;
    //}

    // �_���[�W�󂯂���
    void DealDamage(float Damage) override;

    // Minion�̌��݂�Hp�̃Q�b�^�[
    float GetCurrentHp() { return m_CurHp; }

    // Minion�̍ő��Hp�̃Q�b�^�[
    float GetMaxHp() { return m_MaxHp; }

    // Minion�̍U��CD���擾
    float GetAttackCD() { return m_AttackCD; }

    // Minion�̍U�������擾
    bool GetisAttacking() { return m_isAttacking; }

    // Minion���|���ꂽ���ǂ���
    bool GetisDead() { return m_isDead; }
};

