#pragma once
#include "Scene.h"
class TestScene :
    public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

