


cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}
cbuffer CameraBuffer : register(b5) //バッファの５番とする
{
	float4 CameraPosition; //カメラ座標を受けとる変数
}
cbuffer ParameterBuffer : register(b6)
{
	float4 Parameter;
}
cbuffer PlayerColorBuffer : register(b7)
{
	float4 PlayerColor;
}



struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}




struct LIGHT
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Position;
	float4 Diffuse;
	float4 Ambient;

	matrix View;		// ライトカメラのビュー行列
	matrix Projection;	// ライトカメラのプロジェクション行列
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}





struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
	uint InstanceId		: SV_InstanceID;
};


struct PS_IN
{
	float4 Position		: SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;

	float4 ShadowPosition : POSITION1;	// ライトカメラから見たピクセルの座標
};


 StructuredBuffer<float3> Position : register(t2);