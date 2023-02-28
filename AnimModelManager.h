#pragma once
#include "Component.h"
#include <unordered_map>

class AnimModelManager :
    public Component
{
public:
    enum LightningType
    {
        LitType = 0,
        UnlitType,
        ShadowType,
        BlinnPhongType,
        FogType,
        ToonType,
        PlayerType
    };
private:
    // アニメーションの名前
    std::string m_Name;

    std::string m_NormalTextureName;
    // シェーダーの名前
    std::string m_ShaderName;
    // 前のアニメーション
    const char* m_AnimationName1;
    // 今のアニメーション
    const char* m_AnimationName2;
    // ブレンドレート
    float m_BlendRate;
    // 前のフレーム数
    float m_Frame1 = 0;
    // 今のフレーム数
    float m_Frame2 = 0;

    bool m_UseNormal;

    LightningType m_LightningType = LitType;

    D3DXVECTOR4 m_PlayerColor;

    // アニメーションモデル
    static std::unordered_map<std::string, class AnimationModel*> m_AnimModel;

    static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_LoadTexture;
    // アニメーションモデルサイズ
    static std::unordered_map<std::string, D3DXVECTOR3> m_ModelSize;

    // シェーダー
    static std::unordered_map<std::string, ID3D11VertexShader*> m_VertexShader;
    static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShader;
    static std::unordered_map<std::string, ID3D11InputLayout*> m_VertexLayout;

public:
    static void Load();
    static void LoadGameAsset();
    static void Unload();
    static void UnloadGameAsset();
    void Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;

    void SetTexture(std::string _Name) { m_NormalTextureName = _Name; m_UseNormal = true; }

    void SetModel(std::string _Name, LightningType _Lit) 
    {
        m_Name = _Name;
        m_LightningType = _Lit;

        switch (m_LightningType)
        {
        case UnlitType:
            m_ShaderName = "Unlit";
            break;
        case LitType:
            m_ShaderName = "Lit";
            break;
        case ShadowType:
            m_ShaderName = "Shadow";
            break;
        case BlinnPhongType:
            m_ShaderName = "BlinnPhong";
            break;
        case FogType:
            m_ShaderName = "FogShader";
            break;
        case ToonType:
            m_ShaderName = "Toon";
            break;
        case PlayerType:
            m_ShaderName = "Player";
            break;
        }
    }
    void LoadAnimation(const char* AnimationName1, const char* AnimationName2)
    {
        m_AnimationName1 = AnimationName1;
        m_AnimationName2 = AnimationName2;
    }

    void SetPlayerColor(D3DXVECTOR4 Color)
    {
        m_PlayerColor = Color;
    }

    void SetBlendRate(float Rate)
    {
        m_BlendRate = Rate;
    }
    
    void SetFrame(float Frame1,float Frame2)
    {
        m_Frame1 = Frame1;
        m_Frame2 = Frame2;
    }
    
    float GetBlendRate()
    {
        return m_BlendRate;
    }

    float GetAnimDuration(const char* AnimationName);
    
    D3DXVECTOR3 GetAnimModelSize() { return m_ModelSize[m_Name]; }
};

