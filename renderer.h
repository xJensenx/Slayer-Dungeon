#pragma once





struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};



struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXVECTOR4 Position;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;

	D3DXMATRIX	ViewMatrix;	// ライトカメラ行列
	D3DXMATRIX	ProjectionMatrix;	// ライトプロジェクション行列
};



class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_Device;
	static ID3D11DeviceContext*    m_DeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_ParameterBuffer;
	static ID3D11Buffer*			m_CameraBuffer;
	static ID3D11Buffer*			m_PlayerColorBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11DepthStencilView* m_ShadowDepthStencilView;
	static ID3D11ShaderResourceView* m_ShadowDepthShaderResourceView;

	static LIGHT m_Light;

protected:
	static Renderer* s_pRenderer;
	Renderer();
	Renderer(const Renderer& src);
	Renderer& operator = (const Renderer& src);

public:
	
	enum RenderMode
	{
		Wire = 0,
		Solid
	};
	static RenderMode Mode;

	static Renderer* GetInstance() {
		return s_pRenderer;
	}

	static RenderMode GetRenderMode()
	{
		return Mode;
	}

	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void AddLight()
	{
		// ライト
		m_Light.Enable = true;
		m_Light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
		m_Light.Position = D3DXVECTOR4(0.0f, 50.0f, 0.0f, 0.0f);
		D3DXVec4Normalize(&m_Light.Direction, &m_Light.Direction);
		m_Light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);//光の当たらない部分の反射係数
		m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//光の当たる部分の反射係数

		// ライトカメラのビュー行列を作成
		D3DXVECTOR3 Eye = D3DXVECTOR3(-10.0f, 10.0f, -10.0f);
		D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&m_Light.ViewMatrix, &Eye,
			&At, &Up);

		// ライトカメラのプロジェクション行列を作成
		D3DXMatrixPerspectiveFovLH(&m_Light.ProjectionMatrix, 1.0f,
			(float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 30.0f);
	}
	static void DrawLight()
	{
		// ライト
		m_Light.Enable = true;
		m_Light.Direction = m_Light.Direction;
		m_Light.Position = m_Light.Position;
		D3DXVec4Normalize(&m_Light.Direction, &m_Light.Direction);
		m_Light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f);//光の当たらない部分の反射係数
		m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//光の当たる部分の反射係数

		// ライトカメラのビュー行列を作成
		D3DXVECTOR3 Eye = D3DXVECTOR3(-10.0f, 10.0f, -10.0f);
		D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&m_Light.ViewMatrix, &Eye,
			&At, &Up);

		// ライトカメラのプロジェクション行列を作成
		D3DXMatrixPerspectiveFovLH(&m_Light.ProjectionMatrix, 1.0f,
			(float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 30.0f);
	}

	static LIGHT GetLight()
	{
		return m_Light;
	}

	static void SetLightPosition(D3DXVECTOR4 Pos)
	{
		m_Light.Position = Pos;
	}
	static void SetLightDirection(D3DXVECTOR4 Dir)
	{
		m_Light.Direction = Dir;
	}

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetCameraPosition(D3DXVECTOR3 CameraPosition);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetRenderMode();
	static void SetParameter(D3DXVECTOR4 Parameter);
	static void SetPlayerColor(D3DXVECTOR4 PlayerColor);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }

	static ID3D11ShaderResourceView* GetShadowDepthTexture()
	{
		return m_ShadowDepthShaderResourceView;
	}
	static void BeginDepth()
	{
		// シャドウバッファ深度バッファに設定し、内容を１で塗りつぶしておく
		m_DeviceContext->OMSetRenderTargets(0, NULL, m_ShadowDepthStencilView);
		m_DeviceContext->ClearDepthStencilView(m_ShadowDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);


};
