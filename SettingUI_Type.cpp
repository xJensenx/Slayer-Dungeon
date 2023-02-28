#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "SettingUI.h"
#include "SettingUI_Type.h"
#include "SettingAdjustButton.h"
#include "AudioManager.h"

void SettingUI_Type_BGM::Init()
{
	// スプライト設置
	SpriteComponent* _SC = m_SettingUI->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("UIBGM", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	// 調整ボタン追加
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	m_AdjustButton = _Scene->AddGameObject<SettingAdjustButton>(Scene::Layer_UILayer);
	m_AdjustButton->SetControlUI(m_SettingUI);
	m_AdjustButton->SetValue(AudioManager::GetVolumeBGM());
}

void SettingUI_Type_BGM::Update()
{
	SettingUI_Type::Update();

	// Audio調整（BGM）
	AudioManager::SetVolumeBGM(m_AdjustButton->GetValue());

}

void SettingUI_Type_SE::Init()
{
	// スプライト設置
	SpriteComponent* _SC = m_SettingUI->AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("UISE", "Unlit", D3DXVECTOR2(1.0f, 1.0f));

	// 調整ボタン追加
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	m_AdjustButton = _Scene->AddGameObject<SettingAdjustButton>(Scene::Layer_UILayer);
	m_AdjustButton->SetControlUI(m_SettingUI);
	m_AdjustButton->SetValue(AudioManager::GetVolumeSE());
}

void SettingUI_Type_SE::Update()
{
	SettingUI_Type::Update();
	// Audio調整（BGM）
	AudioManager::SetVolumeSE(m_AdjustButton->GetValue());
}

void SettingUI_Type::Update()
{
	// 座標取得
	D3DXVECTOR3 _Position = m_SettingUI->GetPosition();
	// ０の座標
	D3DXVECTOR3 InitPos = _Position;
	InitPos.x -= 200.0f;
	InitPos.y += 20.0f;
	// １の座標
	D3DXVECTOR3 TarPos = _Position;
	TarPos.x += 220.0f;
	TarPos.y += 20.0f;

	// 座標調整
	m_AdjustButton->SetBothPos(InitPos, TarPos);
}
