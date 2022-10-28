#pragma once

// -TODO- ������ ���̵幮�ڸ� �⺻���� ����ϱ� ������ ������ �ʿ�..

class EngineException : std::exception
{
public:
   /* 
	*  | Parameter :
	*  - const char*	mesaage	: �����޼���
	*  - unsigned int	line	: ������ ��Ÿ�� �� ��ȣ	ex) __LINE__
	*  - const char*	mesaage	: ������ ��Ÿ�� �Լ��̸�	ex) __FUNCTION__
	*  - const char*	mesaage	: ������ ��Ÿ�� ���� �̸�	ex) __FILE__
	*/
	EngineException(const char* message, unsigned int line = 0, const char* functionName = "", const char* fileName = "") noexcept;
	EngineException(std::string message, unsigned int line = 0, const char* functionName = "", const char* fileName = "") noexcept;

	/*
	*  std::excetpion�� what() �޼��带 �״�� �����մϴ�.
	*  ���߿� �߰��� ���� ������ ������.. 
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


// format, string �ʼ�
#define CheckNullptr(ptr) \
if (!ptr) throw EngineException(std::format("{0} is nullptr",#ptr), __LINE__, __FUNCTION__, __FILE__);