#pragma once
class FadeSceneType
{
public:
	FadeSceneType() {}
	~FadeSceneType() {}
	
	// シーンをセット
	virtual void SetScene() = 0;
};

class FadeSceneType_Title : public FadeSceneType
{
public:
	void SetScene() override;
};

class FadeSceneType_Game : public FadeSceneType
{
public:
	void SetScene() override;
};

class FadeSceneType_Loading : public FadeSceneType
{
public:
	void SetScene() override;
};

class FadeSceneType_Result : public FadeSceneType
{
public:
	void SetScene() override;
};

class FadeSceneType_Tutorial : public FadeSceneType
{
public:
	void SetScene() override;
};

class FadeSceneType_Test : public FadeSceneType
{
public:
	void SetScene() override;
};

class FadeSceneType_Quit : public FadeSceneType
{
public:
	void SetScene() override;
};