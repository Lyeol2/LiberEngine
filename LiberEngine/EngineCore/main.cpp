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

	// windows Ŭ������ �Ʒ��� ���� �����մϴ�.
	WNDCLASSEX wc = { 0, };

	// ������ Ŭ������ ��Ÿ���� �����Ѵ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// ������ ���ν����� �Լ����� �����Ѵ�
	wc.lpfnWndProc = WndProc;
	// �������� ���� �޸𸮷� (�ǵ��� X)
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	// �ν��Ͻ� �ڵ��� �����մϴ�
	wc.hInstance = hInstance;
	// ������ �ڵ�
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	// 16*16�� ���� �������ڵ�
	wc.hIconSm = wc.hIcon;
	// Ŀ�� �ڵ��� �����մϴ�.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// �⺻ �������� �����մϴ�.
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// �޴� ���ҽ�
	wc.lpszMenuName = NULL;
	// ������â Ŭ���� �� ���� �����Ͽ� �����츦 �����մϴ�.
	wc.lpszClassName = windowName;
	// ������ Ŭ���� ����ü�� ũ�⸦ �����Ѵ�
	wc.cbSize = sizeof(WNDCLASSEX);

	// windows class �� ����մϴ�.
	RegisterClassEx(&wc);


	int posX = 0;
	int posY = 0;

	// ������� �ػ󵵸� �о�ɴϴ�.
	float screenWidth = 1280.0f; //GetSystemMetrics(SM_CXSCREEN);
	float screenHeight = 720.0f; //GetSystemMetrics(SM_CYSCREEN);

	if (false)
	{
		// Ǯ��ũ�� ���� �����ߴٸ� ����� ȭ�� �ػ󵵸� ����ũ�� �ػ󵵷� �����ϰ� ������ 32bit�� �����մϴ�.
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

		// ������ â�� ����, ������ �� ��� ������ �մϴ�.
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
		// DX12ó��
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

	// �޼��� ����ü ���� �� �ʱ�ȭ
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	msg.message = WM_NULL;
	while (true)
	{
		// ������ �޼����� ó���մϴ�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ���� �޼����� ���� ��� �޽��� ������ Ż�� �մϴ�.
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
