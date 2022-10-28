#include "pch.h"
#include "AssetsReader.h"

AssetsReader::AssetsReader()
{
}

AssetsReader::~AssetsReader()
{
}


auto AssetsReader::ReadAssets(fs::path path)
{
	std::ifstream stream;

	path /= ".lasset"
	// 파일을 엽니다.
	stream.open();

}
