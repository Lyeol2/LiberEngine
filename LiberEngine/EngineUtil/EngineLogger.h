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
	엔진 로그를 찍습니다. 
	로그는 스레드에 안전해야합니다.
*/
class EngineLogger final
{
public:
	/*
	 *	로그를 출력합니다.
	 *  | Parameter :
	 *  - (enum)LogType		type	: 오류 타입
	 *  - string_view		msg		: 로그 메세지
	 */
	static void Log(LogType type, const std::string& msg);
	static void Log(LogType type, std::string&& msg);
};


