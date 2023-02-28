#pragma once
#include "GameObject.h"
class HeadTailPos
{
public:
    HeadTailPos() {}
    ~HeadTailPos() {}

    // �擪
    D3DXVECTOR3 m_HeadPos;
    // ����
    D3DXVECTOR3 m_TailPos;
};

class SwordTrail :
    public GameObject
{
private:
    // �L�^������
    int m_SaveCnt = 0;
    // �擪�̍��W����̍��W���L�^����
    class HeadTailPos* m_TrailPos[2];
    // �`��ł��邩�ǂ���
    bool m_CanDraw = false;
    // �`�掞��
    float m_Duration;
    // �F�̐ݒu
    D3DXVECTOR4 m_Color;

    // �o�b�t�@�[
    ID3D11Buffer* m_VertexBuffer;

    // �e�N�X�`��
    static ID3D11ShaderResourceView* m_Texture;

    // ���_�V�F�[�_�[
    static ID3D11VertexShader* m_VertexShader;
    // �s�N�Z���V�F�[�_�[
    static ID3D11PixelShader* m_PixelShader;
    // ���_���C�A�E�g
    static ID3D11InputLayout* m_VertexLayout;


public:
    // Load��Unload�֐�
    static void Load();
    static void Unload();

    void Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;

    // �O�Ղ�`�揀��
    void InitTrail();

    // �O�Ղ̃|�W�V�������Z�b�g
    void SaveTrailPos(D3DXVECTOR3 HeadPos, D3DXVECTOR3 TailPos)
    {
        if (m_SaveCnt >= 2) return;

        if (m_TrailPos[m_SaveCnt] == NULL)
        {
            // �|�W�V�����̍��W�ۑ�
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
    // �F�̒���
    void ChangeColor(D3DXVECTOR4 Color) { m_Color = Color; }
    
    // �`�悵�����ǂ���
    bool GetTrailDraw() { return m_CanDraw; }
    
};

