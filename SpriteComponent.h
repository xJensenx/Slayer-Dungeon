#pragma once
#include "Component.h"
class SpriteComponent :
    public Component
{
public:
	enum SpriteType
	{
		None = 0,
		BilBoard,
		AnimationBilBoard,
		ProgressBarBilBoard,
		ProgressBar,
		WarningBilBoard
	};
private:
	// 頂点バッファ
	ID3D11Buffer* m_VertexBuffer = NULL;

	// テクスチャ名前（unordered_map用）
	std::string m_Name;
	// シェーダー名前（unordered_map用）
	std::string m_ShaderName;
	// ノーマルテクスチャ名前（unordered_map用）
	std::string m_NormalName;
	

	// 色
	D3DXVECTOR4 m_Color;
	// テクスチャ座標
	D3DXVECTOR2 m_TexCoord;
	// テクスチャのUV
	D3DXVECTOR2 m_UV;

	// オフセット
	D3DXVECTOR3 m_Offset;

	// サイズOffset
	D3DXVECTOR3 m_SizeOffset;

	// テクスチャ
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;
	// ノーマルテクスチャ
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_NormalTexture;

	// 頂点シェーダー
	static std::unordered_map<std::string, ID3D11VertexShader*> m_VertexShader;
	// ピクセルシェーダー
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShader;
	// 頂点レイアウト
	static std::unordered_map<std::string, ID3D11InputLayout*> m_VertexLayout;

	ID3D11Buffer* m_PositionBuffer;
	ID3D11ShaderResourceView* m_PositionSRV;

	// スプライトの種類
	SpriteType m_SpriteType;

	// 見えるかどうか
	bool m_Visible = true;

	// ノーマルテクスチャUV値
	D3DXVECTOR4 m_NormalUV;

public:
	// テクスチャやシェーダーのロード
	static void Load();
	// テクスチャやシェーダーの解放
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	// 頂点などの初期化
	void LoadInfo(std::string Name, std::string Shader, D3DXVECTOR2 UV);
	// 色の調整
	void SetColor(D3DXVECTOR4 Color)
	{
		m_Color = Color;
	}
	// スプライトの種類を設置する
	void SetSpriteType(SpriteType ST)
	{
		m_SpriteType = ST;
	}
	// 可視の設置
	void SetVisibility(bool Visible) { m_Visible = Visible; }
	// UV値の設置
	void SetUV(D3DXVECTOR2 UV) { m_UV = UV; }
	// テクスチャ座標の設置
	void SetTexCoord(D3DXVECTOR2 TexCo) { m_TexCoord = TexCo; }
	// Offsetのセッター
	void SetOffSet(D3DXVECTOR3 Offset) { m_Offset = Offset; }
	// SizeOffsetのセッター
	void SetSizeOffset(D3DXVECTOR3 SizeOffset) { m_SizeOffset = SizeOffset; }
	// ノーマルをセットする
	void SetNormalTexture(std::string NormalName);


	// 色のゲッター
	D3DXVECTOR4 GetColor() { return m_Color; }
};

