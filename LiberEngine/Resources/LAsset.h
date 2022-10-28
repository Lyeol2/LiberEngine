#pragma once

/* 확장자 .LAsset 형식의 파일의 베이스 클래스 입니다. 
	게임에 필요한 리소스의 데이터를 담습니다.*/
class LAsset
{
public:
	LAsset();
	LAsset(fs::path path);
	virtual ~LAsset() noexcept;

private:
	GUID guid;

	std::string filename;
	fs::path filePath;


};