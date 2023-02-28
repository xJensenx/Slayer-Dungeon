#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureToon : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//ピクセルの法線を正規化
	float4 normal = normalize(In.Normal);
	//光源計算をする
	float light = -dot(normal.xyz, Light.Direction.xyz);

	//if (light > 0.7)
	//{
	//	light = 1.0;
	//}
	//else if (light > 0.5)
	//{
	//	light = 0.8;
	//}
	//else
	//{
	//	light = 0.4;
	//}
	// 
	//テクスチャのピクセル色を取得
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	// 明るさの値を適当にクランプする
	float min = 0.05;
	float max = 0.95;
	light = clamp(light, min, max);

	//// 明るさをテキスチャー座標としてテキスチャーから色を取得
	float2 ToonTexCoord;
	ToonTexCoord.x = light;
	ToonTexCoord.y = 0.5;

	float4 ToonColor;
	ToonColor = g_TextureToon.Sample(g_SamplerState, ToonTexCoord);

	 //取得した色を、出力色データに乗算する
	outDiffuse.rgb *=
		In.Diffuse.rgb * ToonColor.rgb;

	//float2 uv = light;
	//uv.x += Parameter.x;
	//uv.y = Parameter.y;



	//float4 ToonColor;
	//ToonColor = g_TextureToon.Sample(g_SamplerState, uv);


	//outDiffuse.rgb *=
	//	saturate(In.Diffuse.rgb * ToonColor.rgb);
	outDiffuse.a *= 
		In.Diffuse.a; //α別計算

	//輪郭線を作る
	//カメラからピクセルへ向かうベクトル
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する

	float d = -dot(eyev, normal.xyz);

	if (d < 0.4)
	{
		outDiffuse.g *= 0.0;
		outDiffuse.r *= 0.0;
		outDiffuse.b *= 1.0;
	}
}


