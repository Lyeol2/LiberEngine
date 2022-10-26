#pragma once

/* DX11�� ����Ͽ� �������ϴ� Ŭ���� */
class DX11RENDERER_API DX11Renderer
{
public:
	/* -THINKING-
		������ ȣ���� ���ܸ� throw ��Ű�� �Ҹ��ڰ� ȣ����� �ʾ�
		�޸� ������ �Ͼ �� �ִ�. (����Ʈ�����ʹ� ���ܴ�)
		Initialize �Լ� ���ο� new�� �����Ҵ��� ��ü�� ������
		�����ڿ��� �ʱ�ȭ�� �׸��ε��� �Ѵ�.
	*/
	DX11Renderer() noexcept;
	virtual ~DX11Renderer() noexcept;

	/*
	*  �������� �⺻���� ���·� ����ϴ�.
	*  | Parameter :
	*  - HINSTANCE	hInstance	: ���α׷� �ڵ鷯
	*  - HWND		hWnd		: �������� ������ �ڵ鷯
	*  - float		width		: ������ ���α���
	*  - float		height		: ������ ���α���
	*/
	void Initialize(HINSTANCE hInstance, HWND hWnd, float screenWidth, float screenHeight);


	// BeginRender	: ȭ���� ���
	// Render		: ȭ���� �غ� 
	// EndRender	: ȭ���� ���
	void BeginRender();
	void Render();
	void EndRender();

private:
	/* Dx11 ����̽��� �����մϴ�. */
	void CreateDeviceAndSwapChain();

	/* RenderTargetView�� ����ϴ� */
	void CreateRenderTargetView();

	/* DepthStancilBuffer�� ����ϴ�. */
	void CreateDepthStancilBuffer();

	/* RasterizerState�� ����ϴ�. */
	void CreateRasterizerState();

	/* 
	*  RenderTargerView(RTV) �� DepthStancilView(DSV)�� ����ϴ�.
	*  | Parameter :
	*  - float color : ������� ������ �����մϴ� (USE) DirectX::Colors
	*/
	void ClearRTVAndDSV(const float* color);

	/* ����ü���� Ȱ���� ���۸� �����մϴ�*/
	void SwapRenderBuffer();


private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	float m_screenWidth;
	float m_screenHeight;

	int m_videoCardMemory;
	wstring m_videoCardDescription;

	// ��������ȭ ����
	bool m_vsyncEnabled;

	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	ComPtr<ID3D11DepthStencilView>	m_depthStencilView;
	ComPtr<ID3D11RasterizerState> m_rasterState;


};