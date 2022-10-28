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

	// 디렉터리가 존재하고 , 일반파일인지 검사
	if (!(dirEntry.exists() && dirEntry.is_directory()))
	{
		// 없다면 디렉토리 생성
		LB_LOG(Warning, "Didn't have assets directory so create assets directory");
		fs::create_directory(assetsPath);
		
	}

	/* -THINKING-
		지금부터 디렉토리를 순회할껀데
		찾아야할 파일형식..
		Model (fbx)
		Texture (png)
		MetaFile (liber)
		Scripts (h, cpp)
		.. 을 조회하고 엔진의 자원메모리에 올려두자.*/ 

	// 디렉토리 순회자 
	// 재귀해서 서브디렉토리까지 찾음
	fs::recursive_directory_iterator directoryIter(assetsPath);
	
	while (directoryIter != fs::end(directoryIter))
	{
		const fs::directory_entry& entry = *directoryIter;

		LB_LOG(Log, entry.path().string());

		// C++(?) auto[] 다중타입추론 
		auto[type, asset] = assetsReader->ReadAssets(entry.path());
		
		directoryIter++;
	}
	
}

void ResourceManager::Reload()
{
}
