#pragma once
#include "GameObject.h"
class MouseCursor :
    public GameObject
{
private:
    // �X�v���C�g
    class SpriteComponent* m_MouseCursor;
    class SpriteComponent* m_ClickCursor;

    // �}�E�X�J�[�\�����\�����Ă��邩�ǂ���
    static bool m_Visibility;
public:
    void Init() override;
    void Update() override;

    // �}�E�X�J�[�\����\������̐ݒ�
    static void SetVisibility(bool Visible) { m_Visibility = Visible; }
};

