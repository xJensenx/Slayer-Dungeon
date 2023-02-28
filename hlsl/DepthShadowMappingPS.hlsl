//thsozai ==>前回までの状態　ZIP　　パスワード　nabe


//BlinnPhongLightingPS.hlsl
//BlinnPhongLightingVS.hlsl


#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
//	//===================================================フォッグ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//	//ピクセルの法線を正規化
//	float4 normal = normalize(In.Normal);
//
//	// 光の方向を計算する
//	float4 lightDir = In.WorldPosition - Light.Position;
//	lightDir = normalize(lightDir);
//
//	//光源計算をする
//	float light = -dot(normal.xyz, lightDir.xyz);
//
//	// スポットライトの向きとピクセルへのライトの方向とで内積を計算する
//	float range = dot(Light.Direction.xyz, lightDir.xyz);
//
//	//スペキュラの計算
//	//カメラからピクセルへ向かうベクトル
//	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
//	eyev = normalize(eyev); //正規化する
//	//光の反射ベクトルを計算
//	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
//	refv = normalize(refv); //正規化する
//
//	float specular = -dot(eyev, refv); //鏡面反射の計算
//	specular = saturate(specular); //値をサチュレート
//	specular = pow(specular, 20); //ここでは３０乗してみる
//
//	// 日向での色＝普通のテクスチャ＊頂点色を作成しておく
//	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
//	outDiffuse.rgb *= In.Diffuse.rgb * light;
//	outDiffuse.a *=
//		In.Diffuse.a; //α別計算
//
//	//スペキュラ値をデフューズとして足しこむ
//	outDiffuse.rgb += specular;
//
//	// フォグ
//
//	// カメラからピクセルへの距離を計算する
////	float len = length(v);	// ベクトルの大きさを取得する
//	float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz);	// 二つのベクトルの距離を取得する
//
//	// フォグの影響度を計算する
//	float fogpow = saturate(dist / 30);	// 最大深度
//
//	// 出力する色を変化させる								フォグカラー
//	outDiffuse.rgb = outDiffuse.rgb * (1.0 - fogpow) + float3(0.0, 0.0, 0.0) * fogpow;

	// =============================================================================================フォッグ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝影＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
	// 日向での色＝普通のテクスチャ＊頂点色を作成しておく
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;

	
	In.ShadowPosition.xyz /= In.ShadowPosition.w;				// 投影面でのピクセルの座標つくる
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;		// テクスチャ座標に変換
	In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;		// 

	// シャドウマップテクスチャより、ライトカメラからピクセルまでの距離（深度値）を取得
	float depth = g_TextureShadowDepth.Sample(g_SamplerState, In.ShadowPosition.xy);

	// 取得値が通常カメラからピクセルへの距離より小さい
	if (depth < In.ShadowPosition.z - 0.01)	// 0.01はZファイティング補正値
	{
		outDiffuse.rgb *= 0.5;	// 色を暗くする
	}
}


