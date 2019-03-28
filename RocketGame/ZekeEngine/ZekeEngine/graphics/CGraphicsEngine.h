#pragma once
#include "SkinModelDataManager.h"
#include "Effect\CEffectEngine.h"
#include "font\CFONT.h"

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

		CShaderResource &GetShaderResources()
		{
			return m_shaderResources;
		}

		Camera& GetMainCamera()
		{
			return m_mainCamera;
		}
		Camera& Get2DCamera()
		{
			return m_2dCamera;
		}

		SkinModelDataManager& GetSkinModelDataManager() {
			return m_skinModelDataManager;
		}
		/*!
		*@brief	エフェクトエンジンの取得。
		*/
		CEffectEngine& GetEffectEngine()
		{
			return m_effectEngine;
		}


		DirectX::SpriteBatch* GetSpriteBatch() const
		{
			return m_spriteBatch.get();
		}
		DirectX::SpriteFont* GetSpriteFont(CFont::TextType type) const
		{
			return m_spriteFont.get();
		}
		int GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		int GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		int Get2DSpaceScreenWidth() const
		{
			return m_2dSpaceScreenWidth;
		}
		int Get2DSpaceScreenHeight() const
		{
			return m_2dSpaceScreenHeight;
		}

		void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
		void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

		void SetAmbientLight(float amb) {
			m_ambientLight = amb;
		}

		const float GetAmbientLight() {
			return m_ambientLight;
		}

	private:
		CShaderResource m_shaderResources;
		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		ID3D11Device * m_pd3dDevice = nullptr;
		ID3D11DeviceContext* m_pd3dDeviceContext = nullptr;
		IDXGISwapChain* m_pSwapChain = nullptr;
		D3D_FEATURE_LEVEL m_featureLevel;
		ID3D11RenderTargetView* m_backBuffer = nullptr;
		ID3D11RasterizerState* m_rasterizerState = nullptr;
		ID3D11Texture2D* m_depthStencil = nullptr;
		ID3D11DepthStencilView* m_depthStencilView = nullptr;
		SkinModelDataManager m_skinModelDataManager;
		std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
		std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;
		CEffectEngine m_effectEngine;
		Camera	m_mainCamera;		//3d camera
		Camera	m_2dCamera;			
		const int				m_2dSpaceScreenWidth = 1280;		
		const int				m_2dSpaceScreenHeight = 720;
		int						m_frameBufferWidth = 0;
		int						m_frameBufferHeight = 0;
		float						m_ambientLight = 0.5f;
	};
}