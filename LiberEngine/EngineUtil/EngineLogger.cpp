#include "pch.h"
#include "EngineLogger.h"



void EngineLogger::Log(LogType type, std::string_view msg)
{
	// -TODO-
	// �ܼ���»Ӹ��ƴ϶� log.txt ���·� ����
	// �ؽ�Ʈ���Ŀ� ��¥, �ٹ�ȣ, �Լ��̸�, ��� ��.. ������ ��ȹ
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