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

std::pair<FileType, std::shared_ptr<LAsset>> AssetsReader::ReadAssets(fs::path path)
{
    // path 뒤에 암것도 없다면 디렉토리
    // 아니면 어떠한 파일형식이다.
    std::string pathStr = path.string();

    // "\" 다짤라버리면 만약 디렉토리라면 "." 기호가 없을꺼임
    pathStr = pathStr.substr(pathStr.find_last_of("\\") + 1);

    auto typeStartIndex = pathStr.find_first_of(".");

    // . 기호가 없다면 이 친구는 디렉토리파일
    if (typeStartIndex == std::string::npos)
    {

        LB_LOG(Log, std::format("Find directory path:{0}", pathStr));
        return std::pair<FileType, std::shared_ptr<LAsset>>(FileType::Directory, nullptr);
    }

    // 확장자 검사
    std::string extentionStr = pathStr.substr(pathStr.find(".") + 1);

    // 만약 '.' 기호가 있다면 예외 드랍
    if (extentionStr.find_last_of(".") != std::string::npos) 
    {
        LB_LOG(Warning, std::format("Do not include '.' in the filename.\nfilename is {0}", pathStr));
        return std::pair<FileType, std::shared_ptr<LAsset>>(FileType::Unknown, nullptr);
    }

    // 해당하는 파일의 .lasset가 있는지 확인 없다면 만들어야함
    auto lassetPath = path.string();
    lassetPath = lassetPath.substr(0, lassetPath.size() - extentionStr.size() - 1);
    lassetPath += ".lasset";
    LB_LOG(Log, lassetPath);



    return std::pair<FileType, std::shared_ptr<LAsset>>();
}

bool AssetsReader::HasLAsset(fs::path path)
{
    path += ".lasset";
    return fs::exists(path);
}

std::optional<std::string> AssetsReader::GetAssetExtension(fs::path path)
{
    return std::optional<std::string>();
}

std::optional<std::string> GetAssetExtension(fs::path path)
{
    // 디렉토리인지 체크
    if (fs::is_directory(path)) return std::nullopt;

    std::string pathStr = path.string();

    // 경로 자르기
    pathStr = pathStr.substr(pathStr.find_last_of("\\") + 1);

    // 확장자 뽑기
    std::string extentionStr = pathStr.substr(pathStr.find_last_of(".") + 1);

    return extentionStr;

}


