#pragma once
#include "GameObject.h"
class TitleLogo : public GameObject
{
private:
	// �G�t�F�N�g���o�����ǂ���
	bool m_TitleEffect;
	// �G�t�F�N�g�o������
	float m_TitleEffectTime;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// �^�C�g�����S�̃p�[�e�B�N���G�t�F�N�g
	void TitleEffect();
	// �^�C�g���G�t�F�N�g�����
	void SetTitleEffect(bool TitleEffect) { m_TitleEffect = TitleEffect; }
};

