#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�s�N�Z���̖@���𐳋K��
	float4 normal = normalize(In.Normal);
	//�����v�Z������
	float light = -dot(normal.xyz, Light.Direction.xyz);

	//�X�y�L�����̌v�Z
	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������

	////���̔��˃x�N�g�����v�Z
	//float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	//refv = normalize(refv); //���K������

	//�n�[�t�x�N�g���쐬
	float3	halfv = eyev + Light.Direction.xyz;
	halfv = normalize(halfv); //���K������


	//���ʔ��˂̌v�Z
	float specular = -dot(halfv, normal.xyz);
	specular = saturate(specular); //�l���T�`�����[�g
	specular = pow(specular, 30); //�����ł͂R�O�悵�Ă݂�

	//�������C�e�B���O
	float rim = 1.0 + dot(eyev, normal.xyz); //�����Ɩ@���̓��ς𖾂邳�ɕϊ�����
	rim = pow(rim, 3) * 2.0f; //�X�y�L�����Ɠ����悤�ȏ�����K���ɍs���B
	rim = saturate(rim); //rim���T�`�����[�g����


	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse = 
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	outDiffuse.rgb *=
		In.Diffuse.rgb * light; //���邳�ƐF����Z
	outDiffuse.a *= 
		In.Diffuse.a; //���ʌv�Z

	//�X�y�L�����l���f�t���[�Y�Ƃ��đ�������
	outDiffuse.rgb += specular;
	//�����l���f�t���[�Y�Ƃ��đ�������
	outDiffuse.r += rim;
	outDiffuse.b += rim;
	
}

