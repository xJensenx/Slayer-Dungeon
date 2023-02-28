//thsozai ==>�O��܂ł̏�ԁ@ZIP�@�@�p�X���[�h�@nabe


//BlinnPhongLightingPS.hlsl
//BlinnPhongLightingVS.hlsl


#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�s�N�Z���̖@���𐳋K��
	float4 normal = normalize(In.Normal);

	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������

	//���̔��˃x�N�g�����v�Z
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //���K������

	// ���˃x�N�g��������}�b�s���O�p�̃e�N�X�`�����W���쐬
	float2 envTexCoord;	
	envTexCoord.x = -refv.x * -0.5 + 0.5;
	envTexCoord.y = -refv.y * -0.5 + 0.5;

	// �X�t�B�A�}�b�v�ƃx�[�X�e�N�X�`�����擾��ɑo�������Z���ďo��
	float4 EnvTex = g_TextureEnv.SampleBias(g_SamplerState, envTexCoord, 0.0f);
	float4 BaseTex = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb = EnvTex + BaseTex;

	// ���l�̏����@�x�[�X�̃e�N�X�`���̃��l�ƈ����̃s�N�Z���F�̃��l����Z
	outDiffuse.a = BaseTex.a * In.Diffuse.a;
}


