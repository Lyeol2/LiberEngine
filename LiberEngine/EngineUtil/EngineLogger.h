#pragma once

#ifdef _DEBUG
#define LB_LOG(type, msg) EngineLogger::Log(LogType::type, msg)
#else
#define LB_LOG(...)
#endif


enum class LogType
{
	Log,
	Warning,
	Error,
};
/*
	���� �α׸� ����ϴ�. 
	�α״� �����忡 �����ؾ��մϴ�.
*/
class EngineLogger final
{
public:
	/*
	 *	�α׸� ����մϴ�.
	 *  | Parameter :
	 *  - (enum)LogType		type	: ���� Ÿ��
	 *  - string_view		msg		: �α� �޼���
	 */
	static void Log(LogType type, const std::string& msg);
	static void Log(LogType type, std::string&& msg);
};


