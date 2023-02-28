#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "AnimationModel.h"

#include "Scene.h"
#include "AnimModelManager.h"

std::unordered_map<std::string, class AnimationModel*>	AnimModelManager::m_AnimModel;
std::unordered_map<std::string, ID3D11ShaderResourceView*> AnimModelManager::m_LoadTexture;
std::unordered_map<std::string, D3DXVECTOR3>			AnimModelManager::m_ModelSize;

std::unordered_map<std::string, ID3D11VertexShader*>	AnimModelManager::m_VertexShader;
std::unordered_map<std::string, ID3D11PixelShader*>		AnimModelManager::m_PixelShader;
std::unordered_map<std::string, ID3D11InputLayout*>		AnimModelManager::m_VertexLayout;

void AnimModelManager::Load()
{
	// タイトル用プレイヤーアニメーション
	m_AnimModel["TitleCharacter"] = new AnimationModel();
	m_AnimModel["TitleCharacter"]->Load("asset\\AnimeModels\\Player\\Title\\TitleCharacter_Idle01.fbx");
	m_AnimModel["TitleCharacter"]->LoadAnimation("asset\\AnimeModels\\Player\\Title\\TitleCharacter_Idle01.fbx", "Idle01");
	m_AnimModel["TitleCharacter"]->LoadAnimation("asset\\AnimeModels\\Player\\Title\\TitleCharacter_Idle02.fbx", "Idle02");
	m_AnimModel["TitleCharacter"]->LoadAnimation("asset\\AnimeModels\\Player\\Title\\TitleCharacter_Idle03.fbx", "Idle03");
	m_AnimModel["TitleCharacter"]->LoadAnimation("asset\\AnimeModels\\Player\\Title\\TitleCharacter_Chosen.fbx", "Chosen");
	
	// Rendererのライティングのcsoファイルもゲーム開始前に読み込みます
	Renderer::CreateVertexShader(&m_VertexShader["Unlit"], &m_VertexLayout["Unlit"], "unlitTextureVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Lit"], &m_VertexLayout["Lit"], "vertexLightingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Shadow"], &m_VertexLayout["Shadow"], "DepthShadowMappingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["BlinnPhong"], &m_VertexLayout["BlinnPhong"], "BlinnPhongLightingVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["FogShader"], &m_VertexLayout["FogShader"], "fogShaderVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Toon"], &m_VertexLayout["Toon"], "toonVS.cso");
	Renderer::CreateVertexShader(&m_VertexShader["Player"], &m_VertexLayout["Player"], "PlayerVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader["Unlit"], "unlitTexturePS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Lit"], "vertexLightingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Shadow"], "DepthShadowMappingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["BlinnPhong"], "BlinnPhongLightingPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["FogShader"], "fogShaderPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Toon"], "toonPS.cso");
	Renderer::CreatePixelShader(&m_PixelShader["Player"], "PlayerPS.cso");
}

void AnimModelManager::LoadGameAsset()
{
	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Toon.bmp",
		NULL,
		NULL,
		&m_LoadTexture["Toon"],
		NULL);

	assert(m_LoadTexture["Toon"]);

	// SwordMasterキャラクターアニメーション
	m_AnimModel["SwordMaster"] = new AnimationModel();
	m_AnimModel["SwordMaster"]->Load("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Idle.fbx");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Idle.fbx", "Idle");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_RunForward.fbx", "Run");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Attack01.fbx", "Attack01");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Attack02.fbx", "Attack02");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Attack03.fbx", "Attack03");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Attack04.fbx", "Attack04");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Attack05.fbx", "Attack05");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Hit.fbx", "Hit");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Dead.fbx", "Dead");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Ult01.fbx", "Ult01");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Ult01_02.fbx", "Ult0102");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Block.fbx", "Block");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_BlockFinish.fbx", "BlockFinish");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_BlockCounter.fbx", "BlockCounter");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_QTEDodge01.fbx", "QTEDodge01");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_QTEDodge02.fbx", "QTEDodge02");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_QTEThrowSword.fbx", "QTEThrowSword");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_KnockedDown.fbx", "KnockedDown");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_GetUp.fbx", "GetUp");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Dodge.fbx", "Dodge");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill01.fbx", "Skill01");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill02.fbx", "Skill02");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill03.fbx", "Skill03");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill04.fbx", "Skill04");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill05.fbx", "Skill05");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill06.fbx", "Skill06");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill07.fbx", "Skill07");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill08.fbx", "Skill08");
	m_AnimModel["SwordMaster"]->LoadAnimation("asset\\AnimeModels\\Player\\SwordMaster\\SwordMaster_Skill09.fbx", "Skill09");

	m_ModelSize["SwordMaster"] = m_AnimModel["SwordMaster"]->GetModelSize();

	// ボスのアニメーション
	m_AnimModel["Boss"] = new AnimationModel();
	m_AnimModel["Boss"]->Load("asset\\AnimeModels\\Boss\\Boss_Idle.fbx");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Idle.fbx", "Idle");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Walk.fbx", "Walk");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Run.fbx", "Run");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Roar.fbx", "Roar");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Punch.fbx", "LightPunch");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Swiping.fbx", "HeavyPunch");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_JumpAtk.fbx", "JumpAttack");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_JumpAtkSecond.fbx", "JumpAtkSecond");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Jumping.fbx", "Jump");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Dead.fbx", "Dead");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_Injured.fbx", "Injured");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_RageAttack01.fbx", "RageAtk01");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_ShootFireBall01.fbx", "ShootFireBall01");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_RageSummonMeteor.fbx", "RageSummonMeteor");
	m_AnimModel["Boss"]->LoadAnimation("asset\\AnimeModels\\Boss\\Boss_SummonRotatingFireBall.fbx", "SummonRotatingFireBall");
	m_ModelSize["Boss"] = m_AnimModel["Boss"]->GetModelSize();

	// Minion（雑魚敵）のアニメーション
	m_AnimModel["Minion"] = new AnimationModel();
	m_AnimModel["Minion"]->Load("asset\\AnimeModels\\Minion\\Minion_Idle.fbx");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Idle.fbx", "Idle");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Run.fbx", "Run");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Attack01.fbx", "Attack01");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Attack02.fbx", "Attack02");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Hit.fbx", "Hit");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Show.fbx", "Show");
	m_AnimModel["Minion"]->LoadAnimation("asset\\AnimeModels\\Minion\\Minion_Dead.fbx", "Dead");
	m_ModelSize["Minion"] = m_AnimModel["Minion"]->GetModelSize();
}

void AnimModelManager::Unload()
{
	// unordered_mapのAnimModelを解放する
	for (auto P : m_AnimModel)
	{
		P.second->Unload();
		delete P.second;
		P.second = NULL;
	}

	m_AnimModel.clear();

	// シェーダーなどの解放
	for (auto VS : m_VertexShader)
	{
		VS.second->Release();
		delete VS.second;
		VS.second = NULL;
	}
	m_VertexShader.clear();
	for (auto VL : m_VertexLayout)
	{
		VL.second->Release();
		delete VL.second;
		VL.second = NULL;
	}
	m_VertexLayout.clear();
	for (auto PS : m_PixelShader)
	{
		PS.second->Release();
		delete PS.second;
		PS.second = NULL;
	}
	m_PixelShader.clear();
}

void AnimModelManager::UnloadGameAsset()
{
	m_AnimModel["SwordMaster"]->Unload();
	delete m_AnimModel["SwordMaster"];
	m_AnimModel["SwordMaster"] = NULL;
	m_AnimModel.erase("SwordMaster");

	m_AnimModel["Boss"]->Unload();
	delete m_AnimModel["Boss"];
	m_AnimModel["Boss"] = NULL;
	m_AnimModel.erase("Boss");

	m_AnimModel["Minion"]->Unload();
	delete m_AnimModel["Minion"];
	m_AnimModel["Minion"] = NULL;
	m_AnimModel.erase("Minion");

	m_LoadTexture["Toon"]->Release();
	m_LoadTexture["Toon"] = NULL;
	m_LoadTexture.erase("Toon");
}

void AnimModelManager::Init()
{
	m_UseNormal = false;
}

void AnimModelManager::Uninit()
{
}

void AnimModelManager::Update()
{
}

void AnimModelManager::Draw()
{
	// ポジションを取る
	D3DXVECTOR3 _Position = m_GameObject->GetPosition();
	// スケールを取る
	D3DXVECTOR3 _Scale = m_GameObject->GetScale();
	// オイラー回転角度を取る
	D3DXVECTOR3 _Rotation = m_GameObject->GetRotation();

	m_AnimModel[m_Name]->Update(m_AnimationName1, m_AnimationName2, m_BlendRate, (int)m_Frame1, (int)m_Frame2);

	// ライティングの種類によってライティングの有無処理
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout[m_ShaderName]);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader[m_ShaderName], NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader[m_ShaderName], NULL, 0);

	// ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, _Scale.x, _Scale.y, _Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, _Rotation.y, _Rotation.x, _Rotation.z);
	//D3DXMatrixRotationQuaternion(&rot, &_Quaternion);
	D3DXMatrixTranslation(&trans, _Position.x, _Position.y, _Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	if (m_UseNormal)
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_LoadTexture[m_NormalTextureName]);
	}

	//// シャドウバッファテクスチャを１番へセット
	//ID3D11ShaderResourceView* shadowDepthTexture =
	//	Renderer::GetShadowDepthTexture();
	//Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &shadowDepthTexture);

	if (m_ShaderName == "Player")	Renderer::SetPlayerColor(m_PlayerColor);

	m_AnimModel[m_Name]->Draw();
}

float AnimModelManager::GetAnimDuration(const char* AnimationName)
{
	return m_AnimModel[m_Name]->GetDuration(AnimationName);
}
