#include "main.h"
#include "manager.h"
#include "RigidBody.h"

// 初期化処理
void RigidBody::Init()
{
	m_RigidType = Dynamic;
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Mass = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Gravity = 0.0f;
}

// 終了処理
void RigidBody::Uninit()
{
}

// 更新処理
void RigidBody::Update()
{
	// ゲームオブジェクトの座標を速度で加算しています
	m_GameObject->SetInformation(m_GameObject->GetPosition() + m_Velocity);

	// 速度がだんだん減ります
	if (!m_IgnoreMass)
	{
		m_Velocity.x -= m_Velocity.x * m_Mass.x;
		m_Velocity.y -= m_Velocity.y * m_Mass.y;
		m_Velocity.z -= m_Velocity.z * m_Mass.z;
	}
	
	// 加速度を追加する
	m_Velocity.x += m_Accelerate.x;
	m_Velocity.y += m_Accelerate.y;
	m_Velocity.z += m_Accelerate.z;
	
	// Yの速度が重力で減ります
	if (!m_IgnoreGrav) m_Velocity.y -= m_Gravity;
}
