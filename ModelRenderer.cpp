#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "Scene.h"
#include "ModelRenderer.h"
#include "Camera.h"

// unordered_mapを使ってモデルとモデルのサイズの情報を記録します
std::unordered_map<std::string, Model*> ModelRenderer::m_Model;
std::unordered_map<std::string, D3DXVECTOR3> ModelRenderer::m_ModelSize;

std::unordered_map<std::string, ID3D11VertexShader*>		ModelRenderer::m_VertexShader;
std::unordered_map<std::string, ID3D11PixelShader*>			ModelRenderer::m_PixelShader;
std::unordered_map<std::string, ID3D11InputLayout*>			ModelRenderer::m_VertexLayout;
std::unordered_map<std::string, ID3D11ShaderResourceView*>	ModelRenderer::m_LoadTexture;


// Modelのファイル読み込みを事前にロードするための関数
void ModelRenderer::Load()
{
	// モデル読み込み
	m_Model["Sky"] = new Model();
	m_Model["Sky"]->Load("asset\\models\\MorningSky.obj");
	m_ModelSize["Sky"] = m_Model["Sky"]->GetModelSize();

	m_Model["Island"] = new Model();
	m_Model["Island"]->Load("asset\\models\\ForTitle\\TestIsland\\TestIsland.obj");

	m_Model["Particle"] = new Model();
	m_Model["Particle"]->Load("asset\\models\\Particle\\Particle.obj");
	m_ModelSize["Particle"] = m_Model["Particle"]->GetModelSize();

	m_Model["Particle02"] = new Model();
	m_Model["Particle02"]->Load("asset\\models\\Particle\\Particle2.obj");
	m_ModelSize["Particle02"] = m_Model["Particle02"]->GetModelSize();

	m_Model["Meteor"] = new Model();
	m_Model["Meteor"]->Load("asset\\models\\Boss\\Attack\\Meteor.obj");
	m_ModelSize["Meteor"] = m_Model["Meteor"]->GetModelSize();

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Toon.bmp",
		NULL,
		NULL,
		&m_LoadTexture["Toon"],
		NULL);

	assert(m_LoadTexture["Toon"]);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/earthenvmap.png",
		NULL,
		NULL,
		&m_LoadTexture["Env"],
		NULL);

	assert(m_LoadTexture["Env"]);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Title/GrassGroundNormalTexture.png",
		NULL,
		NULL,
		&m_LoadTexture["TitleGrass"],
		NULL);

	assert(m_LoadTexture["TitleGrass"]);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/models/FireBall/FireBallNormal.png",
		NULL,
		NULL,
		&m_LoadTexture["FireBallNormal"],
		NULL);

	assert(m_LoadTexture["FireBallNormal"]);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/StoneGroundNormalTexture.png",
		NULL,
		NULL,
		&m_LoadTexture["StoneGroundNormal"],
		NULL);

	assert(m_LoadTexture["StoneGroundNormal"]);

	// Rendererのライティングのcsoファイルもゲーム開始前に読み込みます
	Renderer::CreateVertexShader(&m_VertexShader["Unlit"],	&m_VertexLayout["Unlit"], "unlitTextureVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Lit"],	&m_VertexLayout["Lit"], "vertexLightingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["FogShader"], &m_VertexLayout["FogShader"], "fogShaderVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Shadow"], &m_VertexLayout["Shadow"], "DepthShadowMappingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Toon"], &m_VertexLayout["Toon"], "toonVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Env"], &m_VertexLayout["Env"], "envMappingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["ParEnv"], &m_VertexLayout["ParEnv"], "ParticleEnvVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Rim"], &m_VertexLayout["Rim"], "RimLightingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["TitleGround"], &m_VertexLayout["TitleGround"], "TitleGroundVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["FireBall"], &m_VertexLayout["FireBall"], "FireBallVS.cso");


	Renderer::CreatePixelShader(&m_PixelShader["Unlit"], "unlitTexturePS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Lit"], "vertexLightingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["FogShader"], "fogShaderPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Shadow"], "DepthShadowMappingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Toon"], "toonPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Env"], "envMappingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["ParEnv"], "ParticleEnvPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Rim"], "RimLightingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["TitleGround"], "TitleGroundPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["FireBall"], "FireBallPS.cso");
}

// ゲーム終了時にモデルを解放します
void ModelRenderer::Unload()
{
	// for文で入っている全部モデルクラスの解放処理をします
	for (auto P : m_Model)
	{
		P.second->Unload();
		delete P.second;
	}

	// モデルのunordered_mapを解放します
	m_Model.clear();

	// モデルサイズのunordered_mapを解放します
	m_ModelSize.clear();

	for (auto VS : m_VertexShader)
	{
		VS.second->Release();
		delete VS.second;
	}
	m_VertexShader.clear();

	for (auto VL : m_VertexLayout)
	{
		VL.second->Release();
		delete VL.second;
	}
	m_VertexLayout.clear();

	for (auto PS : m_PixelShader)
	{
		PS.second->Release();
		delete PS.second;
	}
	m_PixelShader.clear();

	for (auto LT : m_LoadTexture)
	{
		LT.second->Release();
		delete LT.second;
	}
	m_LoadTexture.clear();


	
}

void ModelRenderer::LoadGameAsset()
{
	m_Model["Tree"] = new Model();
	m_Model["Tree"]->Load("asset\\models\\Tree_E.obj");
	m_ModelSize["Tree"] = m_Model["Tree"]->GetModelSize();

	m_Model["TestOBB"] = new Model();
	m_Model["TestOBB"]->Load("asset\\models\\TestOBB.obj");
	m_ModelSize["TestOBB"] = m_Model["TestOBB"]->GetModelSize();

	m_Model["ColliderBox"] = new Model();
	m_Model["ColliderBox"]->Load("asset\\models\\ColliderBox.obj");
	m_ModelSize["ColliderBox"] = m_Model["ColliderBox"]->GetModelSize();
	// 
	m_Model["ColliderBox"]->SetWireFrame(true);

	m_Model["Sword"] = new Model();
	m_Model["Sword"]->Load("asset\\models\\Sword\\Sword.obj");
	m_ModelSize["Sword"] = m_Model["Sword"]->GetModelSize();

	m_Model["Rock"] = new Model();
	m_Model["Rock"]->Load("asset\\models\\TestEffect\\TestGroundEffect.obj");
	m_ModelSize["Rock"] = m_Model["Rock"]->GetModelSize();

	m_Model["LimitWall"] = new Model();
	m_Model["LimitWall"]->Load("asset\\models\\LimitWall\\LimitWall.obj");
	m_ModelSize["LimitWall"] = m_Model["LimitWall"]->GetModelSize();

	m_Model["FireBall"] = new Model();
	m_Model["FireBall"]->Load("asset\\models\\FireBall\\FireBall.obj");
	m_ModelSize["FireBall"] = m_Model["FireBall"]->GetModelSize();

	m_Model["Castle"] = new Model();
	m_Model["Castle"]->Load("asset\\models\\Castle\\Tower.obj");
	m_ModelSize["Castle"] = m_Model["Castle"]->GetModelSize();
}

void ModelRenderer::UnloadGameAsset()
{
	m_Model["Tree"]->Unload();
	delete m_Model["Tree"];
	m_Model["Tree"] = NULL;
	m_Model.erase("Tree");

	m_Model["TestOBB"]->Unload();
	delete m_Model["TestOBB"];
	m_Model["TestOBB"] = NULL;
	m_Model.erase("TestOBB");

	m_Model["ColliderBox"]->Unload();
	delete m_Model["ColliderBox"];
	m_Model["ColliderBox"] = NULL;
	m_Model.erase("ColliderBox");

	m_Model["Sword"]->Unload();
	delete m_Model["Sword"];
	m_Model["Sword"] = NULL;
	m_Model.erase("Sword");

	m_Model["Rock"]->Unload();
	delete m_Model["Rock"];
	m_Model["Rock"] = NULL;
	m_Model.erase("Rock");

	m_Model["FireBall"]->Unload();
	delete m_Model["FireBall"];
	m_Model["FireBall"] = NULL;
	m_Model.erase("FireBall");

	m_Model["Castle"]->Unload();
	delete m_Model["Castle"];
	m_Model["Castle"] = NULL;
	m_Model.erase("Castle");

}

void ModelRenderer::Init()
{
	m_UseQuaternion = false;
	// 初期化
	m_Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Visibility = true;
	m_ChangeMaterial = false;
	m_UseNormal = false;
	m_Parameter = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
}

void ModelRenderer::Uninit()
{
	m_VertexPosition.clear();
}

void ModelRenderer::Update()
{
}

// 描画処理
void ModelRenderer::Draw()
{
	if (!m_Visibility) return;

	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	// ポジションを取る
	D3DXVECTOR3 _Position = m_GameObject->GetPosition();

	D3DXVECTOR3 _Size = m_GameObject->GetSize();
	//if (camera != NULL)
	//{
	//	if (!camera->CheckView(_Position,_Size.x ))
	//	{
	//		return;
	//	}
	//}

	// スケールを取る
	D3DXVECTOR3 _Scale = m_GameObject->GetScale();
	// オイラー回転角度を取る
	D3DXVECTOR3 _Rotation = m_GameObject->GetRotation();
	D3DXQUATERNION _Quaternion = m_GameObject->GetQuaternion();


	// ライティングの種類によってライティングの有無処理
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout[m_ShaderName]);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader[m_ShaderName], NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader[m_ShaderName], NULL, 0);

	// ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, _Scale.x, _Scale.y, _Scale.z);
	if (m_UseQuaternion)
	{
		D3DXMatrixRotationQuaternion(&rot, &_Quaternion);
	}
	else
	{
		D3DXMatrixRotationYawPitchRoll(&rot, _Rotation.y, _Rotation.x, _Rotation.z);
	}
	//D3DXMatrixRotationQuaternion(&rot, &_Quaternion);
	D3DXMatrixTranslation(&trans, _Position.x, _Position.y, _Position.z);
	world = scale * rot * trans ;

	Renderer::SetWorldMatrix(&world);

	// マテリアル設定
	if (m_ChangeMaterial)
	{
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = m_Diffuse;
		material.Emission = m_Emission;
		material.Ambient = m_Ambient;
		Renderer::SetMaterial(material);
	}
	
	if (m_UseNormal)
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_LoadTexture[m_NormalTextureName]);

		Renderer::SetParameter(m_Parameter);
	}
	
	m_Model[m_Name]->Draw(m_ChangeMaterial);
}

// モデルの名前とライティングの種類をセットする関数
void ModelRenderer::SetModel(std::string _Name, LightningType _Type)
{
	m_Name = _Name;
	m_LightningType = _Type;

	switch (m_LightningType)
	{
	case UnlitType:
		m_ShaderName = "Unlit";
		break;
	case LitType:
		m_ShaderName = "Lit";
		break;
	case FogType:
		m_ShaderName = "FogShader";
		break;
	case ShadowType:
		m_ShaderName = "Shadow";
		break;
	case ToonType:
		m_ShaderName = "Toon";
		break;
	case EnvType:
		m_ShaderName = "Env";
		break;
	case ParticleEnvType:
		m_ShaderName = "ParEnv";
		break;
	case RimType:
		m_ShaderName = "Rim";
		break;
	case TitleGroundType:
		m_ShaderName = "TitleGround";
		break;
	case FireBallType:
		m_ShaderName = "FireBall";
		break;
	}

	m_VertexPosition = m_Model[m_Name]->GetAllVertexPosition();
}