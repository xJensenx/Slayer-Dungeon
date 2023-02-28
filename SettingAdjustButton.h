#pragma once
#include "GameObject.h"
class SettingAdjustButton :
    public GameObject
{
private:
    // 調整するUIクラス
    class SettingUI* m_ControlUI;
    // ０の値の時の座標
    D3DXVECTOR3 m_InitPos;
    // １の値の時の座標
    D3DXVECTOR3 m_TarPos;
    // 値（0.0～1.0）
    float m_Value;

    // 選択されている時のスプライト
    class SpriteComponent* m_Sprite;
    // 選択されてない時のスプライト
    class SpriteComponent* m_NSSprite;

    // 選択されている場合
    bool m_Chosen;
    // 押している場合
    bool m_isClick;

public:
    void Init() override;
    void Update() override;

    // 調整するUIクラスを設置
    void SetControlUI(class SettingUI* _UI) { m_ControlUI = _UI; }
    // 初期座標を設置
    void SetBothPos(D3DXVECTOR3 _Init, D3DXVECTOR3 _Tar) { m_InitPos = _Init; m_TarPos = _Tar; }
    // 選択されているセッター
    void SetChosen(bool Chose) { m_Chosen = Chose; }
    // 値のセッター
    void SetValue(float Val) { m_Value = Val; }

    // 選択されているゲッター
    bool GetChosen() { return m_Chosen; }
    // 値を取得
    float GetValue() { return m_Value; }

};

