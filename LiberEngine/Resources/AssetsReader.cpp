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
    // path �ڿ� �ϰ͵� ���ٸ� ���丮
    // �ƴϸ� ��� ���������̴�.
    std::string pathStr = path.string();

    // "\" ��©������� ���� ���丮��� "." ��ȣ�� ��������
    pathStr = pathStr.substr(pathStr.find_last_of("\\") + 1);

    auto typeStartIndex = pathStr.find_first_of(".");

    // . ��ȣ�� ���ٸ� �� ģ���� ���丮����
    if (typeStartIndex == std::string::npos)
    {

        LB_LOG(Log, std::format("Find directory path:{0}", pathStr));
        return std::pair<FileType, std::shared_ptr<LAsset>>(FileType::Directory, nullptr);
    }

    // Ȯ���� �˻�
    std::string extentionStr = pathStr.substr(pathStr.find(".") + 1);

    // ���� '.' ��ȣ�� �ִٸ� ���� ���
    if (extentionStr.find_last_of(".") != std::string::npos) 
    {
        LB_LOG(Warning, std::format("Do not include '.' in the filename.\nfilename is {0}", pathStr));
        return std::pair<FileType, std::shared_ptr<LAsset>>(FileType::Unknown, nullptr);
    }

    // �ش��ϴ� ������ .lasset�� �ִ��� Ȯ�� ���ٸ� ��������
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
    // ���丮���� üũ
    if (fs::is_directory(path)) return std::nullopt;

    std::string pathStr = path.string();

    // ��� �ڸ���
    pathStr = pathStr.substr(pathStr.find_last_of("\\") + 1);

    // Ȯ���� �̱�
    std::string extentionStr = pathStr.substr(pathStr.find_last_of(".") + 1);

    return extentionStr;

}


