#pragma once
#include "GameObject.h"
class TitleCharacter :
    public GameObject
{
private:
    // �I�΂ꂽ�A�j���[�V�����I��������ǂ���
    bool m_AnimationFinish = false;
public:
    void Init() override;
    void Chosen();
    // �A�j���[�V�����I�����
    void SetAnimationFinish() { m_AnimationFinish = true; }
    // �A�j���[�V�����I��������ǂ����Q�b�^�[
    bool CheckFinish();
};

