//thsozai ==>�O��܂ł̏�ԁ@ZIP�@�@�p�X���[�h�@nabe

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

	// ���̕������v�Z����
	float4 lightDir = In.WorldPosition - Light.Position;
	lightDir = normalize(lightDir);

	//�����v�Z������
	float light = -dot(normal.xyz, lightDir.xyz);

	// �X�|�b�g���C�g�̌����ƃs�N�Z���ւ̃��C�g�̕����Ƃœ��ς��v�Z����
	float range = dot(Light.Direction.xyz, lightDir.xyz);

	//�X�y�L�����̌v�Z
	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������
	//���̔��˃x�N�g�����v�Z
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //���K������

	float specular = -dot(eyev, refv); //���ʔ��˂̌v�Z
	specular = saturate(specular); //�l���T�`�����[�g
	specular = pow(specular, 20); //�����ł͂R�O�悵�Ă݂�

	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	// �X�|�b�g���C�g�͈̔͊O��������light���[���ɂ���
	//if (range < 0.9)
	//{
	//	light = 0.0;
	//	specular = 0.0;
	//}

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


