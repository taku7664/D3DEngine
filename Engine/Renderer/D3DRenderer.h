#pragma once
#include "IRenderer.h"

class WindowInfo;
class Engine::WindowContext;

using namespace DirectX;

namespace Renderer
{
	class D3DRenderer
		: public IRenderer
	{
	public:
		virtual bool Initialize(Engine::WindowContext* _window) override;
		virtual void Release() override;

		virtual void Clear() override;
		virtual void Clear(ColorF _color) override;
		virtual void BeginRender() override;
		virtual void EndRender() override;

		// temp
		void InitScene();
		void Draw();
	private:
		ID3D11Texture2D* m_backBufferTexture;
		ColorF m_clearColor;

		ID3D11Device* m_device;						
		ID3D11DeviceContext* m_deviceContext;
		IDXGISwapChain* m_swapChain;					
		ID3D11RenderTargetView* m_renderTargetView;

		D3D11_VIEWPORT m_viewport;

		// 렌더링 파이프라인에 적용하는  객체와 정보
		ID3D11VertexShader* m_pVertexShader = nullptr;	// 정점 셰이더.
		ID3D11PixelShader* m_pPixelShader = nullptr;	// 픽셀 셰이더.
		ID3D11InputLayout* m_pInputLayout = nullptr;	// 입력 레이아웃.
		ID3D11Buffer* m_pVertexBuffer = nullptr;		// 버텍스 버퍼.
		UINT m_VertexBufferStride = 0;					// 버텍스 하나의 크기.
		UINT m_VertexBufferOffset = 0;					// 버텍스 버퍼의 오프셋.
		ID3D11Buffer* m_pIndexBuffer = nullptr;			// 버텍스 버퍼.
		int m_nIndices = 0;								// 인덱스 개수.
	};
}
