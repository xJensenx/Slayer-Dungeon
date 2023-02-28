#pragma once
class PauseMenuUIType
{
protected:
	class PauseMenuUI* m_PauseMenuUI;

public:
	PauseMenuUIType() {}
	~PauseMenuUIType() {}

	void SetCharacter(class PauseMenuUI* pPause) { m_PauseMenuUI = pPause; }

	virtual void Init() = 0;
	virtual void Press() = 0;
};

class PauseMenuUIResume : public PauseMenuUIType
{
public:
	void Init() override;
	void Press() override;
};

class PauseMenuUITitle : public PauseMenuUIType
{
public:
	void Init() override;
	void Press() override;
};

class PauseMenuUIQuit : public PauseMenuUIType
{
public:
	void Init() override;
	void Press() override;
};
