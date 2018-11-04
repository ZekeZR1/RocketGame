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
	private:
		ID3D11Device * m_pd3dDevice = nullptr;
		ID3D11DeviceContext* m_pd3dDeviceContext = nullptr;
		IDXGISwapChain* m_pSwapChain = nullptr;
		D3D_FEATURE_LEVEL m_featureLevel;
		ID3D11RenderTargetView* m_backBuffer = nullptr;
		ID3D11RasterizerState* m_rasterizerState = nullptr;
		ID3D11Texture2D* m_depthStencil = nullptr;
		ID3D11DepthStencilView* m_depthStencilView = nullptr;
	};
}