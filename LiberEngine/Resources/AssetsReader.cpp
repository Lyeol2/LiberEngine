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
	// ������ ���ϴ�.
	stream.open();

}
