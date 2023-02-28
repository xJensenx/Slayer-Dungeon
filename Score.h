#pragma once
#include "GameObject.h"
class Score : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

