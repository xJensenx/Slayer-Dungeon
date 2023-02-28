#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_NormalTexture : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	// ���̃s�N�Z���̖@���}�b�v�̃f�[�^RGBA�l���擾
	float4 normalMap =
		g_NormalTexture.Sample(g_SamplerState, In.TexCoord);

	// �擾�����X�P�[�����O��RGBA�l���x�N�g�����XYZW�Ƃ��Č��ɖ߂�
	normalMap = normalMap * 2.0 - 1.0;

	// ���ɖ߂����e�N�X�`��RGBA�f�[�^����ёւ��Ė@���p�ϐ���
	float4 normal;
	normal.x = -normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0;
	normal = normalize(normal); // ���K��

	//�����v�Z������
	float light = -dot(Light.Direction.xyz, normal.xyz);
	//float light = -dot(normal.xyz, Light.Direction.xyz);


	//�X�y�L�����̌v�Z
	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������
	//���̔��˃x�N�g�����v�Z
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //���K������

	float specular = -dot(eyev, refv); //���ʔ��˂̌v�Z
	specular = saturate(specular); //�l���T�`�����[�g
	specular = pow(specular, 30); //�����ł͂R�O�悵�Ă݂�

	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	outDiffuse.rgb *=
		In.Diffuse.rgb * light; //���邳�ƐF����Z
	outDiffuse.a *=
		In.Diffuse.a; //���ʌv�Z

	//�X�y�L�����l���f�t���[�Y�Ƃ��đ�������
	outDiffuse.rgb += specular;
}


