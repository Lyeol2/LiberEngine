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

std::pair<FileType, LAsset> AssetsReader::ReadAssets(fs::path path)
{
    // path 뒤에 암것도 없다면 디렉토리
    // 아니면 어떠한 파일형식이다.
    std::string pathStr = path.string();

    // "\" 다짤라버리면 만약 딕렉토리라면 "." 기호가 없을꺼임
    pathStr = pathStr.substr(pathStr.find_last_of("\\") + 1);

    auto typeStartIndex = pathStr.find_first_of(".");

    // . 기호가 없다면 이 친구는 디렉토리파일
    if (typeStartIndex == std::string::npos)
    {

        LB_LOG(Log, std::format("Find directory path:{0}", pathStr));
        return std::pair<FileType, LAsset>(FileType::Directory, LAsset());
    }

    // 확장자 검사
    std::string extentionStr = pathStr.substr(pathStr.find(".") + 1);

    // 만약 '.' 기호가 있다면 예외 드랍
    if (extentionStr.find_last_of(".") != std::string::npos)
        throw EngineException(std::format("Do not include '.' in the filename.\nfilename is {0}", pathStr),
            __LINE__, __FUNCTION__, __FILE__);


    return std::pair<FileType, LAsset>();
}


