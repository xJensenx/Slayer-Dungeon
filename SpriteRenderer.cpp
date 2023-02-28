#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Fade.h"
#include "SpriteRenderer.h"

std::unordered_map<std::string, ID3D11ShaderResourceView*> SpriteRenderer::m_TextureMap;

ID3D11VertexShader* SpriteRenderer::m_LitVertexShader;
ID3D11PixelShader* SpriteRenderer::m_LitPixelShader;
ID3D11InputLayout* SpriteRenderer::m_LitVertexLayout;

ID3D11VertexShader* SpriteRenderer::m_UnlitVertexShader;
ID3D11PixelShader* SpriteRenderer::m_UnlitPixelShader;
ID3D11InputLayout* SpriteRenderer::m_UnlitVertexLayout;

ID3D11VertexShader* SpriteRenderer::m_NormalVertexShader;
ID3D11PixelShader*  SpriteRenderer::m_NormalPixelShader;
ID3D11InputLayout*  SpriteRenderer::m_NormalVertexLayout;

// ゲーム開始前にSpriteRendererのファイル読み込みをします
void SpriteRenderer::Load()
{
	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/explosion.png",
		NULL,
		NULL,
		&m_TextureMap["Explosion"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/field001.jpg",
		NULL,
		NULL,
		&m_TextureMap["Field"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Result.png",
		NULL,
		NULL,
		&m_TextureMap["ResultLogo"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/TitleLogo.png",
		NULL,
		NULL,
		&m_TextureMap["TitleLogo"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/tree.png",
		NULL,
		NULL,
		&m_TextureMap["Tree"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/field001.jpg",
		NULL,
		NULL,
		&m_TextureMap["Polygon2D"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Shadow2.png",
		NULL,
		NULL,
		&m_TextureMap["Shadow"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/SeaTexture.jpg",
		NULL,
		NULL,
		&m_TextureMap["SeaTexture"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/SeaNormal.bmp",
		NULL,
		NULL,
		&m_TextureMap["SeaNormal"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Title.png",
		NULL,
		NULL,
		&m_TextureMap["TitleWord"],
		NULL);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/UI_Continue.png",
		NULL,
		NULL,
		&m_TextureMap["Continue"],
		NULL);
	Renderer::CreateVertexShader(&m_UnlitVertexShader, &m_UnlitVertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_UnlitPixelShader, "unlitTexturePS.cso");

	Renderer::CreateVertexShader(&m_LitVertexShader, &m_LitVertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_LitPixelShader, "vertexLightingPS.cso");

	Renderer::CreateVertexShader(&m_NormalVertexShader, &m_NormalVertexLayout, "SeaShaderVS.cso");

	Renderer::CreatePixelShader(&m_NormalPixelShader, "SeaShaderPS.cso");
}

// ゲーム終了時に読み込んだファイルを解放します
void SpriteRenderer::Unload()
{
	m_LitVertexShader->Release();
	m_LitPixelShader->Release();
	m_LitVertexLayout->Release();

	m_UnlitVertexShader->Release();
	m_UnlitPixelShader->Release();
	m_UnlitVertexLayout->Release();

	m_NormalVertexShader->Release();
	m_NormalPixelShader->Release();
	m_NormalVertexLayout->Release();
	
	// for文で読み込んだテキスチャーを解放します
	for (auto p : m_TextureMap)
	{
		p.second->Release();
		delete p.second;
	}

	// unordered_mapを解放します
	m_TextureMap.clear();
}

// 情報をロードします
void SpriteRenderer::LoadInfo()
{
	m_Cnt = 0;

	VERTEX_3D vertex[4];

	switch (m_SpriteType)
	{
	case Double:
		vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_VertexSize.x, 0.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(m_TexCoord.x, 0.0f);

		vertex[2].Position = D3DXVECTOR3(0.0f, m_VertexSize.y, m_VertexSize.z);
		vertex[2].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[3].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);
		break;
	case Dynamic:
		vertex[0].Position = D3DXVECTOR3(-m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[0].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[1].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(m_TexCoord.x, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-m_VertexSize.x, -m_VertexSize.y, -m_VertexSize.z);
		vertex[2].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(m_VertexSize.x, -m_VertexSize.y, -m_VertexSize.z);
		vertex[3].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);
		break;
	case Bilboard:
		vertex[0].Position = D3DXVECTOR3(-m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[0].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[1].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(m_TexCoord.x, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-m_VertexSize.x, -m_VertexSize.y, -m_VertexSize.z);
		vertex[2].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(m_VertexSize.x, -m_VertexSize.y, -m_VertexSize.z);
		vertex[3].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);
		break;

	case Kinematic:
		vertex[0].Position = D3DXVECTOR3(-m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[0].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[1].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(m_TexCoord.x, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-m_VertexSize.x, -m_VertexSize.y, -m_VertexSize.z);
		vertex[2].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(m_VertexSize.x, -m_VertexSize.y, -m_VertexSize.z);
		vertex[3].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);
		break;

	case Shadow:
		vertex[0].Position = D3DXVECTOR3(-m_VertexSize.x, m_VertexSize.y, -m_VertexSize.z);
		vertex[0].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_VertexSize.x, m_VertexSize.y, -m_VertexSize.z);
		vertex[1].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(m_TexCoord.x, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[2].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, m_TexCoord.y);

		vertex[3].Position = D3DXVECTOR3(m_VertexSize.x, m_VertexSize.y, m_VertexSize.z);
		vertex[3].Normal = D3DXVECTOR3(m_Normal.x, m_Normal.y, m_Normal.z);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(m_TexCoord.x, m_TexCoord.y);
		break;
	}



	//// 頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;

	D3D11_BUFFER_DESC bd{};
	// 頂点バッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;


	//switch (m_SpriteType)
	//{
	//case Dynamic:

	//	break;
	//case Kinematic:
	//	// 頂点バッファ生成
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	bd.CPUAccessFlags = 0;

	//	sd.pSysMem = vertex;
	//	break;
	//}
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	assert(m_TextureMap[m_Map]);

	//switch (m_LightningType)
	//{
	//case SpriteRenderer::UnlitType:
	//	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
	//		"unlitTextureVS.cso");

	//	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
	//	break;
	//case SpriteRenderer::LitType:
	//	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
	//		"vertexLightingVS.cso");

	//	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//	break;
	//}
}
// 初期化
void SpriteRenderer::Init()
{
	m_VertexSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	m_Cnt = 0;

}

// 終了処理
void SpriteRenderer::Uninit()
{
	m_VertexBuffer->Release();
	//m_VertexLayout->Release();
	//m_VertexShader->Release();
	//m_PixelShader->Release();
}

// 更新処理
void SpriteRenderer::Update()
{
	
	if (m_SpriteAnimation != NoEffect)
	{
		m_Cnt++;

		if (m_Cnt >= 16)
		{
			m_GameObject->SetDestroy();
			return;
		}
	}
}

// 描画処理
void SpriteRenderer::Draw()
{
	if (m_SpriteAnimation == DynamicEffect)
	{
		// テキスチャー座標算出
		float x = m_Cnt % 4 * (1.0f / 4);
		float y = m_Cnt / 4 * (1.0f / 4);

		// 頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.25f + x, y);

		vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, 0.25f + y);

		vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(0.25f + x, 0.25f + y);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	switch (m_LightningType)
	{
	case SpriteRenderer::LitType:
		// 入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_LitVertexLayout);

		// シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_LitVertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_LitPixelShader, NULL, 0);
		break;
	case SpriteRenderer::UnlitType:
		// 入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_UnlitVertexLayout);

		// シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_UnlitVertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_UnlitPixelShader, NULL, 0);
		break;
	}

	D3DXVECTOR3 _GameObjectPos = m_GameObject->GetPosition();
	D3DXVECTOR3 _GameObjectSca = m_GameObject->GetScale();
	D3DXVECTOR3 _GameObjectRot = m_GameObject->GetRotation();

	if (m_SpriteType == Dynamic)
	{
		// カメラのビューマトリクス取得
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>();
		D3DXMATRIX view = camera->GetViewMatrix();

		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // 逆行列
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ワールドマトリクス設定
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if (m_SpriteType == Bilboard)
	{
		// カメラのビューマトリクス取得
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>();
		D3DXMATRIX view = camera->GetViewMatrix();

		// ビューの逆行列
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view); // 逆行列

		
		// Yが1.0f
		invView._21 = 0.0f;
		invView._22 = 1.0f;
		invView._23 = 0.0f;

		// 木とカメラの位置のベクトルを取って、Yを0にして
		// そのベクトルをNormalizeしたら代入します
		D3DXVECTOR3 VectorOfDist = camera->GetPosition() - m_GameObject->GetPosition();
		D3DXVECTOR3 XVectorOfDist = D3DXVECTOR3(VectorOfDist.x, 0.0f, VectorOfDist.z);
		D3DXVECTOR3 NormalizeDist;
		D3DXVec3Normalize(&NormalizeDist, &XVectorOfDist);
		invView._31 = camera->GetForward().x;
		invView._32 = camera->GetForward().y;
		invView._33 = camera->GetForward().z;

		// ベクトルYとベクトルZの外積を求めたら代入します
		D3DXVECTOR3 CrossDist;
		D3DXVECTOR3 VectorY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVECTOR3 VectorZ = camera->GetForward();

		D3DXVec3Cross(&CrossDist, &VectorY, &VectorZ);
		invView._11 = CrossDist.x;
		invView._12 = CrossDist.y;
		invView._13 = CrossDist.z;
		
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		// ワールドマトリクス設定
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);

	}
	else if(m_SpriteType == Kinematic || m_SpriteType == Shadow)
	{
		// ワールドマトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, _GameObjectSca.x, _GameObjectSca.y, _GameObjectSca.z);
		D3DXMatrixRotationYawPitchRoll(&rot, _GameObjectRot.y, _GameObjectRot.x, _GameObjectRot.z);
		D3DXMatrixTranslation(&trans, _GameObjectPos.x, _GameObjectPos.y, _GameObjectPos.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else if(m_SpriteType == Double)
	{
		Renderer::SetWorldViewProjection2D();
	}


	
	
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	if (m_SpriteType != Double)
	{
		// マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Renderer::SetMaterial(material);
	}

	

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureMap[m_Map]);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

}
