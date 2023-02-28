#pragma once
#include <list>
#include "Component.h"
#include "AnimationManager.h"

class GameObject
{
public:
	// 優先度
	enum Priority
	{
		FirstPri,
		SecondPri,
		ThirdPri,
		MaxPri
	};
protected:// アクセス指定子
	bool m_Destroy = false;				// 破壊されたかどうか
	D3DXVECTOR3 m_Position;				// 座標
	D3DXVECTOR3 m_PrevPos;				// 前の座標
	D3DXVECTOR3 m_Rotation;				// 回転
	D3DXVECTOR3 m_LocalPos;				// ローカル座標
	D3DXVECTOR3 m_LocalRot;				// ローカル回転
	D3DXVECTOR3 m_LocalSca;				// ローカルスケール
	D3DXQUATERNION m_Quaternion;		// 
	D3DXVECTOR3 m_Scale;				// スケール
	D3DXVECTOR3 m_Size;					// サイズ
	D3DXVECTOR3 m_Target;				// ターゲット（カメラ用）
	bool m_ShadowDepth = false;			// シャドウがあるかどうか
	bool m_isDamaged = false;			// ダメージされたかどうか
	bool m_Cinematic = false;			// カットシーン中かどうか
	bool m_Pause = false;				// ポーズしているかどうか
	bool m_IgnorePause = false;			// ポーズを無視して動けるかどうか

	// 親
	class GameObject* m_Parent = NULL;

	// コンポネント
	std::list<class Component*> m_Component[MaxPri];
	// 子
	std::list<class GameObject*> m_Child;
	// アニメーションマネージャー（アニメーションを管理する）
	class AnimationManager* m_AnimationManager = NULL;
public:
	GameObject() {}				// コントラクタ
	virtual ~GameObject() {}	// デストラクタ（仮想関数）

	// 初期化処理
	virtual void Init() = 0; // 純粋仮想関数

	// ダメージを与えられた
	virtual void DealDamage(float Dmg)
	{
		if (m_isDamaged) return;

		m_isDamaged = true;
	}
	// ノックバックダメージを与えられた
	virtual void KnockBackDamage(float Dmg, D3DXVECTOR3 Dir) {}

	// 終了処理
	virtual void Uninit()
	{
		for (int i = 0; i < MaxPri; i++)
		{
			for (auto c : m_Component[i])
			{
				c->Uninit();
				delete c;
			}
			// listの中身を解放する
			m_Component[i].clear();
		}
		for (auto c : m_Child)
		{
			c->Uninit();
			delete c;
		}
		m_Child.clear();

		if (m_AnimationManager != NULL)
		{
			m_AnimationManager->Uninit();
		}
	}
	// 更新処理
	virtual void Update()
	{
		if (m_AnimationManager != NULL)
		{
			m_AnimationManager->Update();
		}
		for (int i = 0; i < MaxPri; i++)
		{
			for (auto c : m_Component[i])
			{
				c->Update();
			}
		}
		for (auto c : m_Child)
		{
			c->Update();
		}

		if (m_Parent != NULL)
		{
			m_Position = m_Parent->m_Position + m_LocalPos;
			m_Rotation = m_Parent->m_Rotation + m_LocalRot;
		}

		m_PrevPos = m_Position;
	}
	// 描画処理
	virtual void Draw()
	{
		for (int i = 0; i < MaxPri; i++)
		{
			for (auto c : m_Component[i])
			{
				c->Draw();
			}
		}
		for (auto c : m_Child)
		{
			c->Draw();
		}
	}

	// コンポーネントを追加
	template<typename T>
	T* AddComponent(Priority _Pri)
	{
		T* _Component = new T();
		_Component->SetGameObject(this);
		_Component->Init();
		m_Component[_Pri].push_back(_Component);

		return _Component;
	}

	// アニメーションマネージャーを追加
	template<typename T>
	T* AddAnimationManager()
	{
		T* _AnimationManager = new T();
		_AnimationManager->SetGameObject(this);
		AnimModelManager* GameObjectAnim = GetComponent<AnimModelManager>();
		_AnimationManager->SetAnimModel(GameObjectAnim);
		_AnimationManager->Init();
		m_AnimationManager = _AnimationManager;

		return _AnimationManager;
	}

	// アニメーションマネージャーを取得
	template<typename T>
	T* GetAnimationManager()
	{
		if (typeid(*m_AnimationManager) == typeid(T))
		{
			return (T*)m_AnimationManager;
		}

		return NULL;
	}

	// コンポーネントを取得
	template<typename T>
	T* GetComponent()
	{
		for (int i = 0; i < MaxPri; i++)
		{
			for (Component* object : m_Component[i])
			{
				if (typeid(*object) == typeid(T)) // 型を調べる（RTTI動的型情報）
				{
					return (T*)object;
				}
			}
		}
		return NULL;
	}

	// 子を追加
	template<typename T>
	T* AddChild()
	{
		T* _Child = new T();
		_Child->SetParent(this);
		_Child->Init();
		m_Child.push_back(_Child);

		return _Child;
	}
	
	// 子を取得
	template<typename T>
	T* GetChild()
	{
		for (GameObject* object : m_Child)
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	// 破壊されるかどうか
	virtual void SetDestroy() { m_Destroy = true; }

	// YawPitchRoll
	// Forwardを取得
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		
		D3DXMatrixRotationYawPitchRoll(&rot, 
			m_Rotation.y, m_Rotation.x, m_Rotation.z);
		
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	// Rightを取得
	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, 
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}
	// Upを取得
	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, 
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
	}

	// Quaternion
	// Forwardを取得
	D3DXVECTOR3 GetQuaternionForward()
	{
		D3DXMATRIX rot;

		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 Forward;
		Forward.x = rot._31;
		Forward.y = rot._32;
		Forward.z = rot._33;

		return Forward;
	}
	// Rightを取得
	D3DXVECTOR3 GetQuaternionRight()
	{
		D3DXMATRIX rot;

		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 Right;
		Right.x = rot._11;
		Right.y = rot._12;
		Right.z = rot._13;

		return Right;
	}
	// Upを取得
	D3DXVECTOR3 GetQuaternionUp()
	{
		D3DXMATRIX rot;

		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 Up;
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;

		return Up;
	}

	// 破壊されるかどうかの処理
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else 
		{
			return false;
		}
	}

	// 破壊されたを取得
	bool GetDestroy() { return m_Destroy; }
	// Cinematicモードに入ってるかどうか
	bool GetCinematicMode() { return m_Cinematic; }
	// 影ついているかどうか
	bool GetShadowDepth() { return m_ShadowDepth; }
	// 前の座標を取得
	D3DXVECTOR3 GetPrevPos() { return m_PrevPos; }
	// 今の座標を取得
	D3DXVECTOR3 GetPosition() { return m_Position; }
	// 回転を取得
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	// ターゲットを取得
	D3DXVECTOR3 GetTargetPos() { return m_Target; }
	// クォータニオンを取得
	D3DXQUATERNION GetQuaternion() { return m_Quaternion; }
	// スケールを取得
	D3DXVECTOR3 GetScale() { return m_Scale; }
	// サイズを取得
	D3DXVECTOR3 GetSize() { return m_Size; }
	// XのOBBを取得
	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		if (m_Size.x > 0.0f)
		{
			return vx * (m_Size.x / 2);
		}
		else
		{
			return vx * 0.5f;
		}
	}
	// YのOBBを取得
	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vy;
		vy.x = world._21;
		vy.y = world._22;
		vy.z = world._23;

		if (m_Size.y > 0.0f)
		{
			return vy * (m_Size.y / 2);
		}
		else
		{
			return vy * 0.5f;
		}
	}
	// ZのOBBを取得
	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		if (m_Size.z > 0.0f)
		{
			return vz * (m_Size.z / 2);
		}
		else
		{
			return vz * 0.5f;
		}
	}

	// ポジション
	void SetInformation(D3DXVECTOR3 Pos) { m_Position = Pos; }
	// ポジション、回転
	void SetInformation(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot) { m_Position = Pos, m_Rotation = Rot; }
	// ポジション、回転、スケール
	void SetInformation(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Sca) { m_Position = Pos, m_Rotation = Rot, m_Scale = Sca; }

	// 座標を設置
	void SetPosition(D3DXVECTOR3 Pos) { m_Position = Pos; }
	// 回転を設置（Yaw,Pitch,Rollのため、Math::PI() = 180°）
	void SetRotation(D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	// スケールを設置
	void SetScale(D3DXVECTOR3 Sca) { m_Scale = Sca; }
	// サイズを設置
	void SetSize(D3DXVECTOR3 Siz) { m_Size = Siz; }

	// 子オブジェクトのため（デバッグ中）
	void SetLocalPos(D3DXVECTOR3 Pos) { m_LocalPos = Pos; }
	void SetLocalRot(D3DXVECTOR3 Rot) { m_LocalRot = Rot; }

	// 親オブジェクトを設置（デバッグ中）
	void SetParent(GameObject* Parent) { m_Parent = Parent; }
	// カメラのターゲットの設置
	void SetTarget(D3DXVECTOR3 Tar) { m_Target = Tar; }
	// 影があるかどうか
	void SetShadowDepth(bool ShadowDepth) { m_ShadowDepth = ShadowDepth; }	
	// カットシーンに入っているの状態を設置
	void SetCinematicMode(bool Mode) { m_Cinematic = Mode; }
	// ポーズする
	void SetPause(bool Pause) { m_Pause = Pause; }
	// ポーズを無視するのをセットする
	void SetIgnorePause(bool Ignore) { m_IgnorePause = Ignore; }
	// Quaternionをセット
	void SetQuaternion(D3DXQUATERNION Qua) { m_Quaternion = Qua; }
	// isDamagedをセット
	void SetisDamaged(bool Damage) { m_isDamaged = Damage; }
	

};