#pragma once
#include "GameObject.h"
class HeadTailPos
{
public:
    HeadTailPos() {}
    ~HeadTailPos() {}

    // 先頭
    D3DXVECTOR3 m_HeadPos;
    // 末尾
    D3DXVECTOR3 m_TailPos;
};

class SwordTrail :
    public GameObject
{
private:
    // 記録した数
    int m_SaveCnt = 0;
    // 先頭の座標や後ろの座標を記録する
    class HeadTailPos* m_TrailPos[2];
    // 描画できるかどうか
    bool m_CanDraw = false;
    // 描画時間
    float m_Duration;
    // 色の設置
    D3DXVECTOR4 m_Color;

    // バッファー
    ID3D11Buffer* m_VertexBuffer;

    // テクスチャ
    static ID3D11ShaderResourceView* m_Texture;

    // 頂点シェーダー
    static ID3D11VertexShader* m_VertexShader;
    // ピクセルシェーダー
    static ID3D11PixelShader* m_PixelShader;
    // 頂点レイアウト
    static ID3D11InputLayout* m_VertexLayout;


public:
    // LoadとUnload関数
    static void Load();
    static void Unload();

    void Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;

    // 軌跡を描画準備
    void InitTrail();

    // 軌跡のポジションをセット
    void SaveTrailPos(D3DXVECTOR3 HeadPos, D3DXVECTOR3 TailPos)
    {
        if (m_SaveCnt >= 2) return;

        if (m_TrailPos[m_SaveCnt] == NULL)
        {
            // ポジションの座標保存
            m_TrailPos[m_SaveCnt] = new HeadTailPos();
            m_TrailPos[m_SaveCnt]->m_HeadPos = HeadPos;
            m_TrailPos[m_SaveCnt]->m_TailPos = TailPos;

            m_SaveCnt++;

            if (m_SaveCnt >= 2)
            {
                m_CanDraw = true;
                InitTrail();
            }
        }
    }
    // 色の調整
    void ChangeColor(D3DXVECTOR4 Color) { m_Color = Color; }
    
    // 描画したかどうか
    bool GetTrailDraw() { return m_CanDraw; }
    
};

