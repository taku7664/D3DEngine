#include "pch.h"
#include "D3DRenderer.h"
#include "Window/Window/WindowContext.h"

#define USE_FLIPMODE 0			//경고 메세지를 없애려면 Flip 모드를 사용한다.

// 정점 선언.
struct Vertex
{
	Vector3 position;		// 정점 위치 정보.
	Vector4 color;			// 정점 색상 정보.

	Vertex(float x, float y, float z) : position(x, y, z) { }
	Vertex(Vector3 position) : position(position) { }

	Vertex(Vector3 position, Vector4 color)
		: position(position), color(color) { }
};

HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

namespace Renderer
{
	bool D3DRenderer::Initialize(Engine::WindowContext* _window)
	{
		m_clearColor = ColorF(0.0f, 0.5f, 0.5f, 1.0f);

		HRESULT hr = 0;
		
		// 스왑체인 속성 설정 구조체 생성.
		DXGI_SWAP_CHAIN_DESC swapDesc = {};
		swapDesc.BufferCount = 1;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = *_window;	// 스왑체인 출력할 창 핸들 값.
		swapDesc.Windowed = true;		// 창 모드 여부 설정.
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		// 백버퍼(텍스처)의 가로/세로 크기 설정.
		swapDesc.BufferDesc.Width = static_cast<UINT>(_window->GetWindowSize().x);
		swapDesc.BufferDesc.Height = static_cast<UINT>(_window->GetWindowSize().y);
		// 화면 주사율 설정.
		swapDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapDesc.BufferDesc.RefreshRate.Denominator = 1;
		// 샘플링 관련 설정.
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0; 6;

		UINT creationFlags = 0;
#ifdef _DEBUG
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		// 1. 장치 생성.   2.스왑체인 생성. 3.장치 컨텍스트 생성.
		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, NULL,
			D3D11_SDK_VERSION, &swapDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);

		// 4. 렌더타겟뷰 생성.  (백버퍼를 이용하는 렌더타겟뷰)	
		ID3D11Texture2D* pBackBufferTexture = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture);
		m_device->CreateRenderTargetView(pBackBufferTexture, NULL, &m_renderTargetView);  // 텍스처는 내부 참조 증가
		SAFE_RELEASE(pBackBufferTexture);	//외부 참조 카운트를 감소시킨다.
		// 렌더 타겟을 최종 출력 파이프라인에 바인딩합니다.
		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);
#if USE_FLIPMODE==0
		// 렌더 타겟을 최종 출력 파이프라인에 바인딩합니다.
		// FlipMode가 아닐때는 최초 한번만 설정하면 된다.
		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);
#endif 
		// 뷰포트 설정.	
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = _window->GetWindowSize().x;
		m_viewport.Height = _window->GetWindowSize().y;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		// 뷰포트 설정.
		m_deviceContext->RSSetViewports(1, &m_viewport);
		InitScene();
		return true;
	}

	void D3DRenderer::Release()
	{
		SAFE_RELEASE(m_renderTargetView);
		SAFE_RELEASE(m_deviceContext);
		SAFE_RELEASE(m_swapChain);
		SAFE_RELEASE(m_device);

		delete this;
	}

	void D3DRenderer::Clear()
	{
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, m_clearColor);
	}

	void D3DRenderer::Clear(ColorF _color)
	{
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, _color);
	}

	void D3DRenderer::BeginRender()
	{
		// Draw계열 함수를 호출하기전에 렌더링 파이프라인에 필수 스테이지 설정을 해야한다.	
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 정점을 이어서 그릴 방식 설정.
		m_deviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_VertexBufferStride, &m_VertexBufferOffset);
		m_deviceContext->IASetInputLayout(m_pInputLayout);
		m_deviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		m_deviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
		m_deviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
	}
	void D3DRenderer::Draw()
	{
		m_deviceContext->DrawIndexed(m_nIndices, 0, 0);
	}
	void D3DRenderer::EndRender()
	{
		m_swapChain->Present(0, 0);
	}

	void D3DRenderer::InitScene()
	{
		HRESULT hr = 0; // 결과값.
		// 1. Render() 에서 파이프라인에 바인딩할 버텍스 버퍼및 버퍼 정보 준비
		// Normalized Device Coordinate
		//   0-----1
		//   |    /|
		//   |  /  |                중앙이 (0,0)  왼쪽이 (-1,0) 오른쪽이 (1,0) , 위쪽이 (0,1) 아래쪽이 (0,-1)
		//   |/    |
		//	 2-----3
		Vertex vertices[] =
		{
			Vertex(Vector3(-0.5f,  0.5f, 0.5f), Vector4(1.0f, 0.0f, 0.0f, 1.0f)),  // 
			Vertex(Vector3(0.5f,  0.5f, 0.5f), Vector4(0.0f, 1.0f, 0.0f, 1.0f)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f))
		};

		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.Usage = D3D11_USAGE_DEFAULT;
		D3D11_SUBRESOURCE_DATA vbData = {};
		vbData.pSysMem = vertices;	// 배열 데이터 할당.
		Utillity::HR_T(m_device->CreateBuffer(&vbDesc, &vbData, &m_pVertexBuffer));
		m_VertexBufferStride = sizeof(Vertex);		// 버텍스 버퍼 정보
		m_VertexBufferOffset = 0;

		// 2. Render() 에서 파이프라인에 바인딩할 InputLayout 생성 	
		D3D11_INPUT_ELEMENT_DESC layout[] = // 입력 레이아웃.
		{   // SemanticName , SemanticIndex , Format , InputSlot , AlignedByteOffset , InputSlotClass , InstanceDataStepRate	
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		ID3D10Blob* vertexShaderBuffer = nullptr;
		Utillity::HR_T(CompileShaderFromFile(L"BasicVertexShader.hlsl", "main", "vs_4_0", &vertexShaderBuffer));
		Utillity::HR_T(m_device->CreateInputLayout(layout, ARRAYSIZE(layout),
			vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_pInputLayout));

		// 3. Render() 에서 파이프라인에 바인딩할  버텍스 셰이더 생성
		Utillity::HR_T(m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader));
		SAFE_RELEASE(vertexShaderBuffer);	// 버퍼 해제.

		// 4. Render() 에서 파이프라인에 바인딩할 인덱스 버퍼 생성
		WORD indices[] =
		{
			0, 1, 2,
			2, 1, 3
		};
		m_nIndices = ARRAYSIZE(indices);	// 인덱스 개수 저장.
		D3D11_BUFFER_DESC ibDesc = {};
		ibDesc.ByteWidth = sizeof(WORD) * ARRAYSIZE(indices);
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.Usage = D3D11_USAGE_DEFAULT;
		D3D11_SUBRESOURCE_DATA ibData = {};
		ibData.pSysMem = indices;
		Utillity::HR_T(m_device->CreateBuffer(&ibDesc, &ibData, &m_pIndexBuffer));

		// 5. Render() 에서 파이프라인에 바인딩할 픽셀 셰이더 생성
		ID3D10Blob* pixelShaderBuffer = nullptr;
		Utillity::HR_T(CompileShaderFromFile(L"BasicPixelShader.hlsl", "main", "ps_4_0", &pixelShaderBuffer));
		Utillity::HR_T(m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
			pixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader));
		SAFE_RELEASE(pixelShaderBuffer);	// 픽셀 셰이더 버퍼 더이상 필요없음.
	}
}


HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			MessageBoxA(NULL, (char*)pErrorBlob->GetBufferPointer(), "CompileShaderFromFile", MB_OK);
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}