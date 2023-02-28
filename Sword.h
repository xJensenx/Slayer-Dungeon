#pragma once
#include "GameObject.h"
#include "SwordStatus.h"

class Sword :
    public GameObject
{
public:
    // ���̌����ǂ̈ʒu�ɂ��邩
    enum SwordPosition
    {
        First = 0,
        Second,
        Third,
        Fourth,
        Fifth
    };

private:
    class SwordStatus* m_SwordStatus;

    class SwordTrail* m_SwordTrail;

    // �v���C���[�N���X
    class Player* m_Character = NULL;
    // ���̈ʒu
    SwordPosition m_SwordPos;
    // �ł��̌��ݎ���
    float m_CurShootTime;
    // �ڕW�܂œ��B����܂ł̎���
    const float m_TotalShootTime = 1.0f * Manager::Time;
    // �h��̎��������鎞��
    const float m_TotalBlockTime = 0.2f * Manager::Time;
    // �ҋ@��Ԃɖ߂鎞��
    const float m_TotalIdleTime = 0.2f * Manager::Time;
    // �ڕW
    class GameObject* m_TargetObj = NULL;
    // �ڕW�^�[�Q�b�g�n�_
    D3DXVECTOR3 m_TargetPos;
    // �U������
    float m_TotalAttackTime;
    // �����|�W�V����
    D3DXVECTOR3 m_InitPos;
    // �������[�e�[�V����
    D3DXVECTOR3 m_InitRot;
    // �ŏ���Up���擾
    D3DXVECTOR3 m_InitUp;
    // �ڕW�|�W�V�����i�U���p�j
    D3DXVECTOR3 m_EndPos;
    // �ڕWTangent�i�U���p�j
    D3DXVECTOR3 m_EndTan;
    // �U�������������ǂ���
    bool m_Damaged;
    // �U����
    float m_AtkDmg;
    // Ult�̃J�����V�F�[�N
    bool m_isShake;
    // �V�F�[�N�̋���
    float m_ShakeStr;
    // ���̋O�Ղ̐F
    D3DXVECTOR4 m_SwordTrailColor;
    // Skill06�̌���
    int m_ShootCnt;
    
    // �ҋ@��Ԃ̃A�j���[�V�����p����
    float m_IdleAnimTime;
    int m_IdleState;

public:
    void Init() override;
    void Uninit() override;
    void Update() override;

    // �\�[�h�X�e�[�^�X��ǉ�
    template <typename T>
    T* SetSwordStatus()
    {
        if (m_SwordStatus != NULL)
        {
            delete m_SwordStatus;
            m_SwordStatus = NULL;
        }

        T* Stat = new T();
        Stat->SetCharacter(this);
        Stat->Init();
        m_SwordStatus = Stat;
        return (T*)m_SwordStatus;
    }
    // �g���[����������
    void InitSwordTrail();

    void SetCharacter(Player* P, SwordPosition SP);

    // Skill06�̌�������
    void ShootSwordSkill06(GameObject* Target, int ShootCnt)
    {
        m_TargetObj = Target;
        m_InitUp = GetQuaternionUp();
        m_ShootCnt = ShootCnt;
        SetSwordStatus<SwordSkill06>();
    }
    // Skill06�̌�������
    void ShootSwordSkill06(D3DXVECTOR3 Target, int ShootCnt)
    {
        m_TargetPos = Target;
        m_InitUp = GetQuaternionUp();
        m_ShootCnt = ShootCnt;
        SetSwordStatus<SwordSkill06>();
    }

    // �����ˏo����
    void ShootSword(GameObject* Target)
    {
        m_TargetObj = Target;
        m_CurShootTime = 0.0f;
        m_InitPos = m_Position;
        m_InitUp = GetQuaternionUp();
        SetSwordStatus<SwordShoot>();
    }
    // �����ˏo����
    void ShootSword(D3DXVECTOR3 Target)
    {
        m_TargetPos = Target;
        m_CurShootTime = 0.0f;
        m_InitPos = m_Position;
        m_InitUp = GetQuaternionUp();
        SetSwordStatus<SwordShoot>();
    }
    // ���𒼐��Ŏˏo
    void ShootStraightSword(D3DXVECTOR3 Target)
    {
        m_TargetPos = Target;
        m_CurShootTime = 0.0f;
        m_InitPos = m_Position;
        SetSwordStatus<SwordShootStraight>();
    }

    // ���ōU������
    void AttackSword(D3DXVECTOR3 InitPos, D3DXVECTOR3 InitTan, D3DXVECTOR3 EndPos, D3DXVECTOR3 EndTan, float AtkTime)
    {
        m_Damaged = false;
        m_InitPos = InitPos;
        m_InitUp = InitTan;
        m_EndPos = EndPos;
        m_EndTan = EndTan;
        m_CurShootTime = 0.0f;
        m_TotalAttackTime = AtkTime * Manager::Time;

        SetSwordStatus<SwordAttack>();
    }

    // ���ōU������
    void AttackSword_Skill(D3DXVECTOR3 InitPos, D3DXVECTOR3 InitTan, D3DXVECTOR3 EndPos, D3DXVECTOR3 EndTan, float AtkTime)
    {
        m_Damaged = false;
        m_InitPos = InitPos;
        m_InitUp = InitTan;
        m_EndPos = EndPos;
        m_EndTan = EndTan;
        m_CurShootTime = 0.0f;
        m_TotalAttackTime = AtkTime * Manager::Time;

        SetSwordStatus<SwordAttack_ForSkill>();
    }

    // ���Ŗh�䂷��
    void DefenseSword(D3DXVECTOR3 InitPos, D3DXVECTOR3 InitRot)
    {
        m_InitPos = InitPos;
        m_InitRot = InitRot;
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordBlock>();
    }

    // QTE�̌��̎ˏo
    void QTEShootSword(D3DXVECTOR3 Tar)
    {
        m_InitPos = m_Position;
        m_EndPos = Tar;
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordQTE>();
    }

    // �ҋ@��Ԃɖ߂�
    void BackToIdle()
    {
        m_InitPos = m_Position;
        m_InitRot = m_Rotation;
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordIdle>();
    }

    // ����Ult���g��
    void UltSword()
    {
        m_CurShootTime = 0.0f;

        SetSwordStatus<SwordUlt>();
    }

    // �U���͂��Z�b�g
    void SetAtkDmg(float AtkDmg) { m_AtkDmg = AtkDmg; }

    // ���̋O�Ղ̐F�𒲐�
    void ChangeTrailColor(D3DXVECTOR4 _Color) { m_SwordTrailColor = _Color; }

    // TrailRenderer�i���̋O�Ձj
    void TrailEffect();
    
    // HitEffect
    void HitEffect(D3DXVECTOR3 HitPos);
    
    // DissolveEffect
    void DissolveEffect();

    void SetIdleAnimTime(float T) { m_IdleAnimTime = T; }

    // ShakeStr��ݒu����
    void SetShakeStr(float ShakeStr) { m_ShakeStr = ShakeStr; }

    //
    class GameObject* GetTargetObj() { return m_TargetObj; }

    // �L�����N�^�[���Q�b�g
    class Player* GetCharacter() { return m_Character; }

    //
    D3DXVECTOR3 GetTargetPos() { return m_TargetPos; }

    // 
    D3DXVECTOR3 GetInitUp() { return m_InitUp; }

    //
    D3DXVECTOR3 GetEndPos() { return m_EndPos; }

    D3DXVECTOR3 GetEndTan() { return m_EndTan; }

    float GetTotalAtkTime() { return m_TotalAttackTime; }

    float GetShakeStr() { return m_ShakeStr; }

    int GetShootCnt() { return m_ShootCnt; }

    // �U���͂��擾
    float GetAtkDmg() { return m_AtkDmg; }

    // �\�[�h�̒u���ʒu���Q�b�g
    SwordPosition GetSwordPos() { return m_SwordPos; }
};

