#pragma once
#define USE 1
#define USE_CONSOLE USE


// ����� �ܼ� ���
#if USE_CONSOLE == USE
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif


enum class Graphics
{
	NONE,
	GL,
	DX9,
	DX11,
	DX12,
	VK,
};
// �������� �׷��Ƚ� ���̺귯�� ó��
#define NONE 0
// OpenGL
#define GL 1
// DirectX
#define DX9 2
#define DX11 3
#define DX12 4
// VULKAN
#define VK 5

#define RENDERER DX11

#if RENDERER == DX12
#include "DX12Define.h"
#elif RENDERER == DX11
#include "DX11Define.h"
#endif 


// Resources
#pragma comment(lib, "Resources.lib")
#include "../Resources/pch.h"
#include "../Resources/ResourceManager.h"


// EngineUtil
#pragma comment(lib, "EngineUtil.lib")
// ǥ�ض��̺귯�� ����� ���ǵǾ��ֽ��ϴ�.
#include "../EngineUtil/EngineLib.h"
#include "../EngineUtil/EngineException.h"
#include "../EngineUtil/EngineLogger.h"

// ���� throw �˻�� ��ũ��
#define CheckEngine(func) \


