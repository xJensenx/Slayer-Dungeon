#pragma once
#include "GameObject.h"
#include "PauseMenuUIType.h"

class PauseMenuUI :
    public GameObject
{
private:
    // UI�̎��
    class PauseMenuUIType* m_UIType;

    // �I������Ă���X�v���C�g
    class SpriteComponent* m_Sprite;
    // �I������Ă��Ȃ��X�v���C�g
    class SpriteComponent* m_NSSprite;

    // �I������Ă��邩�ǂ���
    bool m_Chosen;

public:
    void Init() override;
    void Update() override;

    // ��ނ̃Z�b�^�[
    template <typename T>
    void SetType()
    {
        T* Type = new T();
        Type->SetCharacter(this);
        Type->Init();
        m_UIType = Type;
    }

    // ��ނ̃Q�b�^�[
    template <typename T>
    T* GetType()
    {
        if (typeid(*m_UIType) == typeid(T))
        {
            return (T*)m_UIType;
        }

        return NULL;
    }

    // �I������Ă���X�v���C�g�̃Q�b�^�[
    class SpriteComponent* GetSprite() { return m_Sprite; }

    // �I������Ă��Ȃ��X�v���C�g�̃Q�b�^�[
    class SpriteComponent* GetNSSprite() { return m_NSSprite; }

    // �I�΂�Ă���̃Z�b�^�[
    void SetChosen(bool Chosen) { m_Chosen = Chosen; }

    // �I�΂�Ă���̃Q�b�^�[
    bool GetChosen() { return m_Chosen; }
};

