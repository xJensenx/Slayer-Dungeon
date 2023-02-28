//���_�V�F�[�_�[
#include "common.hlsl" //�K���C���N���[�h
//
//in �͓��͂���Ă���f�[�^�[
//out �͏o�͂���f�[�^
//
void main(in VS_IN In, out PS_IN Out)
{
	// wvp���[���h�r���[�v���W�F�N�V�����s��쐬
	matrix wvp;
	wvp = mul(World, View); //wvp = ���[���h�s�񁖃r���[�s��
	wvp = mul(wvp, Projection);

	// �@�������[���h�s��ŕϊ�
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);//�@���x�N�g����w��0�Ƃ��ăR�s�[�i���s�ړ����Ȃ�����)
	worldNormal = mul(normal, World); // �@��*���[���h�s��
	worldNormal = normalize(worldNormal); // ���K������

	// ���_���W��wvp�ŕϊ����ďo��
	Out.Position = mul(In.Position, wvp);
	// ���_���W�����[���h�s��ŕϊ����ďo��
	Out.WorldPosition = mul(In.Position, World);
	// ���[���h�ϊ������@�����o��
	Out.Normal = worldNormal;
	// �f�t���[�Y���o��
	Out.Diffuse = In.Diffuse;
	// �e�N�X�`�����W���o��
	Out.TexCoord = In.TexCoord;
}
