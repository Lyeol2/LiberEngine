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
	// �������� �Ϸ�Ǿ����Ƿ� ȭ�鿡 �� ���۸� ǥ���մϴ�.
	// ��������ȭ�� Ȱ��ȭ �Ǿ�������� Ȱ���մϴ�.
	SwapRenderBuffer();
}

void DX11Renderer::CreateDeviceAndSwapChain()
{
	// DX�Լ��� ����� ���� ����
	HRESULT hResult;

	// CreateDXGIFactry factory��ü�� ��� �Լ�
	ComPtr<IDXGIFactory> factory;
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
	ThrowIfFailed(hResult, "Couldn't create DXGIFactory");

	// ���丮 ��ü�� ����Ͽ� ù��° �׷��� ī�� �������̽� ��͸� �����մϴ�.
	// 0�� �׷���ī��
	ComPtr<IDXGIAdapter> adapter;
	hResult = factory->EnumAdapters(0, adapter.GetAddressOf());
	ThrowIfFailed(hResult, "Couldn't create Adapter");

	// ��� (�����)�� ���� ù��° ��͸� �����մϴ�.
	// 0�� �����
	ComPtr<IDXGIOutput> adapterOutput;
	hResult = adapter->EnumOutputs(0, adapterOutput.GetAddressOf());
	ThrowIfFailed(hResult, "Couldn't create adapterOutput");

	// ��� (�����)�� ���� DXGI_FORMAT_R8G8B8A8_UNORM ǥ�� ���Ŀ� �´� ��� ���� �����ɴϴ�
	UINT numModes = 0;
	hResult = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&numModes, NULL);
	ThrowIfFailed(hResult, "Couldn't get ModeCount");

	// ������ ��� ����Ϳ� ������ ������ ����Ʈ�� �����մϴ�.
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	hResult = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&numModes, displayModeList);
	ThrowIfFailed(hResult, "Couldn't get Display Mode List");

	// ���� ��� ���÷��� ��忡 ���� ȭ�� �ʺ�/���� �� �´� ���÷��� ��带 ã���ϴ�
	// ������ ���� ã���� ������� ���ΰ�ħ ������ �и�� ���ڰ��� �����մϴ�.
	UINT numerator = 0;
	UINT denominator = 0;

	// ������� �ػ󵵸� �о�ɴϴ�.
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

	// ���� ī���� ����ü�� ����ϴ�.
	DXGI_ADAPTER_DESC adapterDesc;
	ThrowIfFailed(adapter->GetDesc(&adapterDesc), "Couldn't get vidiocard desc");
	// ����ī�� �޸� �뷮 ������ �ް�����Ʈ ������ �����մϴ�.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	// ����ī���� �̸��� �����մϴ�.
	m_videoCardDescription = adapterDesc.Description;

	delete[] displayModeList;
	displayModeList = nullptr;

	// ��ó������ DirectX 11 �� �����մϴ�.
	// DirectX�� ��ɼ����� ���� �츮�� 11�� ����Ѵ�.
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	

	// ����ü�� ����ü�� �ʱ�ȭ�մϴ�.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// ����۸� 1���� ����ϵ��� �����մϴ� (�������)
	swapChainDesc.BufferCount = 1;

	// ������� ���̿� ���̸� �����մϴ�.
	swapChainDesc.BufferDesc.Width = static_cast<UINT>(m_screenWidth);
	swapChainDesc.BufferDesc.Height = static_cast<UINT>(m_screenHeight);

	// 32bit �����̽��� �����մϴ�.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ������� ���ΰ�ħ ������ �����մϴ� '��������ȭ'
	if (m_vsyncEnabled)
	{
		// ���� �ֱ�, �������� �и�
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		// ���� �ֱ�, �������� ����
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// ������� ���뵵�� �����մϴ� ( ������� )
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// �������� ���� ������ �ڵ��� �����մϴ�.
	swapChainDesc.OutputWindow = m_hWnd;

	// ��Ƽ���ø��� ���ϴ�.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.Windowed = true;

	// ( ���� ��ĵ���� ������ �������� �ʴ´�. )
	// ��ĵ ���� ���� �� ũ�⸦ �������� �������� �����մϴ�.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ��µ� ���� ����۸� ��쵵�� �����մϴ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// �߰��ɼ� �÷��׸� ������� �ʽ��ϴ�.
	swapChainDesc.Flags = 0;

	// �� ��ɼ����� ����� ���� ü��, Direct3D ��ġ �� Direct3D ��ġ ���ؽ�Ʈ�� ����ϴ�.
	hResult = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, m_swapChain.GetAddressOf(), m_device.GetAddressOf(), NULL, m_deviceContext.GetAddressOf());

	ThrowIfFailed(hResult, "Couldn't Create D3D11Device and SwapChain");
}

void DX11Renderer::CreateRenderTargetView()
{
	// ����ü�����κ��� ����� �����͸� ���ɴϴ�.
	ComPtr<ID3D11Texture2D> backBufferPtr;

	CheckNullptr(m_swapChain);
	HRESULT hResult = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backBufferPtr.GetAddressOf());

	ThrowIfFailed(hResult, "Couldn't Get backBufferPtr");

	CheckNullptr(m_device);
	// �� ���� �����ͷ� ���� Ÿ�� �並 �����Ѵ�.
	m_device->CreateRenderTargetView(backBufferPtr.Get(), NULL, m_renderTargetView.GetAddressOf());
}

void DX11Renderer::CreateDepthStancilBuffer()
{
}

void DX11Renderer::CreateRasterizerState()
{
	// �׷����� ������� ����� ������ ������ ����ü�� �����մϴ�.
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

	// ��� �ۼ��� ����ü���� ������ ������ ���¸� ����ϴ�.
	// ������ �������� �ϴ���
	// 1. Clipping ���� ������ �Ϻκ��� ���������ų� �ƿ� �ۿ� �����ϴ� ��ü���� �����ϴ� �۾�
	//		���ο� ������ �߰��ؼ� ���ο� ������ �����.
	// 2. Prespective division (���� ������) ���ٹ��� �����ϴ� �ܰ��̴�. (������Ľ�)
	//		( ��Ŀ� ���ؼ� ���� �˾ƺ��� �����غ��� )
	// 3. Back-face culling �츮�� ���� �繰�� ���� �� ó�� �޸����� display�� �ø��� �ʰų�
	//		�������� ������ ��� ��, �޸��� ��¦ ���̰� �ϴµ��� ó���� �ϴ� �ܰ��̴�.
	// 4. Viewport Transform �ﰢ�� �޽����� ��ũ�� �������� �ű�� ��ȯ�̴�.
	// 5. Scan conversion  �ﰢ�� ���� �����׸�Ʈ�� ������ ���̴�
	CheckNullptr(m_device);
	m_device->CreateRasterizerState(&rasterDesc, m_rasterState.GetAddressOf());

	CheckNullptr(m_deviceContext);
	// ������ ������ ���¸� �����մϴ�
	m_deviceContext->RSSetState(m_rasterState.Get());
}

void DX11Renderer::ClearRTVAndDSV(const float* color)
{
	CheckNullptr(m_deviceContext);
	// ����۸� ����ϴ�
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color);

	// ���� ���۸� ����ϴ�
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
		// ������ ������ ����մϴ�
		m_swapChain->Present(0, 0);
	}
}