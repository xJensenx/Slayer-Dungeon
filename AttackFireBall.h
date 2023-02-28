#pragma once
#include "GameObject.h"

#include "AttackFireBall_Type.h"
class AttackFireBall :
    public GameObject
{
private:
    // ファイアボールのタイプのクラス
    class AttackFireBall_Type* m_FireBallType;
    // 目標オブジェクト
    class GameObject* m_TargetObj;
    // エルミート用Tan
    D3DXVECTOR3 m_ShootTan;
    // 初期角度
    float m_InitAngle;
public:
    void Init() override;
    void Update() override;

    // タイプの設置
    template <typename T>
    void SetType()
    {
        // 既に存在していると消します
        if (m_FireBallType != NULL)
        {
            delete m_FireBallType;
            m_FireBallType = NULL;
        }

        // 新しいタイプを宣言し初期化します
        T* Type = new T();
        Type->SetCharacter(this);
        Type->SetTarget(m_TargetObj);
        Type->Init();
        // タイプを自分のタイプに追加する
        m_FireBallType = Type;
    }

    // エルミート用Tanを設置
    void SetHermiteTan(D3DXVECTOR3 _Tan) { m_ShootTan = _Tan; }

    // ターゲットオブジェクトをセット
    void SetTargetObj(class GameObject* Obj) { m_TargetObj = Obj; }

    // 初期角度を設置
    void SetInitAngle(float Angle) { m_InitAngle = Angle; }

    // 初期角度を取得
    float GetInitAngle() { return m_InitAngle; }

    // エルミート用Tanを取得
    D3DXVECTOR3 GetHermiteTan() { return m_ShootTan; }
};

