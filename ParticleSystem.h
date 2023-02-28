#pragma once
#include "Component.h"
#include "ModelRenderer.h"

class ParticleSystem : public Component
{
private:
	// パーティクルの数
	int m_ParticleNum;
	// パーティクルのサイズ
	D3DXVECTOR3 m_ParticleSize;
	// パーティクルの回転の加速度
	D3DXVECTOR3 m_ParticleAccRot;
	// 当たり判定設定
	bool m_ParticleCol;
	// 色の設定
	D3DXCOLOR m_ParticleColor;
	// Emission設定
	D3DXCOLOR m_ParticleEmission;
	// Ambient設定
	D3DXCOLOR m_ParticleAmbient;
	// TitleEffectを付けるかどうか
	bool m_TitleEffect;
	// マテリアルを設置するかどうか
	bool m_UseMaterial;
	// シェーダーの設置
	ModelRenderer::LightningType m_ShaderType;
	// 2Dの設定
	bool m_Particle2D;
	// Particleの使っているモデルかテクスチャの名前
	std::string m_ParticleName;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// パーティクルを生成する
	void SpawnEmitter(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, D3DXVECTOR3 Acc, float Dur);
	
	// パーティクルの数を設置する
	void SetParticleNum(int Num) { m_ParticleNum = Num; }
	// パーティクルのサイズを設置する
	void SetParticleSize(D3DXVECTOR3 Size) { m_ParticleSize = Size; }
	// パーティクルの当たり判定を設置する
	void SetParticleCol(bool Col) { m_ParticleCol = Col; }
	// パーティクルの色設定
	void SetParticleColor(D3DXCOLOR Color) { m_ParticleColor = Color; }
	// パーティクルのAmbient設定
	void SetParticleAmbient(D3DXCOLOR Ambient) { m_ParticleAmbient = Ambient; }
	// パーティクルのEmission設定
	void SetParticleEmission(D3DXCOLOR Emission) { m_ParticleEmission = Emission; }
	// タイトルエフェクトを付ける
	void SetTitleEffect() { m_TitleEffect = true; }
	// マテリアルを設置する
	void SetParticleMaterial(bool useMaterial) { m_UseMaterial = useMaterial; }
	// シェーダーの設置
	void SetParticleShader(ModelRenderer::LightningType Shader) { m_ShaderType = Shader; }
	// 2Dの設置
	void SetParticle2D(bool is2D) { m_Particle2D = is2D; }
	// テクスチャの設定
	void SetParticleName(std::string Name) { m_ParticleName = Name; }
	// パーティクルの回転の加速度をセット
	void SetParticleAccRotation(D3DXVECTOR3 Rotation) { m_ParticleAccRot = Rotation; }
	
	// パーティクルの数をゲットする
	int GetParticleNum() { return m_ParticleNum; }


};

