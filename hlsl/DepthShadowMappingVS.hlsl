//���_�V�F�[�_�[
#include "common.hlsl" //�K���C���N���[�h
//
//in �͓��͂���Ă���f�[�^�[
//out �͏o�͂���f�[�^
//
void main(in VS_IN In, out PS_IN Out)
{
	//�P���_���̃f�[�^���󂯎��A�������āA�o�͂���
	//���_�ϊ����� ���̏����͕K���K�v
	matrix wvp; //�s��ϐ����쐬
	wvp = mul(World, View); //wvp = ���[���h�s�񁖃J�����s��
	wvp = mul(wvp, Projection); //wvp = wvp *�v���W�F�N�V�����s��
	float4 worldNormal, normal;		// �@���̃��[���h�ϊ�
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	// ��������
	float light = -dot(Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);
	Out.Diffuse = light;
	Out.Diffuse.a = In.Diffuse.a;

	Out.Position = mul(In.Position, wvp);	// ���_���W�����[���h�ϊ����ďo��
	Out.Normal = worldNormal;				// �@�����o��
	Out.TexCoord = In.TexCoord;				// �e�N�X�`�����W���o��

	matrix lightwvp;
	lightwvp = mul(World, Light.View);	// ���[���h�s�� * ���C�g�r���[�s��
	lightwvp = mul(lightwvp, Light.Projection);	// ����� * ���C�g�v���W�F�N�V�����s��

	Out.ShadowPosition = mul(In.Position, lightwvp);	// ���C�g�J��������݂����_���W�o��
		//���[���h�ϊ��������_���W���o��
	//Out.WorldPosition = mul(In.Position, World);
}
