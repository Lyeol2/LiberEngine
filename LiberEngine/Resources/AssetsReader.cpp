#include "pch.h"
#include "Model.h"
#include "ResourceManager.h"
#include "AssetsReader.h"

AssetsReader::AssetsReader()
{
}

AssetsReader::~AssetsReader()
{
}

std::pair<ResourceType, LAsset> AssetsReader::ReadAssets(fs::path path)
{
    // path �ڿ� �ϰ͵� ���ٸ� ���丮
    // �ƴϸ� ��� ���������̴�.

    
    std::string pathStr = path.string();

    // .���� �߶��µ� "\" �� ���Ҵٸ� ��ųʸ���
    pathStr = pathStr.substr(pathStr.find_last_of(".") + 1);
    
    LB_LOG(Log, pathStr);

    return std::pair<ResourceType, LAsset>();
}


