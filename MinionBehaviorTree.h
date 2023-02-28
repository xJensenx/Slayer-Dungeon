#pragma once
class MinionBehaviorTree
{
protected:
	// Minionクラス
	class Minion* m_Character;
	// Minionのアニメーションマネージャー
	class MinionAnimation* m_AnimationTree;
public:
	MinionBehaviorTree() {}
	~MinionBehaviorTree() {}

	// キャラクターをセット
	void SetCharacter(Minion* Character) { m_Character = Character; }
	// アニメーションマネージャーをセット
	void SetAnimationTree(MinionAnimation* Animation) { m_AnimationTree = Animation; }

	// 初期化
	virtual void Init() = 0;
	// 更新処理
	virtual void Update() = 0;
};

class MinionBehaviorTree_Idle : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Chase : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Attack : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_BeenHit : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_TutorialBeenHit : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Show : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

class MinionBehaviorTree_Dead : public MinionBehaviorTree
{
public:
	void Init() override;
	void Update() override;
};

