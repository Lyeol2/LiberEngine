#pragma once

/* 메타파일을 읽거나 생성합니다. */
class AssetsReader
{
public:
	AssetsReader();
	virtual ~AssetsReader();

private:
	auto ReadAssets(fs::path path);

};