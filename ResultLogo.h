#pragma once
#include "GameObject.h"
class ResultLogo : public GameObject
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

