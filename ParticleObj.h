#pragma once
#include "GameObject.h"
#include "ModelRenderer.h"

class ParticleObj :
    public GameObject
{
public:
private:
    // 存在する時間
    float m_Duration;
    // 当たり判定あるかどうか
    bool m_Collision;
    // タイトルロゴのエフェクト
    bool m_Title;
    // タイトルエフェクトの初期座標
    D3DXVECTOR3 m_TitlePos;
    // 回転の加速度
    D3DXVECTOR3 m_AccRotation;
    // タイトルエフェクト挙動Lerp用
    float m_SinValue;
    // タイトルエフェクトステート
    int m_TitleState;
    // 2Dか3D
    bool m_Particle2D;

public:
    void Init() override;
    void Update() override;

    // 存在する時間を設置する
    void SetDuration(float Duration) { m_Duration = Duration * Manager::Time; }
    // シェーダーの設置
    void SetShader(ModelRenderer::LightningType ShaderType);
    // マテリアルの設置
    void SetMaterial(bool On);
    // 当たり判定を設置する
    void SetCollision(bool Col) { m_Collision = Col; }
    // 色の設定
    void SetColor(D3DXCOLOR Color, D3DXCOLOR Ambient, D3DXCOLOR Emission);
    // タイトルエフェクトを設置する
    void SetTitleEffect() { m_Title = true; m_TitlePos = m_Position; }
    // Set2D
    void Set2DParticle();
    // 名前をセット
    void SetParticleName(std::string Name);
    // 回転の加速度をセット
    void SetAccRotation(D3DXVECTOR3 Acc) { m_AccRotation = Acc; }

    // タイトルエフェクトの挙動
    void TitleEffectMovement();
    

};

