#pragma once
// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

// 여기에 미리 컴파일하려는 헤더 추가

// EngineUtil
#pragma comment(lib, "EngineUtil.lib")
#include "../EngineUtil/EngineLib.h"
#include "../EngineUtil/EngineException.h"
#include "../EngineUtil/EngineLogger.h"
// D3D
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "d3dcompiler.lib")


// 다이렉트 인풋버전을 선언해줍니다
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <DirectXColors.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

using namespace DirectX;
using namespace std;

// 컴객체 사용을 위한 헤더와 네임스페이스
#include <wrl.h>
using namespace Microsoft::WRL;


// EXPORTS
#ifndef DX11RENDERER_EXPORTS
#define	DX11RENDERER_API	__declspec(dllimport)
#else
#define	DX11RENDERER_API	__declspec(dllexport)
#endif



// -WARNING- 
#pragma warning (disable : 4251)

