#pragma once

// -TODO- 엔진은 와이드문자를 기본으로 사용하기 때문에 수정이 필요..

class EngineException : std::exception
{
public:
   /* 
	*  | Parameter :
	*  - const char*	mesaage	: 오류메세지
	*  - unsigned int	line	: 오류가 나타난 줄 번호	ex) __LINE__
	*  - const char*	mesaage	: 오류가 나타난 함수이름	ex) __FUNCTION__
	*  - const char*	mesaage	: 오류가 나타난 파일 이름	ex) __FILE__
	*/
	EngineException(const char* message, unsigned int line = 0, const char* functionName = "", const char* fileName = "") noexcept;
	EngineException(std::string message, unsigned int line = 0, const char* functionName = "", const char* fileName = "") noexcept;

	/*
	*  std::excetpion의 what() 메서드를 그대로 구현합니다.
	*  나중에 추가할 일이 생기지 않을까.. 
	*/
	virtual const char* what() const noexcept override;

private:
	std::string m_lineNum;
	std::string m_functionName;
	std::string m_filename;

	std::string m_fullMessage;

public:
	inline std::string_view GetLineNum()		const noexcept	{ return m_lineNum;			}
	inline std::string_view GetFunctionName()	const noexcept	{ return m_functionName;	}
	inline std::string_view Getfilename()		const noexcept	{ return m_filename;		}
};

#define ThrowIfFailed(hr, msg) \
if (FAILED(hr)) { throw EngineException(msg, __LINE__, __FUNCTION__, __FILE__); }


// format, string 필수
#define CheckNullptr(ptr) \
if (!ptr) throw EngineException(std::format("{0} is nullptr",#ptr), __LINE__, __FUNCTION__, __FILE__);