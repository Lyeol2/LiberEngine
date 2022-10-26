#pragma once

/* DX11를 사용하여 렌더링하는 클래스 */
class DX11RENDERER_API DX11Renderer
{
public:
	/* -THINKING-
		생성자 호출중 예외를 throw 시키면 소멸자가 호출되지 않아
		메모리 누수가 일어날 수 있다. (스마트포인터는 예외다)
		Initialize 함수 내부에 new로 동적할당한 객체가 있으니
		생성자에서 초기화는 그만두도록 한다.
	*/
	DX11Renderer() noexcept;
	virtual ~DX11Renderer() noexcept;

	/*
	*  렌더러를 기본설정 상태로 만듭니다.
	*  | Parameter :
	*  - HINSTANCE	hInstance	: 프로그램 핸들러
	*  - HWND		hWnd		: 렌더링할 윈도우 핸들러
	*  - float		width		: 윈도우 가로길이
	*  - float		height		: 윈도우 세로길이
	*/
	void Initialize(HINSTANCE hInstance, HWND hWnd, float screenWidth, float screenHeight);


	// BeginRender	: 화면을 비움
	// Render		: 화면을 준비 
	// EndRender	: 화면을 출력
	void BeginRender();
	void Render();
	void EndRender();

private:
	/* Dx11 디바이스를 생성합니다. */
	void CreateDeviceAndSwapChain();

	/* RenderTargetView를 만듭니다 */
	void CreateRenderTargetView();

	/* DepthStancilBuffer를 만듭니다. */
	void CreateDepthStancilBuffer();

	/* RasterizerState를 만듭니다. */
	void CreateRasterizerState();

	/* 
	*  RenderTargerView(RTV) 와 DepthStancilView(DSV)를 지웁니다.
	*  | Parameter :
	*  - float color : 어떤색으로 지울지 결정합니다 (USE) DirectX::Colors
	*/
	void ClearRTVAndDSV(const float* color);

	/* 스왑체인을 활용해 버퍼를 변경합니다*/
	void SwapRenderBuffer();


private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	float m_screenWidth;
	float m_screenHeight;

	int m_videoCardMemory;
	wstring m_videoCardDescription;

	// 수직동기화 여부
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