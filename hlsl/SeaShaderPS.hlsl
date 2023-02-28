#include "common.hlsl"

// �@���}�b�v�p�̃e�N�X�`���ϐ���ǉ�
Texture2D g_Texture : register(t0); // �ʏ�̃e�N�X�`���p
Texture2D g_TextureNormal : register(t1); // �@���}�b�v�p
Texture2D g_SecondNormal: register(t3);

// �T���v���[�X�e�[�g�̂O�ԃX���b�g���g��
SamplerState g_SamplerState : register(s0); // ����͂P��ok
// �T���v���[�X�e�[�g�̂P�ԃX���b�g���g���ꍇ
// SamplerState g_SamplerState1 : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float2 uv = In.TexCoord;
	uv.x += Parameter.x;
	uv.y += Parameter.x;

	float2 SecUV = In.TexCoord;
	SecUV.x -= Parameter.x;
	SecUV.y -= Parameter.y;

	// ���̃s�N�Z���̖@���}�b�v�̃f�[�^RGBA�l���擾
	float4 normalMap =
		g_TextureNormal.Sample(g_SamplerState, uv);
	float4 SecNormal =
		g_SecondNormal.Sample(g_SamplerState, SecUV);

	// �擾�����X�P�[�����O��RGBA�l���x�N�g�����XYZW�Ƃ��Č��ɖ߂�
	normalMap = normalMap * 2.0 - 1.0;
	SecNormal = SecNormal * 2.0 - 1.0;

	normalMap *= SecNormal;

	// ���ɖ߂����e�N�X�`��RGBA�f�[�^����ёւ��Ė@���p�ϐ���
	float4 normal;
	normal.x = -normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0;
	normal = normalize(normal); // ���K��

	float4 Second;
	Second.x = -SecNormal.r;
	Second.y = SecNormal.b;
	Second.z = SecNormal.g;
	Second.w = 0.0;
	Second = normalize(Second);

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


	// �t�H�O

	// �J��������s�N�Z���ւ̋������v�Z����
//	float len = length(v);	// �x�N�g���̑傫�����擾����
	float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz);	// ��̃x�N�g���̋������擾����

	// �t�H�O�̉e���x���v�Z����
	float fogpow = saturate(dist / 100);	// �ő�[�x

	// �o�͂���F��ω�������								�t�H�O�J���[
	outDiffuse.rgb = outDiffuse.rgb * (1.0 - fogpow) + float3(1.0, 1.0, 1.0) * fogpow;
}