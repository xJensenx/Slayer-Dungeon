#pragma once
class OBB
{
public:
	enum Direct
	{
		FORWARD = 0,
		RIGHT,
		UP,
		MAX
	};
protected:
	D3DXVECTOR3 m_Pos;              // 位置
	D3DXVECTOR3 m_NormaDirect[Direct::MAX];   // 方向ベクトル
	FLOAT m_fLength[Direct::MAX];             // 各軸方向の長さ

public:
	void SetDirect(int elem, D3DXVECTOR3 _Direct) { m_NormaDirect[elem] = _Direct; }
	void SetPos(D3DXVECTOR3 _Pos) { m_Pos = _Pos; }
	void SetLength(int elem, FLOAT _Length) { m_fLength[elem] = _Length; }

	// 指定軸番号の方向ベクトルを取得
	D3DXVECTOR3 GetDirect(int elem) { return m_NormaDirect[elem]; }
	// 指定軸方向の長さを取得
	FLOAT GetLen_W(int elem) { return m_fLength[elem]; }
	// 位置を取得
	D3DXVECTOR3 GetPos_W() { return m_Pos; }
};

