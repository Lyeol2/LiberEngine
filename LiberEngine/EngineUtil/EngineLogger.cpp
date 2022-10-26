#include "pch.h"
#include "EngineLogger.h"



void EngineLogger::Log(LogType type, std::string_view msg)
{
	// -TODO-
	// 콘솔출력뿐만아니라 log.txt 형태로 저장
	// 텍스트형식에 날짜, 줄번호, 함수이름, 경로 등.. 포함할 계획
	switch (type)
	{
	case LogType::Log:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LiberEngine::Colors::WHITE);
		std::cout << std::format("[Log] {0}", msg) << std::endl;
		break;
	case LogType::Warning:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LiberEngine::Colors::YELLOW);
		std::cout << std::format("[Warning] {0}", msg) << std::endl;
		break;
	case LogType::Error:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LiberEngine::Colors::RED);
		std::cout << std::format("[Error] {0}", msg) << std::endl;
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_BRUSH);
}