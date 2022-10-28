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
    // path 뒤에 암것도 없다면 디렉토리
    // 아니면 어떠한 파일형식이다.

    
    std::string pathStr = path.string();

    // .까지 잘랏는데 "\" 가 남았다면 딕셔너리임
    pathStr = pathStr.substr(pathStr.find_last_of(".") + 1);
    
    LB_LOG(Log, pathStr);

    return std::pair<ResourceType, LAsset>();
}


