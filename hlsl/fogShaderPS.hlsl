//thsozai ==>前回までの状態　ZIP　　パスワード　nabe

#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_NormalTexture : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	// このピクセルの法線マップのデータRGBA値を取得
	float4 normalMap =
		g_NormalTexture.Sample(g_SamplerState, In.TexCoord);

	// 取得したスケーリング済RGBA値をベクトル情報XYZWとして元に戻す
	normalMap = normalMap * 2.0 - 1.0;

	// 元に戻したテクスチャRGBAデータを並び替えて法線用変数へ
	float4 normal;
	normal.x = -normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0;
	normal = normalize(normal); // 正規化

	// 光の方向を計算する
	float4 lightDir = In.WorldPosition - Light.Position;
	lightDir = normalize(lightDir);

	//光源計算をする
	float light = -dot(normal.xyz, lightDir.xyz);

	// スポットライトの向きとピクセルへのライトの方向とで内積を計算する
	float range = dot(Light.Direction.xyz, lightDir.xyz);

	//スペキュラの計算
	//カメラからピクセルへ向かうベクトル
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する
	//光の反射ベクトルを計算
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //正規化する

	float specular = -dot(eyev, refv); //鏡面反射の計算
	specular = saturate(specular); //値をサチュレート
	specular = pow(specular, 20); //ここでは３０乗してみる

	//テクスチャのピクセル色を取得
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	// スポットライトの範囲外だったらlightをゼロにする
	//if (range < 0.9)
	//{
	//	light = 0.0;
	//	specular = 0.0;
	//}

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


