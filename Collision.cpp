#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "RigidBody.h"
#include "Collision.h"

// 初期化
void Collision::Init()
{
	m_OffSet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isTrigger = false;
	isCollision = false;
}

// 終了処理
void Collision::Uninit()
{
	m_CollideObjects = NULL;
}

// 更新処理
void Collision::Update()
{
	// 各シーンの情報を手に入れる
	Scene* _Scene = Manager::GetScene();
	// 親ゲームオブジェクトのRigidBodyの情報を手に入れる
	RigidBody* _Rigid = m_GameObject->GetComponent<RigidBody>();

	// IsTriggerをオンにしたら、押し出し処理行わない（当たり判定まだ実行しています）
	if (isTrigger)
	{
		return;
	}

	// シーンの中にCollisionのコンポネント付いてるゲームオブジェクトの情報を手に入れる
	std::vector<GameObject*> _GameObject = _Scene->GetGameObjectsWithComponent<Collision>();

	// 床地面の高さ（実験中）
	float GroundHeight = 0.5f;

	for (GameObject* gameobject : _GameObject)
	{
		// 自分のゲームオブジェクトと同じだったら次のループに進む
		if (gameobject == m_GameObject || gameobject->GetComponent<Collision>()->isTrigger)
		{
			continue;
		}

		// ゲームオブジェクトのポジションを取る
		D3DXVECTOR3 Pos = gameobject->GetPosition();
		// ゲームオブジェクトのサイズを取る
		D3DXVECTOR3 Size = gameobject->GetSize();
		// ゲームオブジェクトのスケールを取る
		D3DXVECTOR3 Scale = gameobject->GetScale();
		// 自分のゲームオブジェクトのポジションを取る
		D3DXVECTOR3 SelfPos = m_GameObject->GetPosition();
		// 自分のゲームオブジェクトのサイズを取る
		D3DXVECTOR3 SelfSize = m_GameObject->GetSize();
		// 自分のゲームオブジェクトの前のフレームのポジションを取る
		D3DXVECTOR3 SelfPrevPos = m_GameObject->GetPrevPos();
		// 自分のゲームオブジェクトのスケールを取る
		D3DXVECTOR3 SelfScale = m_GameObject->GetScale();

		// 自分と相手のベクトルを取る
		D3DXVECTOR3 Dir = SelfPos - Pos;
		// Ｙ軸を０にする（ＸとＺの距離を計算するため）
		Dir.y = 0.0f;
		// 距離を計算する
		float Length = D3DXVec3Length(&Dir);

		// 
		if (Length < Scale.x)
		{
			if (_Rigid != NULL)
			{
				if (_Rigid->GetRigidType() == RigidBody::Dynamic)
				{
					if (SelfPos.y < Pos.y + (Scale.y * Size.y) - (Size.y / 2) + m_OffSet.y)
					{
						m_GameObject->SetInformation(
							D3DXVECTOR3(m_GameObject->GetPrevPos().x,
								m_GameObject->GetPosition().y,
								m_GameObject->GetPrevPos().z));
					}
					else
					{
						GroundHeight = Pos.y + (Scale.y * Size.y) - (Size.y / 2) + m_OffSet.y;
					}
				}
			}
		}
	}

	// デバッグ用当たり判定
	if (_Rigid != NULL)
	{
		if (m_GameObject->GetPosition().y < GroundHeight + (m_GameObject->GetSize().y / 2) + m_OffSet.y && _Rigid->GetVelocity().y < 0.0f)
		{
			m_GameObject->SetInformation(D3DXVECTOR3(m_GameObject->GetPosition().x,
				GroundHeight + (m_GameObject->GetSize().y / 2) + m_OffSet.y, m_GameObject->GetPosition().z));

			_Rigid->SetVelocity(D3DXVECTOR3(_Rigid->GetVelocity().x, 0.0f, _Rigid->GetVelocity().z));
		}
	}
}

// 立方体の当たり判定
bool Collision::CollisionBlock
(	D3DXVECTOR3 _SelfPos,		// 自分のポジション 
	D3DXVECTOR3 _SelfSize,		// 自分のサイズ
	D3DXVECTOR3 _SelfScale,		// 自分のスケール
	D3DXVECTOR3 _ColPos, 		// 相手のポジション
	D3DXVECTOR3 _ColSize,		// 相手のサイズ
	D3DXVECTOR3 _ColScale)		// 相手のスケール
{
	float AxMax = _SelfPos.x + _SelfSize.x / 2;
	float AxMin = _SelfPos.x - _SelfSize.x / 2;
	float AyMax = _SelfPos.y + _SelfSize.y / 2;
	float AyMin = _SelfPos.y - _SelfSize.y / 2;
	float AzMax = _SelfPos.z + _SelfSize.z / 2;
	float AzMin = _SelfPos.z - _SelfSize.z / 2;

	float BxMax = _ColPos.x + _ColSize.x / 2;
	float BxMin = _ColPos.x - _ColSize.x / 2;
	float ByMax = _ColPos.y + _ColSize.y / 2;
	float ByMin = _ColPos.y - _ColSize.y / 2;
	float BzMax = _ColPos.z + _ColSize.z / 2;
	float BzMin = _ColPos.z - _ColSize.z / 2;

		// 左
	if ((AxMin < BxMax) &&
		// 右
		(AxMax > BxMin) &&
		// 上
		(AyMin < ByMax) &&
		// 下
		(AyMax > ByMin) &&
		// 後ろ
		(AzMin < BzMax) &&
		// 前
		(AzMax > BzMin))
	{
		return true;
	}

	return false;
}

template<typename T>
inline bool Collision::isCollision2DBox()
{
	Scene* _Scene = Manager::GetScene();
	std::vector<T*> _CollideObj = _Scene->GetGameObjects<T>();

	for (auto object : _CollideObj)
	{
		auto C = object->GetComponent<Collision>();
		if (C != NULL)
		{
			D3DXVECTOR3 ObjectPos = object->GetPosition();
			D3DXVECTOR3 ObjectSize = object->GetSize();

			D3DXVECTOR3 SelfPos = m_GameObject->GetPosition();
			D3DXVECTOR3 SelfSize = m_GameObject->GetSize();

			float AxMax = SelfPos.x + (SelfSize.x / 2);
			float AxMin = SelfPos.x - (SelfSize.x / 2);
			float AyMax = SelfPos.y + (SelfSize.y / 2);
			float AyMin = SelfPos.y - (SelfSize.y / 2);

			float BxMax = ObjectPos.x + (ObjectSize.x / 2);
			float BxMin = ObjectPos.x - (ObjectSize.x / 2);
			float ByMax = ObjectPos.y + (ObjectSize.y / 2);
			float ByMin = ObjectPos.y - (ObjectSize.y / 2);

			if ((AxMin < BxMax) &&
				(AxMax > BxMin) &&
				(AyMin < ByMax) &&
				(AyMax > ByMin))
			{
				return true;
			}
		}
	}

	return false;
}