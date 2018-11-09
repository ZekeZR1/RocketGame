#pragma once
namespace ZekeEngine {
	class CGraphicsEngine : Noncopyable
	{
	public:
		CGraphicsEngine();
		~CGraphicsEngine();
		bool InitDirectX(HWND hwnd);
		void Release();
		void BeginRender();
		void EndRender();

		ID3D11Device* GetD3DDevice() {
			return m_pd3dDevice;
		}

		ID3D11DeviceContext* GetD3DDeviceContext()
		{
			return m_pd3dDeviceContext;
		}

		ID3D11RenderTargetView* GetTarget() {
			return m_backBuffer;
		}

		ID3D11DepthStencilView* GetDepthStencilView() {
			return m_depthStencilView;
		}

		Camera& GetMainCamera()
		{
			return m_mainCamera;
		}
		Camera& Get2DCamera()
		{
			return m_2dCamera;
		}

	private:
		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		ID3D11Device * m_pd3dDevice = nullptr;
		ID3D11DeviceContext* m_pd3dDeviceContext = nullptr;
		IDXGISwapChain* m_pSwapChain = nullptr;
		D3D_FEATURE_LEVEL m_featureLevel;
		ID3D11RenderTargetView* m_backBuffer = nullptr;
		ID3D11RasterizerState* m_rasterizerState = nullptr;
		ID3D11Texture2D* m_depthStencil = nullptr;
		ID3D11DepthStencilView* m_depthStencilView = nullptr;
		Camera	m_mainCamera;		//3d camera
		Camera	m_2dCamera;			
		const int				m_2dSpaceScreenWidth = 1280;		
		const int				m_2dSpaceScreenHeight = 720;
		int						m_frameBufferWidth = 0;
		int						m_frameBufferHeight = 0;
	};
}