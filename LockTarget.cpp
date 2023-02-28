#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ComponentInclude.h"

#include "LockTarget.h"
#include "Camera.h"

void LockTarget::Init()
{
	// 初期化
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// サイズ指定
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	
	// スプライトコンポーネント追加
	SpriteComponent* _SC = AddComponent<SpriteComponent>(GameObject::FirstPri);
	_SC->LoadInfo("LockTarget", "Unlit", D3DXVECTOR2(1.0f, 1.0f));
	_SC->SetSpriteType(SpriteComponent::BilBoard);
	_SC->SetVisibility(false);
}

void LockTarget::Update()
{
	// シーン取得
	Scene* _Scene = Manager::GetScene();
	// SpriteComponentを取得
	SpriteComponent* _SC = GetComponent<SpriteComponent>();
	// カメラ取得
	Camera* _Cam = _Scene->GetGameObject<Camera>();

	// ロックしている目標が存在していると
	if (m_LockOnTarget != NULL)
	{
		// 見えるようにする
		_SC->SetVisibility(true);

		// カメラのBackward取得
		D3DXVECTOR3 CamBackward = _Cam->GetForward() * -1;

		// ロックしている目標の座標を取る
		D3DXVECTOR3 _LockPos = m_LockOnTarget->GetPosition();
		// アニメーションモデルの座標は足の部分だからYを調整します
		_LockPos.y = m_LockOnTarget->GetPosition().y + m_LockOnTarget->GetSize().y / 2;
		// 敵より前に出る
		_LockPos.x += CamBackward.x * 0.5f;
		_LockPos.z += CamBackward.z * 0.5f;

		// 座標を調整します
		m_Position = _LockPos;
	}
	else
	{
		// ロックしている相手がいない時は見えないようにする
		_SC->SetVisibility(false);
	}

	GameObject::Update();
}
