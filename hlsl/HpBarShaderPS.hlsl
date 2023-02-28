#include "common.hlsl"

// �@���}�b�v�p�̃e�N�X�`���ϐ���ǉ�
Texture2D g_Texture : register(t0); // �ʏ�̃e�N�X�`���p
Texture2D g_TextureNormal : register(t1); // �@���}�b�v�p

// �T���v���[�X�e�[�g�̂O�ԃX���b�g���g��
SamplerState g_SamplerState : register(s0); // ����͂P��ok
// �T���v���[�X�e�[�g�̂P�ԃX���b�g���g���ꍇ
// SamplerState g_SamplerState1 : register(s1);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float2 uv = In.TexCoord;
	uv.x += Parameter.x;
	uv.y += Parameter.x;

	// ���̃s�N�Z���̖@���}�b�v�̃f�[�^RGBA�l���擾
	float4 normalMap =
		g_TextureNormal.Sample(g_SamplerState, uv);

	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse =
		g_Texture.Sample(g_SamplerState, In.TexCoord);

	outDiffuse.rgb *=
		mul(In.Diffuse.rgb, normalMap); //���邳�ƐF����Z
	outDiffuse.a *=
		In.Diffuse.a; //���ʌv�Z
}