#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "SwordTrail.h"

// テクスチャ
ID3D11ShaderResourceView* SwordTrail::m_Texture;

// 頂点シェーダー
ID3D11VertexShader* SwordTrail::m_VertexShader;
// ピクセルシェーダー
ID3D11PixelShader* SwordTrail::m_PixelShader;
// 頂点レイアウト
ID3D11InputLayout* SwordTrail::m_VertexLayout;


void SwordTrail::Load()
{
	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/SwordTrail.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	// VSシェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	// PSシェーダー読み込み
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}

void SwordTrail::Unload()
{
	// テクスチャ解放
	m_Texture->Release();
	m_Texture = NULL;

	// VSシェーダー解放
	m_VertexShader->Release();
	m_VertexShader = NULL;
	
	// PSシェーダー解放
	m_PixelShader->Release();
	m_PixelShader = NULL;

	// VertexLayout解放
	m_VertexLayout->Release();
	m_VertexLayout = NULL;
}

void SwordTrail::Init()
{
	// 色の初期化
	m_Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	// 初期化
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 記録した座標の数初期化
	m_SaveCnt = 0;
	// 描画できるかどうか初期化
	m_CanDraw = false;
	// 存在時間初期化
	m_Duration = 0.0f;
}

void SwordTrail::Uninit()
{
	// Vertexバッファーの解放
	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
	}

	// 軌跡の座標を解放
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

	// 描画できる時だけ更新
	if (m_CanDraw)
	{
		// 時間更新
		m_Duration++;

		// 0.2秒以上存在すると消えます
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

	// 描画できる時だけ描画します
	if (!m_CanDraw) return;

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * trans;
	Renderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);


	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(8, 0);
}

void SwordTrail::InitTrail()
{
	VERTEX_3D vertex[8];

	// 座標設置やUV設置
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

	// 他の初期化
	for (int i = 0; i < 8; i++)
	{
		vertex[i].Diffuse = m_Color;
		vertex[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}


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

	assert(m_Texture);
}
