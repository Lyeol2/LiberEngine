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
		MetaFile (lasset)
		Scripts (h, cpp)
		.. �� ��ȸ�ϰ� ������ �ڿ��޸𸮿� �÷�����.*/ 

	// ���丮 ��ȸ�� 
	// ����ؼ� ������丮���� ã��
	for (fs::recursive_directory_iterator directoryIter(assetsPath);
		directoryIter != fs::end(directoryIter); 
		++directoryIter)
	{
		/* -THINKING-
			Iterator�� ������������  �������� string too long ������ ����
			���� ��; �Ƹ� �Լ������� �����Ҷ� ���� �ֳ�����. ������ �ذ���ϴ� ���ذ��
			���ܵ� �ݺ��� ������ �Լ� ������ ó���ϴ� �ɷ� ���� �Ǵ� for�� ���
		*/
		
		const fs::directory_entry& entry = *directoryIter;
		
		/* -TODO- 
			switch ���� ���ڿ��� ����� �� ���� �ؽ��� ����ؼ� ó���ϴ� ������� �ִ�.
			(ǥ�� �ؽ� ���̺귯���� ����ص� ������������ map, hash, ect..)
			���࿡ �����̽��� ���ٸ� ó������ ����. ����� if else�� ����Ѵ�*/
		auto extensionStr = assetsReader->GetAssetExtension(entry.path());

		if (!extensionStr.has_value())
		{
			LB_LOG(Log, std::format("Find directory path:{0}", entry.path()));
			continue;
		}
		else if (extensionStr.value() == "lasset")
		{
			LB_LOG(Log, std::format("Find lasset path:{0}", entry.path()));
			continue;
		}
		else
		{
			auto[type, lasset] = assetsReader->ReadAssets(entry.path());
		}
		
		// ���¸�Ÿ������ �ִ��� üũ�ѵ� �ε�
		if (assetsReader->HasLAsset(entry.path()))
		{
			// ������ �ִٸ� �� lasset �ε�
		}
		else
		{
			// �ƴϸ� ����
		}
	}
	
}

void ResourceManager::Reload()
{
}
