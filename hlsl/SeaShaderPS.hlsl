#include "common.hlsl"

// 法線マップ用のテクスチャ変数を追加
Texture2D g_Texture : register(t0); // 通常のテクスチャ用
Texture2D g_TextureNormal : register(t1); // 法線マップ用
Texture2D g_SecondNormal: register(t3);

// サンプラーステートの０番スロットを使う
SamplerState g_SamplerState : register(s0); // これは１つでok
// サンプラーステートの１番スロットを使う場合
// SamplerState g_SamplerState1 : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float2 uv = In.TexCoord;
	uv.x += Parameter.x;
	uv.y += Parameter.x;

	float2 SecUV = In.TexCoord;
	SecUV.x -= Parameter.x;
	SecUV.y -= Parameter.y;

	// このピクセルの法線マップのデータRGBA値を取得
	float4 normalMap =
		g_TextureNormal.Sample(g_SamplerState, uv);
	float4 SecNormal =
		g_SecondNormal.Sample(g_SamplerState, SecUV);

	// 取得したスケーリング済RGBA値をベクトル情報XYZWとして元に戻す
	normalMap = normalMap * 2.0 - 1.0;
	SecNormal = SecNormal * 2.0 - 1.0;

	normalMap *= SecNormal;

	// 元に戻したテクスチャRGBAデータを並び替えて法線用変数へ
	float4 normal;
	normal.x = -normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0;
	normal = normalize(normal); // 正規化

	float4 Second;
	Second.x = -SecNormal.r;
	Second.y = SecNormal.b;
	Second.z = SecNormal.g;
	Second.w = 0.0;
	Second = normalize(Second);

	//光源計算をする
	float light = -dot(Light.Direction.xyz, normal.xyz);
	//float light = -dot(normal.xyz, Light.Direction.xyz);


	//スペキュラの計算
	//カメラからピクセルへ向かうベクトル
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する
	//光の反射ベクトルを計算
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //正規化する

	float specular = -dot(eyev, refv); //鏡面反射の計算
	specular = saturate(specular); //値をサチュレート
	specular = pow(specular, 30); //ここでは３０乗してみる


	//テクスチャのピクセル色を取得
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	outDiffuse.rgb *=
		In.Diffuse.rgb * light; //明るさと色を乗算
	outDiffuse.a *=
		In.Diffuse.a; //α別計算

	//スペキュラ値をデフューズとして足しこむ
	outDiffuse.rgb += specular;


	// フォグ

	// カメラからピクセルへの距離を計算する
//	float len = length(v);	// ベクトルの大きさを取得する
	float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz);	// 二つのベクトルの距離を取得する

	// フォグの影響度を計算する
	float fogpow = saturate(dist / 100);	// 最大深度

	// 出力する色を変化させる								フォグカラー
	outDiffuse.rgb = outDiffuse.rgb * (1.0 - fogpow) + float3(1.0, 1.0, 1.0) * fogpow;
}