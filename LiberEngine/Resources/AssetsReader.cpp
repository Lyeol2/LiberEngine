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
        return std::pair<FileType, LAsset>(FileType::Directory, LAsset());
    }

    // Ȯ���� �˻�
    std::string extentionStr = pathStr.substr(pathStr.find(".") + 1);

    // ���� '.' ��ȣ�� �ִٸ� ���� ���
    if (extentionStr.find_last_of(".") != std::string::npos)
        throw EngineException(std::format("Do not include '.' in the filename.\nfilename is {0}", pathStr),
            __LINE__, __FUNCTION__, __FILE__);


    return std::pair<FileType, LAsset>();
}


