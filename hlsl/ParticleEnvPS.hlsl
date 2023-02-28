//thsozai ==>前回までの状態　ZIP　　パスワード　nabe


//BlinnPhongLightingPS.hlsl
//BlinnPhongLightingVS.hlsl


#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//ピクセルの法線を正規化
	float4 normal = normalize(In.Normal);

	//カメラからピクセルへ向かうベクトル
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する

	//光の反射ベクトルを計算
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //正規化する

	// 反射ベクトルから環境マッピング用のテクスチャ座標を作成
	float2 envTexCoord;	
	envTexCoord.x = -refv.x * -0.5 + 0.5;
	envTexCoord.y = -refv.y * -0.5 + 0.5;

	// スフィアマップとベーステクスチャを取得後に双方を加算して出力
	float4 EnvTex = g_TextureEnv.SampleBias(g_SamplerState, envTexCoord, 0.0f);
	float4 BaseTex = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb = EnvTex + BaseTex;

	// α値の処理　ベースのテクスチャのα値と引数のピクセル色のα値を乗算
	outDiffuse.a = BaseTex.a * In.Diffuse.a;
}


