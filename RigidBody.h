#pragma once
#include "Component.h"
class RigidBody : public Component
{
public:
	enum RigidType
	{
		Dynamic = 0,
		Kinematic,
		Static
	};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {};

	D3DXVECTOR3 GetVelocity() { return m_Velocity; }
	RigidType GetRigidType() { return m_RigidType; }

	void SetRigidType(RigidType _Type) { m_RigidType = _Type; }
	void SetGravity(float _Grav) { m_Gravity = _Grav; }
	void SetVelocity(D3DXVECTOR3 _Vel) { m_Velocity = _Vel; }
	void SetMass(D3DXVECTOR3 _Mass) { m_Mass = _Mass; }
	void SetAccelerate(D3DXVECTOR3 _Acc) { m_Accelerate = _Acc; }
	void SetIgnoreMass(bool Ignore) { m_IgnoreMass = Ignore; }
	void SetIgnoreGrav(bool Ignore) { m_IgnoreGrav = Ignore; }
	void AddForce(D3DXVECTOR3 _Force) { m_Velocity += _Force; }

private:
	RigidType m_RigidType;			// 
	D3DXVECTOR3 m_Velocity;			// ���x
	D3DXVECTOR3 m_Mass;				// ����
	D3DXVECTOR3 m_Accelerate;		// �����x
	float m_Gravity;				// �d��
	bool m_IgnoreMass;				// ���ʂ𖳎�
	bool m_IgnoreGrav;				// �d�͂𖳎�
};

