#pragma once
#include "Scene.h"
#include "Title.h"
#include "Game.h"
#include "Tutorial.h"

class LoadingScene :
    public Scene
{
private:
    // ���[�h�������������ǂ���
    static bool m_LoadFinish;

    // ���̃V�[��
    static class LoadingType* m_LoadNext;

public:
    static void SetLoadFinish(bool Status) { m_LoadFinish = Status; }
    static bool GetLoadFinish() { return m_LoadFinish; }

    void Init() override;
    void Uninit() override;
    void Update() override;

    // ���̃V�[�����Z�b�g
    template <typename T>
    static void SetNextScene()
    {
        if (m_LoadNext != NULL)
        {
            delete m_LoadNext;
            m_LoadNext = NULL;
        }

        T* NextScene = new T();
        m_LoadNext = NextScene;
    }

};

class LoadingType
{
public:
    LoadingType() {}
    ~LoadingType() {}

    // �V�[���̃A�Z�b�g�����[�h����
    virtual void LoadAsset() = 0;
    // �V�[�������[�h����
    virtual void LoadScene() = 0;
};

class LoadingType_Title : public LoadingType
{
public:
    void LoadAsset() override;
    void LoadScene() override;
};

class LoadingType_Game : public LoadingType
{
public:
    void LoadAsset() override;
    void LoadScene() override;
};

class LoadingType_Tutorial : public LoadingType
{
public:
    void LoadAsset() override;
    void LoadScene() override;
};