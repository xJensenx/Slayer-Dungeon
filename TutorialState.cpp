#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "ComponentInclude.h"

#include "Tutorial.h"
#include "TutorialState.h"
#include "Player.h"
#include "Minion.h"
#include "TutorialUI.h"
#include "input.h"

void TutorialState_Mission01::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// ミッション０１を追加し位置調整
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission01>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission01Hint>();
		
		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UIの目標座標
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UIの初期座標
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;
			// UI用Lerp変数
			D3DXVECTOR3 LerpUI;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// 座標更新
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
			// ボタン押されたのbool文初期化
			for (int i = 0; i < 4; i++)
			{
				m_PushButton[i] = false;
			}
			// チュートリアル完成の初期化
			m_Finish = false;
		}
		break;
	case 2:
		// 移動キー全部押された場合次のステップ進む
		if (Input::GetKeyTrigger('W'))
		{
			m_PushButton[0] = true;
		}

		if (Input::GetKeyTrigger('A'))
		{
			m_PushButton[1] = true;
		}

		if (Input::GetKeyTrigger('S'))
		{
			m_PushButton[2] = true;
		}

		if (Input::GetKeyTrigger('D'))
		{
			m_PushButton[3] = true;
		}

		// 全部ボタン押されたの確認
		m_Finish = true;
		for (int i = 0; i < 4; i++)
		{
			// まだfalseがあるとFinishをfalseにする
			if (!m_PushButton[i]) m_Finish = false;
		}

		// ボタンが全部押されたら次のステップ
		if (m_Finish)
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// チュートリアルUIをクリア状態にする
			m_MissionUI->SetFinish();
			// 次のステップ
			m_State = 3;
		}
		break;
	case 3:
		// ２秒待ってからチュートリアル変更
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 次のステップ
			m_State = 4;
			return;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ステート変更
			m_Tutorial->ChangeState<TutorialState_Mission02>();
		}
		break;
	}
}

void TutorialState_Mission02::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// ミッション０１を追加し位置調整
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission02>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission02Hint>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UIの目標座標
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UIの初期座標
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;
			// UI用Lerp変数
			D3DXVECTOR3 LerpUI;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// 座標更新
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
			// チュートリアル完成の初期化
			m_Finish = false;
		}
		break;
	case 2:
		// ボタンが全部押されたら次のステップ
		if (m_Finish)
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// チュートリアルUIをクリア状態にする
			m_MissionUI->SetFinish();
			// 次のステップ
			m_State = 3;
		}
		break;
	case 3:
		// ２秒待ってからチュートリアル変更
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 次のステップ
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ステート変更
			m_Tutorial->ChangeState<TutorialState_Mission03>();
		}
		break;
	}

}

void TutorialState_Mission03::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// ミッション０１を追加し位置調整
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission03>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission03Hint>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UIの目標座標
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UIの初期座標
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;
			// UI用Lerp変数
			D3DXVECTOR3 LerpUI;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// 座標更新
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
			// チュートリアル完成の初期化
			m_Finish = false;
		}
		break;
	case 2:
		// ボタンが全部押されたら次のステップ
		if (m_Finish)
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// チュートリアルUIをクリア状態にする
			m_MissionUI->SetFinish();
			// 次のステップ
			m_State = 3;
		}
		break;
	case 3:
		// ２秒待ってからチュートリアル変更
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 次のステップ
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ステート変更
			m_Tutorial->ChangeState<TutorialState_Mission04>();
		}
		break;
	}
}

void TutorialState_Mission04::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// ミッション０１を追加し位置調整
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission04>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission04Hint>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UIの目標座標
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UIの初期座標
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;
			// UI用Lerp変数
			D3DXVECTOR3 LerpUI;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// 座標更新
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
			// チュートリアル完成の初期化
			m_Finish = false;

			// Minionを攻撃できるようにする
			m_Tutorial->GetMinion()->ChangeBehavior<MinionBehaviorTree_Chase>();
		}
		break;
	case 2:
		// ボタンが全部押されたら次のステップ
		if (m_Finish)
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// チュートリアルUIをクリア状態にする
			m_MissionUI->SetFinish();
			// 次のステップ
			m_State = 3;
		}
		break;
	case 3:
		// ２秒待ってからチュートリアル変更
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 次のステップ
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ステート変更
			m_Tutorial->ChangeState<TutorialState_Mission05>();
		}
		break;
	}
}

void TutorialState_Mission05::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// プレイヤーのMpを全回復
		m_Tutorial->GetPlayer()->SetCurMp(m_Tutorial->GetPlayer()->GetMaxMp());

		// Minionを止める
		m_Tutorial->GetMinion()->ChangeBehavior<MinionBehaviorTree_Idle>();

		// ミッション０１を追加し位置調整
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission05>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission05Hint>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UIの目標座標
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UIの初期座標
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;
			// UI用Lerp変数
			D3DXVECTOR3 LerpUI;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// 座標更新
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
			// チュートリアル完成の初期化
			m_Finish = false;
			for (int i = 0; i < 3; i++)
			{
				m_PushButton[i] = false;
			}
		}
		break;
	case 2:
		m_Finish = true;
		for (int i = 0; i < 3; i++)
		{
			if (!m_PushButton[i]) m_Finish = false;
		}

		// ボタンが全部押されたら次のステップ
		if (m_Finish)
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// チュートリアルUIをクリア状態にする
			m_MissionUI->SetFinish();
			// 次のステップ
			m_State = 3;
		}
		break;
	case 3:
		// ２秒待ってからチュートリアル変更
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 次のステップ
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ステート変更
			m_Tutorial->ChangeState<TutorialState_Mission06>();
		}
		break;
	}
}

void TutorialState_Mission06::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// プレイヤーのMpを全回復
		m_Tutorial->GetPlayer()->SetCurDp(m_Tutorial->GetPlayer()->GetMaxDp());

		// ミッション０１を追加し位置調整
		m_MissionUI = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionUI->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f));
		m_MissionUI->SetUIType<TutorialUIType_Mission06>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_Mission06Hint>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// UIの目標座標
			D3DXVECTOR3 UITargetPos = D3DXVECTOR3(SCREEN_WIDTH - 130.0f, 100.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// UIの初期座標
			D3DXVECTOR3 UIInitPos = D3DXVECTOR3(SCREEN_WIDTH + 130.0f, 100.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;
			// UI用Lerp変数
			D3DXVECTOR3 LerpUI;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);
			D3DXVec3Lerp(&LerpUI, &UIInitPos, &UITargetPos, T);

			// 座標更新
			m_MissionUI->SetPosition(LerpUI);
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
			// チュートリアル完成の初期化
			m_Finish = false;
		}
		break;
	case 2:
		// ボタンが全部押されたら次のステップ
		if (m_Finish)
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// チュートリアルUIをクリア状態にする
			m_MissionUI->SetFinish();
			// 次のステップ
			m_State = 3;
		}
		break;
	case 3:
		// ２秒待ってからチュートリアル変更
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;

			// 次のステップ
			m_State = 4;
		}
		break;
	case 4:
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// ステート変更
			m_Tutorial->ChangeState<TutorialState_TutorialFinish>();
		}
		break;
	}
}

void TutorialState_TutorialFinish::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// プレイヤーのMpを全回復
		m_Tutorial->GetPlayer()->SetCurMp(m_Tutorial->GetPlayer()->GetMaxMp());
		// プレイヤーのDpを全回復
		m_Tutorial->GetPlayer()->SetCurDp(m_Tutorial->GetPlayer()->GetMaxDp());

		// チュートリアル完了を設置
		m_Tutorial->SetFinish();

		// Minionを攻撃できるようにする
		m_Tutorial->GetMinion()->ChangeBehavior<MinionBehaviorTree_Chase>();

		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_TutorialFinish>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
		}
		break;
	case 2:
		// ２秒間待ってから次のステップ進む
		if (m_CurTime < 2.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// ステップ初期化
			m_State = 3;
			return;
		}
		break;
	case 3:
		// UIを上に戻す
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			m_State = 4;
		}
		break;
	}

}

void TutorialState_Greeting::Update()
{
	// 順番に進む
	switch (m_State)
	{
	case 0:
		// ミッション０１のヒントを追加する
		m_MissionHint = m_Tutorial->AddGameObject<TutorialUI>(Scene::Layer_UILayer);
		m_MissionHint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
		m_MissionHint->SetUIType<TutorialUIType_GreetingHint>();

		// タイム初期化
		m_CurTime = 0.0f;

		// 次のステートに進む
		m_State = 1;
		break;
	case 1:
		// UIを移動させる
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintInitPos, &HintTargetPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// 次のステップ
			m_State = 2;
		}
		break;
	case 2:
		// ２秒間待ってから次のステップ進む
		if (m_CurTime < 2.0f * Manager::Time)
		{
			m_CurTime++;
		}
		else
		{
			// 時間初期化
			m_CurTime = 0.0f;
			// ステップ初期化
			m_State = 3;
			return;
		}
		break;
	case 3:
		// UIを上に戻す
		if (m_CurTime < 1.0f * Manager::Time)
		{
			m_CurTime++;
			float T = m_CurTime / (1.0f * Manager::Time);

			// ヒントの目標座標
			D3DXVECTOR3 HintTargetPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
			// ヒントの初期座標
			D3DXVECTOR3 HintInitPos = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);
			// ヒント用Lerp変数
			D3DXVECTOR3 LerpHint;

			// 線形補間
			D3DXVec3Lerp(&LerpHint, &HintTargetPos, &HintInitPos, T);

			// 座標更新
			m_MissionHint->SetPosition(LerpHint);
		}
		else
		{
			// ミッション１に進む
			m_Tutorial->ChangeState<TutorialState_Mission01>();
		}
		break;
	}
}
