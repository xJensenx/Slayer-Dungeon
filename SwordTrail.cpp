#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "SwordTrail.h"

// �e�N�X�`��
ID3D11ShaderResourceView* SwordTrail::m_Texture;

// ���_�V�F�[�_�[
ID3D11VertexShader* SwordTrail::m_VertexShader;
// �s�N�Z���V�F�[�_�[
ID3D11PixelShader* SwordTrail::m_PixelShader;
// ���_���C�A�E�g
ID3D11InputLayout* SwordTrail::m_VertexLayout;


void SwordTrail::Load()
{
	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/SwordTrail.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	// VS�V�F�[�_�[�ǂݍ���
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	// PS�V�F�[�_�[�ǂݍ���
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}

void SwordTrail::Unload()
{
	// �e�N�X�`�����
	m_Texture->Release();
	m_Texture = NULL;

	// VS�V�F�[�_�[���
	m_VertexShader->Release();
	m_VertexShader = NULL;
	
	// PS�V�F�[�_�[���
	m_PixelShader->Release();
	m_PixelShader = NULL;

	// VertexLayout���
	m_VertexLayout->Release();
	m_VertexLayout = NULL;
}

void SwordTrail::Init()
{
	// �F�̏�����
	m_Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	// ������
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �L�^�������W�̐�������
	m_SaveCnt = 0;
	// �`��ł��邩�ǂ���������
	m_CanDraw = false;
	// ���ݎ��ԏ�����
	m_Duration = 0.0f;
}

void SwordTrail::Uninit()
{
	// Vertex�o�b�t�@�[�̉��
	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
	}

	// �O�Ղ̍��W�����
	for (int i = 0; i < 2; i++)
	{
		if (m_TrailPos[i] != NULL)
		{
			delete m_TrailPos[i];
			m_TrailPos[i] = NULL;
		}
	}
	
	GameObject::Uninit();
}

void SwordTrail::Update()
{
	if (m_Pause && !m_IgnorePause) return;

	// �`��ł��鎞�����X�V
	if (m_CanDraw)
	{
		// ���ԍX�V
		m_Duration++;

		// 0.2�b�ȏ㑶�݂���Ə����܂�
		if (m_Duration > 0.2f * Manager::Time)
		{
			SetDestroy();
			return;
		}
	}

	GameObject::Update();
}

void SwordTrail::Draw()
{
	GameObject::Draw();

	// �`��ł��鎞�����`�悵�܂�
	if (!m_CanDraw) return;

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * trans;
	Renderer::SetWorldMatrix(&world);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);


	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(8, 0);
}

void SwordTrail::InitTrail()
{
	VERTEX_3D vertex[8];

	// ���W�ݒu��UV�ݒu
	for (int i = 0; i < 2; i++)
	{
		vertex[i * 2].Position = m_TrailPos[i]->m_HeadPos;
		vertex[i * 2 + 1].Position = m_TrailPos[i]->m_TailPos;
		vertex[i * 2].TexCoord = D3DXVECTOR2(i * 0.5f, 0.0f);
		vertex[i * 2 + 1].TexCoord = D3DXVECTOR2(i * 0.5f, 1.0f);
	}
	vertex[4].Position = m_TrailPos[1]->m_HeadPos;
	vertex[4].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[5].Position = m_TrailPos[1]->m_TailPos;
	vertex[5].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[6].Position = m_TrailPos[0]->m_HeadPos;
	vertex[6].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	vertex[7].Position = m_TrailPos[0]->m_TailPos;
	vertex[7].TexCoord = D3DXVECTOR2(0.5f, 1.0f);

	// ���̏�����
	for (int i = 0; i < 8; i++)
	{
		vertex[i].Diffuse = m_Color;
		vertex[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}


	D3D11_BUFFER_DESC bd{};
	// ���_�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	assert(m_Texture);
}
