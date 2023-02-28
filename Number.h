#pragma once
#include "GameObject.h"
class Number :
    public GameObject
{
private:
    // �X�v���C�g
    std::vector<class SpriteComponent*> m_Number;
    // ��
    int m_Cnt;
    // �O�̐�
    int m_OldCnt;
    // ����
    int m_Numeric;
public:
    void Init() override;
    void Update() override;

    // ����ݒ肷��
    void SetNumber(int Num)
    {
        m_Cnt = Num;
        LoadNumber();
    }

    // �����̐ݒ�
    void SetNumeric(int Num) { m_Numeric = Num; }

    // �X�v���C�g�̃��[�h
    void LoadNumber();
};

