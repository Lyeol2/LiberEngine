#include "pch.h"
#include "EngineException.h"

EngineException::EngineException(const char* message, unsigned int line, const char* functionName, const char* fileName) noexcept : exception(message)
{
	m_lineNum = std::to_string(line);
	m_functionName = functionName;
	m_filename = fileName;

	// [C++20]  std::format
	m_fullMessage = format("Line:{0}\nPath:{1}\nFunction:{2}\n{3}", m_lineNum, m_filename, m_functionName, message);
}

EngineException::EngineException(std::string message, unsigned int line, const char* functionName, const char* fileName) noexcept : exception(message.c_str())
{
	m_lineNum = std::to_string(line);
	m_functionName = functionName;
	m_filename = fileName;
	m_fullMessage = format("Line:{0}\nPath:{1}\nFunction:{2}\n{3}", m_lineNum, m_filename, m_functionName, message);
}


const char* EngineException::what() const noexcept 
{
	return m_fullMessage.c_str();
}
	 