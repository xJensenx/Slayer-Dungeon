#pragma once
#include "GameObject.h"
class SettingAdjustButton :
    public GameObject
{
private:
    // ��������UI�N���X
    class SettingUI* m_ControlUI;
    // �O�̒l�̎��̍��W
    D3DXVECTOR3 m_InitPos;
    // �P�̒l�̎��̍��W
    D3DXVECTOR3 m_TarPos;
    // �l�i0.0�`1.0�j
    float m_Value;

    // �I������Ă��鎞�̃X�v���C�g
    class SpriteComponent* m_Sprite;
    // �I������ĂȂ����̃X�v���C�g
    class SpriteComponent* m_NSSprite;

    // �I������Ă���ꍇ
    bool m_Chosen;
    // �����Ă���ꍇ
    bool m_isClick;

public:
    void Init() override;
    void Update() override;

    // ��������UI�N���X��ݒu
    void SetControlUI(class SettingUI* _UI) { m_ControlUI = _UI; }
    // �������W��ݒu
    void SetBothPos(D3DXVECTOR3 _Init, D3DXVECTOR3 _Tar) { m_InitPos = _Init; m_TarPos = _Tar; }
    // �I������Ă���Z�b�^�[
    void SetChosen(bool Chose) { m_Chosen = Chose; }
    // �l�̃Z�b�^�[
    void SetValue(float Val) { m_Value = Val; }

    // �I������Ă���Q�b�^�[
    bool GetChosen() { return m_Chosen; }
    // �l���擾
    float GetValue() { return m_Value; }

};

