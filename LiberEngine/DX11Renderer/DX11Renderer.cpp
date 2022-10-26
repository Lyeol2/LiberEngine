#include "pch.h"
#include "DX11Renderer.h"




DX11Renderer::DX11Renderer() noexcept
{
}

DX11Renderer::~DX11Renderer() noexcept
{
}

void DX11Renderer::Initialize(HINSTANCE hInstance, HWND hWnd, float screenWidth, float screenHeight)
{

	m_hInstance = hInstance;
	m_hWnd = hWnd;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	CreateDepthStancilBuffer();
	CreateRasterizerState();

}

void DX11Renderer::BeginRender()
{
	ClearRTVAndDSV(Colors::LightGray);
}

void DX11Renderer::Render()
{

}

void DX11Renderer::EndRender()
{
	// 렌더링이 완료되었으므로 화면에 백 버퍼를 표시합니다.
	// 수직동기화가 활성화 되어있을경우 활용합니다.
	SwapRenderBuffer();
}

void DX11Renderer::CreateDeviceAndSwapChain()
{
	// DX함수의 결과를 받을 변수
	HRESULT hResult;

	// CreateDXGIFactry factory객체를 얻는 함수
	ComPtr<IDXGIFactory> factory;
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
	ThrowIfFailed(hResult, "Couldn't create DXGIFactory");

	// 팩토리 객체를 사용하여 첫번째 그래픽 카드 인터페이스 어뎁터를 생성합니다.
	// 0번 그래픽카드
	ComPtr<IDXGIAdapter> adapter;
	hResult = factory->EnumAdapters(0, adapter.GetAddressOf());
	ThrowIfFailed(hResult, "Couldn't create Adapter");

	// 출력 (모니터)에 대한 첫번째 어뎁터를 지정합니다.
	// 0번 모니터
	ComPtr<IDXGIOutput> adapterOutput;
	hResult = adapter->EnumOutputs(0, adapterOutput.GetAddressOf());
	ThrowIfFailed(hResult, "Couldn't create adapterOutput");

	// 출력 (모니터)에 대한 DXGI_FORMAT_R8G8B8A8_UNORM 표시 형식에 맞는 모드 수를 가져옵니다
	UINT numModes = 0;
	hResult = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&numModes, NULL);
	ThrowIfFailed(hResult, "Couldn't get ModeCount");

	// 가능한 모든 모니터와 조합을 저장할 리스트를 생성합니다.
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	hResult = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&numModes, displayModeList);
	ThrowIfFailed(hResult, "Couldn't get Display Mode List");

	// 이제 모든 디스플레이 모드에 대해 화면 너비/높이 에 맞는 디스플레이 모드를 찾습니다
	// 적합한 것을 찾으면 모니터의 새로고침 비율의 분모와 분자값을 저장합니다.
	UINT numerator = 0;
	UINT denominator = 0;

	// 모니터의 해상도를 읽어옵니다.
	UINT monitorWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT monitorHeight = GetSystemMetrics(SM_CYSCREEN);

	for (UINT i = 0; i < numModes; ++i)
	{
		if (displayModeList[i].Width == monitorWidth)
		{
			if (displayModeList[i].Height == monitorHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// 비디오 카드의 구조체를 얻습니다.
	DXGI_ADAPTER_DESC adapterDesc;
	ThrowIfFailed(adapter->GetDesc(&adapterDesc), "Couldn't get vidiocard desc");
	// 비디오카드 메모리 용량 단위를 메가바이트 단위로 저장합니다.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	// 비디오카드의 이름을 저장합니다.
	m_videoCardDescription = adapterDesc.Description;

	delete[] displayModeList;
	displayModeList = nullptr;

	// 피처레벨을 DirectX 11 로 설정합니다.
	// DirectX의 기능수준을 정함 우리는 11을 사용한다.
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	

	// 스왑체인 구조체를 초기화합니다.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// 백버퍼를 1개만 사용하도록 지정합니다 (더블버퍼)
	swapChainDesc.BufferCount = 1;

	// 백버퍼의 넓이와 높이를 지정합니다.
	swapChainDesc.BufferDesc.Width = static_cast<UINT>(m_screenWidth);
	swapChainDesc.BufferDesc.Height = static_cast<UINT>(m_screenHeight);

	// 32bit 서페이스를 설정합니다.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 백버퍼의 새로고침 비율을 설정합니다 '수직동기화'
	if (m_vsyncEnabled)
	{
		// 갱신 주기, 프레임의 분모
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		// 갱신 주기, 프레임의 분자
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// 백버퍼의 사용용도를 지정합니다 ( 더블버퍼 )
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 렌더링에 사용될 윈도우 핸들을 지정합니다.
	swapChainDesc.OutputWindow = m_hWnd;

	// 멀티샘플링을 끕니다.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.Windowed = true;

	// ( 따로 스캔라인 순서가 정해지지 않는다. )
	// 스캔 라인 순서 및 크기를 지정하지 않음으로 설정합니다.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 출력된 다음 백버퍼를 비우도록 지정합니다
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// 추가옵션 플래그를 사용하지 않습니다.
	swapChainDesc.Flags = 0;

	// 위 기능수준을 사용해 스왑 체인, Direct3D 장치 및 Direct3D 장치 컨텍스트를 만듭니다.
	hResult = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, m_swapChain.GetAddressOf(), m_device.GetAddressOf(), NULL, m_deviceContext.GetAddressOf());

	ThrowIfFailed(hResult, "Couldn't Create D3D11Device and SwapChain");
}

void DX11Renderer::CreateRenderTargetView()
{
	// 스왑체인으로부터 백버퍼 포인터를 얻어옵니다.
	ComPtr<ID3D11Texture2D> backBufferPtr;

	CheckNullptr(m_swapChain);
	HRESULT hResult = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backBufferPtr.GetAddressOf());

	ThrowIfFailed(hResult, "Couldn't Get backBufferPtr");

	CheckNullptr(m_device);
	// 백 버퍼 포인터로 렌더 타겟 뷰를 생성한다.
	m_device->CreateRenderTargetView(backBufferPtr.Get(), NULL, m_renderTargetView.GetAddressOf());
}

void DX11Renderer::CreateDepthStancilBuffer()
{
}

void DX11Renderer::CreateRasterizerState()
{
	// 그려지는 폴리곤과 방법을 결정할 래스터 구조체를 설정합니다.
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// 방금 작성한 구조체에서 래스터 라이저 상태를 만듭니다.
	// 레스터 라이저가 하는일
	// 1. Clipping 경계면 밖으로 일부분이 삐져나오거나 아예 밖에 존재하는 물체들을 삭제하는 작업
	//		새로운 정점을 추가해서 새로운 도형을 만든다.
	// 2. Prespective division (원근 나눗셈) 원근법을 구현하는 단계이다. (투영행렬식)
	//		( 행렬에 대해서 좀더 알아본뒤 공부해보자 )
	// 3. Back-face culling 우리가 실제 사물을 보는 것 처럼 뒷면쪽을 display에 올리지 않거나
	//		반투명의 재질의 경우 앞, 뒷면을 살짝 보이게 하는등의 처리를 하는 단계이다.
	// 4. Viewport Transform 삼각형 메쉬들을 스크린 공간으로 옮기는 변환이다.
	// 5. Scan conversion  삼각형 내부 프래그먼트를 생성할 것이다
	CheckNullptr(m_device);
	m_device->CreateRasterizerState(&rasterDesc, m_rasterState.GetAddressOf());

	CheckNullptr(m_deviceContext);
	// 래스터 라이저 상태를 설정합니다
	m_deviceContext->RSSetState(m_rasterState.Get());
}

void DX11Renderer::ClearRTVAndDSV(const float* color)
{
	CheckNullptr(m_deviceContext);
	// 백버퍼를 지웁니다
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color);

	// 깊이 버퍼를 지웁니다
	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11Renderer::SwapRenderBuffer()
{
	CheckNullptr(m_swapChain);
	if (m_vsyncEnabled)
	{
		m_swapChain->Present(1, 0);
	}
	else
	{
		// 가능한 빠르게 출력합니다
		m_swapChain->Present(0, 0);
	}
}