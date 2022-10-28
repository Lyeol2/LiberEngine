#pragma once
#include "ResourceManager.h"
#include "Model.h"

/* 메타파일을 읽거나 생성합니다. */
class AssetsReader
{
public:
	AssetsReader();
	virtual ~AssetsReader();
private:
	/*
	*  .lasset 파일을 생성합니다
	*  | Template :
	*  - LAsset : 사용할 LAsset 자원의 형식입니다. (Enum)ResourceType 과 관련이 있습니다.
	* 
	*  | Parameter :
	*  - fs::path path : 읽을 에셋 경로 (fs << std::filesystem)
	* 
	*  | Return :
	*  - LAsset 반환할 lasset의 데이터
	*/
	template<typename AssetType = LAsset>
	AssetType CreateLAsset(fs::path path);
	/* template specialization*/
	template<>
	Model CreateLAsset(fs::path path);
	/*
	*  에셋을 읽습니다 .lasset 형식의 파일이 없다면 생성합니다.
	*  | Template :
	*  - LAsset : 사용할 AssetType 자원의 형식입니다. (Enum)ResourceType 과 관련이 있습니다.
	* 
	*  | Parameter :
	*  - fs::path path : 읽을 에셋 경로 (fs << std::filesystem) Condition: ~~.lasset
	*/
	template<typename AssetType>
	AssetType ReadLAssets(fs::path path);
public:
	/// <summary>
	/// asd
	/// </summary>
	/// <param name="path">asd</param>
	/// <returns>ads</returns>
	std::pair<ResourceType, LAsset> ReadAssets(fs::path path);

};

#include "AssetsReader.hpp"
