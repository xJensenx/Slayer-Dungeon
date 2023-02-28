//thsozai ==>�O��܂ł̏�ԁ@ZIP�@�@�p�X���[�h�@nabe


//BlinnPhongLightingPS.hlsl
//BlinnPhongLightingVS.hlsl


#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
//	//===================================================�t�H�b�O������������������������������������������������������
//	//�s�N�Z���̖@���𐳋K��
//	float4 normal = normalize(In.Normal);
//
//	// ���̕������v�Z����
//	float4 lightDir = In.WorldPosition - Light.Position;
//	lightDir = normalize(lightDir);
//
//	//�����v�Z������
//	float light = -dot(normal.xyz, lightDir.xyz);
//
//	// �X�|�b�g���C�g�̌����ƃs�N�Z���ւ̃��C�g�̕����Ƃœ��ς��v�Z����
//	float range = dot(Light.Direction.xyz, lightDir.xyz);
//
//	//�X�y�L�����̌v�Z
//	//�J��������s�N�Z���֌������x�N�g��
//	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
//	eyev = normalize(eyev); //���K������
//	//���̔��˃x�N�g�����v�Z
//	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
//	refv = normalize(refv); //���K������
//
//	float specular = -dot(eyev, refv); //���ʔ��˂̌v�Z
//	specular = saturate(specular); //�l���T�`�����[�g
//	specular = pow(specular, 20); //�����ł͂R�O�悵�Ă݂�
//
//	// �����ł̐F�����ʂ̃e�N�X�`�������_�F���쐬���Ă���
//	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
//	outDiffuse.rgb *= In.Diffuse.rgb * light;
//	outDiffuse.a *=
//		In.Diffuse.a; //���ʌv�Z
//
//	//�X�y�L�����l���f�t���[�Y�Ƃ��đ�������
//	outDiffuse.rgb += specular;
//
//	// �t�H�O
//
//	// �J��������s�N�Z���ւ̋������v�Z����
////	float len = length(v);	// �x�N�g���̑傫�����擾����
//	float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz);	// ��̃x�N�g���̋������擾����
//
//	// �t�H�O�̉e���x���v�Z����
//	float fogpow = saturate(dist / 30);	// �ő�[�x
//
//	// �o�͂���F��ω�������								�t�H�O�J���[
//	outDiffuse.rgb = outDiffuse.rgb * (1.0 - fogpow) + float3(0.0, 0.0, 0.0) * fogpow;

	// =============================================================================================�t�H�b�O������������������������������������������������������������������������������//

	// ���������������������������������������������������������������������������������������������e��������������������������������������������������������������������������������������������������//
	// �����ł̐F�����ʂ̃e�N�X�`�������_�F���쐬���Ă���
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse *= In.Diffuse;

	
	In.ShadowPosition.xyz /= In.ShadowPosition.w;				// ���e�ʂł̃s�N�Z���̍��W����
	In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;		// �e�N�X�`�����W�ɕϊ�
	In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;		// 

	// �V���h�E�}�b�v�e�N�X�`�����A���C�g�J��������s�N�Z���܂ł̋����i�[�x�l�j���擾
	float depth = g_TextureShadowDepth.Sample(g_SamplerState, In.ShadowPosition.xy);

	// �擾�l���ʏ�J��������s�N�Z���ւ̋�����菬����
	if (depth < In.ShadowPosition.z - 0.01)	// 0.01��Z�t�@�C�e�B���O�␳�l
	{
		outDiffuse.rgb *= 0.5;	// �F���Â�����
	}
}


