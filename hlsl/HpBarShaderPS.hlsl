#include "common.hlsl"

// 法線マップ用のテクスチャ変数を追加
Texture2D g_Texture : register(t0); // 通常のテクスチャ用
Texture2D g_TextureNormal : register(t1); // 法線マップ用

// サンプラーステートの０番スロットを使う
SamplerState g_SamplerState : register(s0); // これは１つでok
// サンプラーステートの１番スロットを使う場合
// SamplerState g_SamplerState1 : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float2 uv = In.TexCoord;
	uv.x += Parameter.x;
	uv.y += Parameter.x;

	// このピクセルの法線マップのデータRGBA値を取得
	float4 normalMap =
		g_TextureNormal.Sample(g_SamplerState, uv);

	//テクスチャのピクセル色を取得
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	outDiffuse.rgb *=
		mul(In.Diffuse.rgb, normalMap); //明るさと色を乗算
	outDiffuse.a *=
		In.Diffuse.a; //α別計算
}