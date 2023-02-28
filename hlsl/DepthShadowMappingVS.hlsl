//頂点シェーダー
#include "common.hlsl" //必ずインクルード
//
//in は入力されてくるデーター
//out は出力するデータ
//
void main(in VS_IN In, out PS_IN Out)
{
	//１頂点分のデータを受け取り、処理して、出力する
	//頂点変換処理 この処理は必ず必要
	matrix wvp; //行列変数を作成
	wvp = mul(World, View); //wvp = ワールド行列＊カメラ行列
	wvp = mul(wvp, Projection); //wvp = wvp *プロジェクション行列
	float4 worldNormal, normal;		// 法線のワールド変換
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	// 光源処理
	float light = -dot(Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);
	Out.Diffuse = light;
	Out.Diffuse.a = In.Diffuse.a;

	Out.Position = mul(In.Position, wvp);	// 頂点座標をワールド変換して出力
	Out.Normal = worldNormal;				// 法線を出力
	Out.TexCoord = In.TexCoord;				// テクスチャ座標を出力

	matrix lightwvp;
	lightwvp = mul(World, Light.View);	// ワールド行列 * ライトビュー行列
	lightwvp = mul(lightwvp, Light.Projection);	// さらに * ライトプロジェクション行列

	Out.ShadowPosition = mul(In.Position, lightwvp);	// ライトカメラからみた頂点座標出力
		//ワールド変換した頂点座標を出力
	//Out.WorldPosition = mul(In.Position, World);
}
