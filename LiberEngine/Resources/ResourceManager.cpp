#include "pch.h"
#include "AssetsReader.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Initialize()
{

	assetsReader = std::make_unique<AssetsReader>();

	fs::path assetsPath(AssetsPath);

	fs::directory_entry dirEntry(assetsPath);

	// ���͸��� �����ϰ� , �Ϲ��������� �˻�
	if (!(dirEntry.exists() && dirEntry.is_directory()))
	{
		// ���ٸ� ���丮 ����
		LB_LOG(Warning, "Didn't have assets directory so create assets directory");
		fs::create_directory(assetsPath);
		
	}

	/* -THINKING-
		���ݺ��� ���丮�� ��ȸ�Ҳ���
		ã�ƾ��� ��������..
		Model (fbx)
		Texture (png)
		MetaFile (liber)
		Scripts (h, cpp)
		.. �� ��ȸ�ϰ� ������ �ڿ��޸𸮿� �÷�����.*/ 

	// ���丮 ��ȸ�� 
	// ����ؼ� ������丮���� ã��
	fs::recursive_directory_iterator directoryIter(assetsPath);
	
	while (directoryIter != fs::end(directoryIter))
	{
		const fs::directory_entry& entry = *directoryIter;

		LB_LOG(Log, entry.path().string());

		// C++(?) auto[] ����Ÿ���߷� 
		auto[type, asset] = assetsReader->ReadAssets(entry.path());
		
		directoryIter++;
	}
	
}

void ResourceManager::Reload()
{
}
