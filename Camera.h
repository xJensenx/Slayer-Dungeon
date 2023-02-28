#pragma once
#include "GameObject.h"

class Camera: public GameObject
{
public:
	enum BlendType
	{
		Lerp = 0,
		Hermite
	};
private:
	D3DXMATRIX	m_ViewMatrix;
	D3DXMATRIX	m_ProjectionMatrix;
	bool		m_PilotMode = false;

	// ブレンドの種類
	BlendType m_BlendType;

	// 自動回転前の座標
	D3DXVECTOR3 m_BeforeRotation;

	// 自動的に前に回転する時間
	const float m_TotalRotateTime = 1.5f * Manager::Time;

	// 今の回転している時の時間
	float m_CurRotateTime;

	// 自動回転するまで何秒待ちます
	const float m_TotalWaitTime = 4.0f * Manager::Time;
	// 回転が自動的にプレイヤーの前に回転させるの待ち時間
	float m_WaitTime;
	// 前のフレームのRotation値
	D3DXVECTOR3 m_OldRotation;

	// カメラシェーク用
	D3DXVECTOR3 m_Magnitude;
	// カメラシェーク用
	D3DXVECTOR3 m_Amplitude;
	// カメラシェーク中
	bool m_Shaking;
	// カメラシェークの時間
	float m_ShakeTime;
	// 減衰時間
	float m_RecoverTime;
	// 合計減衰時間
	const float m_TotalRecoverTime = 1.5f * Manager::Time;
	// 初期Magnitude
	D3DXVECTOR3 m_InitMagnitude;

	// カットシーン用ブレンドターゲットとポジション
	D3DXVECTOR3 m_BeforePos;
	D3DXVECTOR3 m_AfterPos;
	D3DXVECTOR3 m_BeforeTarget;
	D3DXVECTOR3 m_AfterTarget;
	D3DXVECTOR3 m_BeforeTan;
	D3DXVECTOR3 m_AfterTan;

	// カットシーン用時間
	float m_BlendTime;
	float m_TotalBlendTime = 3.0f * Manager::Time;

	// ブレンドしているかどうか
	bool m_isBlend;

	// ターゲットのブレンドしているか
	bool m_isTargetBlend;

	// ターゲットブレンド時間
	float m_TargetBlendTime;

	// 次のターゲット
	D3DXVECTOR3 m_NewTargetPos;

	// ブレンド前のターゲット
	D3DXVECTOR3 m_OldTargetPos;
	
	// ブレンド前のポジション
	D3DXVECTOR3 m_OldPos;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }

	bool CheckView(D3DXVECTOR3 Position, float Size);
	bool GetIsBlend() { return m_isBlend; }

	// デバッグ用
	void SetPilotMode(bool Pilot)
	{
		m_PilotMode = Pilot;
	}

	// カメラシェーク（Magの値は0.1～がベスト）
	void ShakeCam(D3DXVECTOR3 Mag, float Time);

	// 元の場所に戻る
	void BlendBack(float TotalBlendTime);

	// カメラブレンド
	void BlendTo(D3DXVECTOR3 Pos, D3DXVECTOR3 Tar, float BlendTime)
	{
		if (!m_Cinematic) return;

		m_BlendType = Lerp;
		m_BlendTime = 0.0f;
		m_BeforePos = m_Position;
		m_BeforeTarget = m_Target;
		m_AfterPos = Pos;
		m_AfterTarget = Tar;
		m_TotalBlendTime = BlendTime * Manager::Time;
		m_isBlend = true;
	}

	// カメラブレンド（エルミート）
	void HermiteBlendTo(D3DXVECTOR3 Pos, D3DXVECTOR3 Tar, D3DXVECTOR3 Tan1, D3DXVECTOR3 Tan2, float BlendTime)
	{
		if (!m_Cinematic) return;

		m_BlendType = Hermite;
		m_BlendTime = 0.0f;
		m_BeforePos = m_Position;
		m_BeforeTarget = m_Target;
		m_AfterPos = Pos;
		m_AfterTarget = Tar;
		m_TotalBlendTime = BlendTime * Manager::Time;
		m_isBlend = true;
		m_BeforeTan = Tan1;
		m_AfterTan = Tan2;
	}

	// Cinematicモードの時直接座標をセットする
	void SetOldPosTar(D3DXVECTOR3 Pos, D3DXVECTOR3 Tar) { m_OldPos = Pos, m_OldTargetPos = Tar; }

	void InitOldPos()
	{
		m_OldPos = m_Position;
		m_OldTargetPos = m_Target;
	}
};

