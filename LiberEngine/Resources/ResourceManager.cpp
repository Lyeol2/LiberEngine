#include "pch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Initialize()
{
	fs::path assetsPath(AssetsPath);

	fs::directory_entry dirEntry(assetsPath);

	// ���͸��� �����ϰ� , �Ϲ��������� �˻�
	if (!(dirEntry.exists() && dirEntry.is_regular_file()))
	{
		LB_LOG(Warning, "Didn't have assets directory so create assets directory");
		fs::create_directory(assetsPath);
	}

}

void ResourceManager::Reload()
{
}
