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
	D3DXVECTOR3 m_Pos;              // �ʒu
	D3DXVECTOR3 m_NormaDirect[Direct::MAX];   // �����x�N�g��
	FLOAT m_fLength[Direct::MAX];             // �e�������̒���

public:
	void SetDirect(int elem, D3DXVECTOR3 _Direct) { m_NormaDirect[elem] = _Direct; }
	void SetPos(D3DXVECTOR3 _Pos) { m_Pos = _Pos; }
	void SetLength(int elem, FLOAT _Length) { m_fLength[elem] = _Length; }

	// �w�莲�ԍ��̕����x�N�g�����擾
	D3DXVECTOR3 GetDirect(int elem) { return m_NormaDirect[elem]; }
	// �w�莲�����̒������擾
	FLOAT GetLen_W(int elem) { return m_fLength[elem]; }
	// �ʒu���擾
	D3DXVECTOR3 GetPos_W() { return m_Pos; }
};

