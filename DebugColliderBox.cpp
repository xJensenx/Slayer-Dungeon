#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "ComponentInclude.h"
#include "DebugColliderBox.h"

// デバッグ用当たり判定表示

void DebugColliderBox::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void DebugColliderBox::Uninit()
{
	m_VertexBuffer->Release();

	GameObject::Uninit();
}

void DebugColliderBox::Update()
{
	m_Duration--;
	if (m_Duration <= 0.0f)
	{
		SetDestroy();
	}

	GameObject::Update();
}

void DebugColliderBox::Draw()
{
	// ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(8, 0);

	GameObject::Draw();
}

void DebugColliderBox::LoadInfo()
{
	VERTEX_3D vertex[8];

	vertex[0].Position = D3DXVECTOR3(m_Position.x - (m_Size.x / 2), m_Position.y - (m_Size.y / 2), m_Position.z - (m_Size.z / 2));
	vertex[0].Normal = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertex[0].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y - (m_Size.y / 2), m_Position.z - (m_Size.z / 2));
	vertex[1].Normal = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertex[1].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Position.z - (m_Size.z / 2));
	vertex[2].Normal = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertex[2].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[3].Position = D3DXVECTOR3(m_Position.x - (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Position.z - (m_Size.z / 2));
	vertex[3].Normal = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vertex[3].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[4].Position = D3DXVECTOR3(m_Position.x - (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Position.z + (m_Size.z / 2));
	vertex[4].Normal = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vertex[4].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[4].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[5].Position = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Position.z + (m_Size.z / 2));
	vertex[5].Normal = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vertex[5].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[5].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[6].Position = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y - (m_Size.y / 2), m_Position.z + (m_Size.z / 2));
	vertex[6].Normal = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertex[6].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[6].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[7].Position = D3DXVECTOR3(m_Position.x - (m_Size.x / 2), m_Position.y - (m_Size.y / 2), m_Position.z + (m_Size.z / 2));
	vertex[7].Normal = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vertex[7].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[7].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	D3D11_BUFFER_DESC bd{};
	// 頂点バッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


}
