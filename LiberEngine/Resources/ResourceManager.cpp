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
		MetaFile (lasset)
		Scripts (h, cpp)
		.. 을 조회하고 엔진의 자원메모리에 올려두자.*/ 

	// 디렉토리 순회자 
	// 재귀해서 서브디렉토리까지 찾음
	for (fs::recursive_directory_iterator directoryIter(assetsPath);
		directoryIter != fs::end(directoryIter); 
		++directoryIter)
	{
		/* -THINKING-
			Iterator를 구문마지막에  안적으면 string too long 오류를 띄운다
			왠진 모름; 아마 함수내에서 참조할때 뭔가 있나보다. 지금은 해결못하니 미해결로
			남겨둠 반복자 증감은 함수 끝에서 처리하는 걸로 결정 또는 for문 사용
		*/
		
		const fs::directory_entry& entry = *directoryIter;
		
		/* -TODO- 
			switch 내부 문자열을 사용할 수 없다 해쉬를 사용해서 처리하는 사람들이 있다.
			(표준 해쉬 라이브러리를 사용해도 괜찮을꺼같다 map, hash, ect..)
			만약에 성능이슈가 난다면 처리해할 문제. 현재는 if else를 사용한다*/
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
		
		// 에셋메타파일이 있는지 체크한뒤 로드
		if (assetsReader->HasLAsset(entry.path()))
		{
			// 가지고 있다면 그 lasset 로드
		}
		else
		{
			// 아니면 생성
		}
	}
	
}

void ResourceManager::Reload()
{
}
