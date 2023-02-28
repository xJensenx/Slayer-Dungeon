#pragma once
#include <unordered_map>
#include "Component.h"
class ModelRenderer : public Component
{
public:
	enum LightningType
	{
		UnlitType = 0,
		LitType,
		FogType,
		ShadowType,
		ToonType,
		EnvType,
		ParticleEnvType,
		RimType,
		TitleGroundType,
		FireBallType
	};
private:
	LightningType m_LightningType = UnlitType;

	std::string m_Name;
	std::string m_ShaderName;
	std::string m_NormalTextureName;
	// 見えるかどうか
	bool m_Visibility = true;

	// ノーマルテクスチャ使っているかどうか
	bool m_UseNormal = false;

	// マテリアルを上書きしますか
	bool m_ChangeMaterial = false;

	// Quaternion使用しているかどうか
	bool m_UseQuaternion;

	// Parameter
	D3DXVECTOR4 m_Parameter;
	
	// マテリアル用
	D3DXCOLOR m_Ambient;
	D3DXCOLOR m_Emission;
	D3DXCOLOR m_Diffuse;

	// モデル
	static std::unordered_map<std::string, class Model*>m_Model;
	// 事前にロードするテクスチャ
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_LoadTexture;
	// モデルのサイズ
	static std::unordered_map<std::string, D3DXVECTOR3> m_ModelSize;

	// 頂点シェーダー
	static std::unordered_map<std::string, ID3D11VertexShader*> m_VertexShader;
	// ピクセルシェーダー
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShader;
	// 頂点レイアウト
	static std::unordered_map<std::string, ID3D11InputLayout*> m_VertexLayout;

	// 全ての頂点の座標
	std::vector<D3DXVECTOR3> m_VertexPosition;

public:
	// モデルやテクスチャをロードする
	static void Load();
	// モデルやテクスチャをアンロードする
	static void Unload();
	// ゲーム内のモデルやテクスチャをロードする
	static void LoadGameAsset();
	// ゲーム内のモデルやテクスチャをアンロードする
	static void UnloadGameAsset();
	// 初期化処理
	void Init() override;
	// 終了処理
	void Uninit() override;
	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;
	// モデルをセットする
	void SetModel(std::string _Name, LightningType _Type);
	// Ambientをセットする
	void SetAmbient(D3DXCOLOR Ambient) { m_Ambient = Ambient; }
	// Emissionをセットする
	void SetEmission(D3DXCOLOR Emission) { m_Emission = Emission; }
	// Diffuseをセットする
	void SetDiffuse(D3DXCOLOR Diffuse) { m_Diffuse = Diffuse; }
	// Material使っているのをセットする
	void SetUseMaterial(bool useMaterial) { m_ChangeMaterial = useMaterial; }
	// ノーマルテクスチャをセットする
	void SetTexture(std::string Name) { m_NormalTextureName = Name; m_UseNormal = true; }
	// 見えるかどうかをセットする
	void SetVisibility(bool Visible) { m_Visibility = Visible; }
	// Quaternion使っているかどうか
	void SetQuaternion(bool Qua) { m_UseQuaternion = Qua; }
	// Parameterをセット
	void SetParameter(D3DXVECTOR4 Par) { m_Parameter = Par; }
	// モデルサイズを取得
	D3DXVECTOR3 GetModelSize(std::string _Name) { return m_ModelSize[_Name]; }
	// 全部の頂点座標を取得
	std::vector<D3DXVECTOR3> GetVertexPosition() { return m_VertexPosition; }
	// Parameterを取得
	D3DXVECTOR4 GetParameter() { return m_Parameter; }


};