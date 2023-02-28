#pragma once
#include "GameObject.h"
class Number :
    public GameObject
{
private:
    // スプライト
    std::vector<class SpriteComponent*> m_Number;
    // 数
    int m_Cnt;
    // 前の数
    int m_OldCnt;
    // 何桁
    int m_Numeric;
public:
    void Init() override;
    void Update() override;

    // 数を設定する
    void SetNumber(int Num)
    {
        m_Cnt = Num;
        LoadNumber();
    }

    // 桁数の設定
    void SetNumeric(int Num) { m_Numeric = Num; }

    // スプライトのロード
    void LoadNumber();
};

