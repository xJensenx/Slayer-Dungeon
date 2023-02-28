#pragma once
#include "GameObject.h"
#include "PlayerSkill.h"

class Player :public GameObject // 継承
{
public:
	// 攻撃の種類
	enum AttackType
	{
		NotAttacking = 0,
		Attack01,
		Attack02,
		Attack03,
		Attack04,
		Attack05,
		Block
	};
private:
	// プレイヤーアニメーション
	class PlayerAnimation* m_PlayerAnimation;

	class PlayerSkillUI* m_SkillUI[3];

	// Mpバーのクラス
	class PlayerMpBar* m_MpBar;

	// Dpバーのクラス
	class PlayerDpBar* m_DpBar;

	// 移動速度
	float m_MovementSpd = 0.01f;
	// 攻撃しているかどうか
	bool m_isAttacking;
	// 次の攻撃実行していい
	bool m_NextAtk;
	// 現在の攻撃の種類
	AttackType m_AttackType;
	// 動く準備する
	bool m_ReadyToMove = false;
	// 動く時間
	float m_ReadyTime;
	// WalkValue
	D3DXVECTOR2 m_KeyValue;

	// 攻撃速度
	float m_AttackSpd;

	// ステータスの色を付ける条件
	bool m_StatusColor;
	// ステータスの色は何秒後元に戻る
	float m_StatusTime;
	// 
	float m_StatusInitTime;
	// ステータスの最初の色
	D3DXVECTOR4 m_StatusInitColor;

	// 剣の情報
	class Sword* m_Swords[5];
	// 剣が回復する
	float m_SwordRecover[5];
	// 剣が回復する時間
	float m_RecoverTime = 5.0f * Manager::Time;
	// 現在の剣の番号
	int m_CurrentNo;

	// 死んでるかどうか
	bool m_isDead;

	// 回避しているかどうか
	bool m_Dodge;

	// 現在のHp
	float m_CurHp;

	// フルのHp
	float m_MaxHp;

	// 現在のHp
	float m_CurMp;

	// フルのHp
	float m_MaxMp;

	// 現在のDp
	float m_CurDp;

	// フルのDp
	float m_MaxDp;

	// プレイヤーのコマンドのスロット番号
	int m_Slot;

	// 前のスロット番号
	int m_LastSlot;

	// コマンドリスト
	class PlayerCommand* m_CommandSlot[3];

	// プレイヤーステータス変数
	class PlayerStatusWarning* m_PlayerStatus;

	// プレイヤースキル
	class PlayerSkill* m_SkillSlot[3];


	// 防御しているかどうか
	bool m_isBlock;

	// 防御成功かどうか
	bool m_BlockSuccess;

	// 無敵時間
	float m_InvulTime;

	// 無敵に入っているかどうか
	bool m_Invulnerable;

	// Ult用変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝=
	// Ult用State
	int m_UltState;
	// Ultを使っているかどうか
	bool m_isUlt;
	// Ult用待ち時間
	float m_UltWaitTime;

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	// Skill用変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝=
	// クールダウン
	float m_CurCoolDown[3];
	// 最大クールダウン
	float m_MaxCoolDown[3];
	
	// 剣の雨のタイム
	float m_SwordRainTime;
	
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

public:
	void Init()override;	// 初期処理
	void Update()override;	// 更新処理
	void Draw()override;	// 描画処理

	// ダメージ受けた時
	void DealDamage(float Damage) override;

	// スキルセット
	template <typename T>
	void SetSkill(int Slot)
	{
		if (m_SkillSlot[Slot] != NULL)
		{
			delete m_SkillSlot[Slot];
			m_SkillSlot[Slot] = NULL;
		}

		T* Skill = new T();
		Skill->Init();
		Skill->SetCharacter(this);
		Skill->SetAnimationManager(m_PlayerAnimation);

		m_SkillSlot[Slot] = Skill;
	}

	// プレイヤースキルを使う
	void ActivateSkill(int Slot)
	{
		if (m_SkillSlot[Slot] != NULL && m_CurCoolDown[Slot] <= 0.0f)
		{
			m_SkillSlot[Slot]->Activate(Slot);
		}
	}

	// 無敵時間をセット
	void SetInvulTime(float Time) { m_InvulTime = Time * Manager::Time; }

	// スキルを装備
	void SetInitSkill();

	// スキルコマンド
	void SkillShortCut();

	// 新しい剣に切り替える
	void PrepareNewSwords();

	// 大ダメージ受けた時
	void KnockBackDamage(float Damage, D3DXVECTOR3 Dir) override;

	// 攻撃処理
	void AttackCombo(AttackType AT);

	// 次の攻撃もう実行していいセッター
	void ReadyToAtk() { m_NextAtk = true; }

	// 動く準備セッター
	void ReadyToMove(float Time)
	{
		m_ReadyToMove = true;
		m_ReadyTime = Time * Manager::Time;
	}
	// 回避処理
	void TimeToDodge();

	// 攻撃イベント
	void AttackEvent();

	// コマンド処理
	void CommandEvent();

	// コマンドチェック
	void CommandCheck();

	// 剣を補充する
	void RecoverSword();

	// Dodgeイベント
	void DodgeEvent();

	// 死んでる状態を取得
	bool GetIsDead() { return m_isDead; }

	// Mpをセット
	void SetCurMp(float Mp) { m_CurMp = Mp; }

	// Mpを増やす
	void AddMp(float AddAmt)
	{ 
		float TotalAmt = m_CurMp + AddAmt;
		if (TotalAmt > m_MaxMp)
		{
			m_CurMp = m_MaxMp;
			return;
		}

		m_CurMp = TotalAmt;
	}

	// Dpをセット
	void SetCurDp(float Dp) { m_CurDp = Dp; }

	// Dpを増やす
	void AddDp(float AddAmt) { m_CurDp += AddAmt; }

	// Hp,Mp,Dpの調整
	void AdjustGauge();

	// MpBarのゲッター
	class PlayerMpBar* GetMpBar() { return m_MpBar; }

	// DpBarのゲッター
	class PlayerDpBar* GetDpBar() { return m_DpBar; }

	// Ult中かどうか
	bool GetisUlt() { return m_isUlt; }

	// 現在のHpを取得
	float GetCurHp() { return m_CurHp; }

	// フルのHpを取得
	float GetMaxHp() { return m_MaxHp; }

	// 現在のMpを取得
	float GetCurMp() { return m_CurMp; }

	// フルのMpを取得
	float GetMaxMp() { return m_MaxMp; }

	// 現在のDpを取得
	float GetCurDp() { return m_CurDp; }

	// フルのDpを取得
	float GetMaxDp() { return m_MaxDp; }

	// 現在のクールダウンを取得
	float GetCurCooldown(int SlotNo) { return m_CurCoolDown[SlotNo]; }
	
	// 現在のクールダウンを取得
	float GetMaxCooldown(int SlotNo) { return m_MaxCoolDown[SlotNo]; }

	// 攻撃速度をゲット
	float GetAttackSpd() { return m_AttackSpd; }

	// 死亡時の処理
	void DeadEvent();

	// Ultを発動する
	void ActivateUlt();

	// Ult処理
	void UltCommand();

	// Ultのステートを切り替える
	void ChangeUltState(int State) { m_UltState = State; }

	// 移動処理
	void MoveEvent();
	
	// 回転処理
	void RotateEvent();

	// 防御が終わる
	void BlockFinish() { m_isBlock = false; m_BlockSuccess = false; }

	// 剣の防御アニメーション
	void SwordBlock(bool isBlock);

	// 待機状態に戻る
	void BackToIdle();

	// プレイヤーの色
	void StatusChangeColor();

	// プレイヤーの色を変える処理
	void ChangeBackColor(D3DXVECTOR4 Color, float Time);

	// スキル用関数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// スキル使う前の準備や条件 
	bool InitSkill();
	// カメラに向いて準備や条件
	bool InitRotCamSkill();
	// クールダウン用関数
	void CoolDownEvent();
	// クールダウンをセットする
	void SetCoolDown(int Slot) { m_CurCoolDown[Slot] = m_MaxCoolDown[Slot]; }

	// 全部の剣を射出する
	void ShootAllSword();
	// 剣の雨
	void RainSword();
	// チャージ撃つ
	void ChargeSword();
	// 剣を連続前に打つ
	void SwordMachineGun();
	// スキル０６
	void ShootSwordSkill06();
	// スキル０７（Comboの数字によって処理が変わります、１は最初の攻撃、２は二個目、３は最後）
	void Skill07Combo(int Combo);
	// スキル０８
	void Skill08Combo();
	// スキル０９
	void Skill09Combo();


	// 前に突っ込んで攻撃する
	void RushSword();

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
};