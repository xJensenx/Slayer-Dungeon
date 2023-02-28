#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureToon : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�s�N�Z���̖@���𐳋K��
	float4 normal = normalize(In.Normal);
	//�����v�Z������
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
	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	// ���邳�̒l��K���ɃN�����v����
	float min = 0.05;
	float max = 0.95;
	light = clamp(light, min, max);

	//// ���邳���e�L�X�`���[���W�Ƃ��ăe�L�X�`���[����F���擾
	float2 ToonTexCoord;
	ToonTexCoord.x = light;
	ToonTexCoord.y = 0.5;

	float4 ToonColor;
	ToonColor = g_TextureToon.Sample(g_SamplerState, ToonTexCoord);

	 //�擾�����F���A�o�͐F�f�[�^�ɏ�Z����
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
		In.Diffuse.a; //���ʌv�Z

	//�֊s�������
	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������

	float d = -dot(eyev, normal.xyz);

	if (d < 0.4)
	{
		outDiffuse.g *= 0.0;
		outDiffuse.r *= 0.0;
		outDiffuse.b *= 1.0;
	}
}


