#pragma once
#include <unordered_map>
#include "Component.h"

class SpriteRenderer : public Component
{
public:
	enum LightningType
	{
		UnlitType = 0,
		LitType,
	};
	enum SpriteType
	{
		Dynamic = 0,
		Kinematic,
		Bilboard,
		Double,
		Shadow
	};
	enum SpriteAnimation
	{
		NoEffect = 0,
		DynamicEffect,
		LoopEffect,
		FadeEffect
	};
private:
	LightningType m_LightningType = LightningType::UnlitType;
	SpriteType m_SpriteType = SpriteType::Dynamic;
	SpriteAnimation m_SpriteAnimation = SpriteAnimation::NoEffect;

	ID3D11Buffer* m_VertexBuffer = NULL;
	//ID3D11ShaderResourceView* m_Texture = NULL;

	//ID3D11VertexShader* m_VertexShader = NULL;
	//ID3D11PixelShader* m_PixelShader = NULL;
	//ID3D11InputLayout* m_VertexLayout = NULL;

	static ID3D11VertexShader* m_LitVertexShader;
	static ID3D11PixelShader* m_LitPixelShader;
	static ID3D11InputLayout* m_LitVertexLayout;

	static ID3D11VertexShader* m_UnlitVertexShader;
	static ID3D11PixelShader* m_UnlitPixelShader;
	static ID3D11InputLayout* m_UnlitVertexLayout;

	static ID3D11VertexShader*	m_NormalVertexShader;
	static ID3D11PixelShader*	m_NormalPixelShader;
	static ID3D11InputLayout*	m_NormalVertexLayout;

	D3DXVECTOR3 m_VertexSize;
	D3DXVECTOR3 m_Normal;
	D3DXVECTOR2 m_TexCoord;

	int m_Cnt;
	
	std::string m_Map;
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_TextureMap;



public:
	static void Load();
	static void Unload();
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void LoadInfo();

	void SetInfo(std::string _Name, LightningType _LT,SpriteType _ST,SpriteAnimation _SA,
		D3DXVECTOR3 _Size, D3DXVECTOR3 _Normal, D3DXVECTOR2 _TexCoord)
	{
		m_Map = _Name;
		m_LightningType = _LT;
		m_SpriteType = _ST;
		m_SpriteAnimation = _SA;
		m_VertexSize = _Size;
		m_Normal = _Normal;
		m_TexCoord = _TexCoord;

		LoadInfo();
	}
};

