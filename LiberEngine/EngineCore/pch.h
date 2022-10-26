#pragma once
#define USE 1
#define USE_CONSOLE USE


// 디버그 콘솔 사용
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
// 렌더링할 그래픽스 라이브러리 처리
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
// 표준라이브러리 헤더가 정의되어있습니다.
#include "../EngineUtil/EngineLib.h"
#include "../EngineUtil/EngineException.h"
#include "../EngineUtil/EngineLogger.h"

// 엔진 throw 검사용 매크로
#define CheckEngine(func) \


