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

		// ������ ���������ο� �����ϴ�  ��ü�� ����
		ID3D11VertexShader* m_pVertexShader = nullptr;	// ���� ���̴�.
		ID3D11PixelShader* m_pPixelShader = nullptr;	// �ȼ� ���̴�.
		ID3D11InputLayout* m_pInputLayout = nullptr;	// �Է� ���̾ƿ�.
		ID3D11Buffer* m_pVertexBuffer = nullptr;		// ���ؽ� ����.
		UINT m_VertexBufferStride = 0;					// ���ؽ� �ϳ��� ũ��.
		UINT m_VertexBufferOffset = 0;					// ���ؽ� ������ ������.
		ID3D11Buffer* m_pIndexBuffer = nullptr;			// ���ؽ� ����.
		int m_nIndices = 0;								// �ε��� ����.
	};
}
