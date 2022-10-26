#pragma once
// C++ ǥ�ض��̺귯���� �����մϴ�.

// �ʼ� ���

#define WIN32_LEAN_AND_MEAN				// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <Windows.h>

#include <string>
#include <format>	// (C++20)
#include <iostream>
#include <string_view>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <vector>

namespace LiberEngine::Colors
{
	constexpr unsigned short BLACK			= 0 ;
	constexpr unsigned short BLUE			= 1 ;
	constexpr unsigned short GREEN			= 2 ;
	constexpr unsigned short CYAN			= 3 ;
	constexpr unsigned short RED			= 4 ;
	constexpr unsigned short MAGENTA		= 5 ;
	constexpr unsigned short BROWN			= 6 ;
	constexpr unsigned short LIGHTGRAY		= 7 ;
	constexpr unsigned short DARKGRAY		= 8 ;
	constexpr unsigned short LIGHTBLUE		= 9 ;
	constexpr unsigned short LIGHTGREEN		= 10; 
	constexpr unsigned short LIGHTCYAN		= 11; 
	constexpr unsigned short LIGHTRED		= 12; 
	constexpr unsigned short LIGHTMAGENTA	= 13; 
	constexpr unsigned short YELLOW			= 14; 
	constexpr unsigned short WHITE			= 15;
}