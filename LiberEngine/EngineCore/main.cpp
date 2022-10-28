#include "pch.h"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_QUIT:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	DefWindowProc(hWnd, iMessage, wParam, lParam);
}

#include <iostream>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{

#pragma region WINDOW_INIT

	LPCWSTR windowName = L"LiberEngine";

	// windows 클래스를 아래와 같이 설정합니다.
	WNDCLASSEX wc = { 0, };

	// 윈도우 클래스의 스타일을 지정한다
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 윈도우 프로시저의 함수명을 지정한다
	wc.lpfnWndProc = WndProc;
	// 윈도우의 여분 메모리량 (건들일 X)
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	// 인스턴스 핸들을 전달합니다
	wc.hInstance = hInstance;
	// 아이콘 핸들
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	// 16*16의 작은 아이콘핸들
	wc.hIconSm = wc.hIcon;
	// 커서 핸들을 전달합니다.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// 기본 배경색상을 지정합니다.
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// 메뉴 리소스
	wc.lpszMenuName = NULL;
	// 윈도우창 클래스 이 값을 참조하여 윈도우를 생성합니다.
	wc.lpszClassName = windowName;
	// 윈도우 클래스 구조체의 크기를 지정한다
	wc.cbSize = sizeof(WNDCLASSEX);

	// windows class 를 등록합니다.
	RegisterClassEx(&wc);


	int posX = 0;
	int posY = 0;

	// 모니터의 해상도를 읽어옵니다.
	float screenWidth = 1280.0f; //GetSystemMetrics(SM_CXSCREEN);
	float screenHeight = 720.0f; //GetSystemMetrics(SM_CYSCREEN);

	if (false)
	{
		// 풀스크린 모드로 지정했다면 모니터 화면 해상도를 데스크톱 해상도로 지정하고 색상을 32bit로 지정합니다.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PANNINGWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{

		// 윈도우 창을 가로, 세로의 정 가운데 오도록 합니다.
		posX = (int)((GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2);
		posY = (int)((GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2);
	}

	HWND hWnd = CreateWindowExW(
		NULL,
		windowName,
		windowName,
		WS_OVERLAPPEDWINDOW,
		posX, posY,
		(int)screenWidth, (int)screenHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	UpdateWindow(hWnd);

#pragma endregion
	
	auto renderer =
#if		RENDERER == DX12
		// DX12처리
#elif	RENDERER == DX11
		make_unique<DX11Renderer>()
#else
		nullptr
#endif
;

	auto resources = make_unique<ResourceManager>();

	try 
	{
		renderer->Initialize(hInstance, hWnd, screenWidth, screenHeight);
		resources->Initialize();
	}
	catch (const EngineException& ex) 
	{ 
		MessageBoxA(hWnd, ex.what(), "EngineException", MB_ICONERROR);
	}
	catch (const exception& ex) 
	{
		MessageBoxA(hWnd, ex.what(), "exception", MB_ICONERROR);
	}

	// 메세지 구조체 생성 및 초기화
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	msg.message = WM_NULL;
	while (true)
	{
		// 윈도우 메세지를 처리합니다
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// 종료 메세지를 받을 경우 메시지 루프를 탈출 합니다.
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			try
			{
				renderer->BeginRender();
				renderer->Render();
				renderer->EndRender();
			}
			catch (const EngineException& ex)
			{
				MessageBoxA(hWnd, ex.what(), "EngineException", 0);
			}
			catch (const exception& ex)
			{
				MessageBoxA(hWnd, ex.what(), "exception", 0);
			}
		}
	}
	return 0;
}
