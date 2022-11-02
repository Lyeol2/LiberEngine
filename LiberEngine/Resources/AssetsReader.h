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
	*  .lasset 파일을 읽어 LAsset 객체를 생성합니다.
	*  | Template :
	*  - LAsset : 사용할 AssetType 자원의 형식입니다. (Enum)ResourceType 과 관련이 있습니다.
	* 
	*  | Parameter :
	*  - fs::path path : 읽을 에셋 경로 (fs << std::filesystem) Condition: ~~.lasset
	*/
	template<typename AssetType>
	AssetType ReadLAssets(fs::path path);
public:
	/*
	*  에셋을 읽습니다 .lasset 형식의 파일이 없다면 생성합니다.
	*  | Parameter :
	*  - fs::path path : 읽을 에셋 경로 (fs << std::filesystem)
	*  | Return : 
	*  - std::pair<ResourceType, LAsset> : 리소스타입과 LAsset 객체를 반환합니다
	*/
	std::pair<FileType, std::shared_ptr<LAsset>> ReadAssets(fs::path path);

	// >>
	//	 .lasset를 가진 파일인지 확인합니다.
	//  
	//  # Parameter :		
	//        - fs::path path : 파일의 경로입니다.
	//  # Return :			
	//        - bool : lasset를 가진파일이라면 참을 반환합니다.
	// <<
	inline bool HasLAsset(fs::path path);
	// >>
	//	 파일 확장자를 검사해서 반환합니다.
	//  
	//  # Parameter :		
	//        - fs::path path : 파일의 경로입니다.
	//  # Return :			
	//        - std::optional<std::string> : 확장자의 이름을 반환합니다 없다면 nullopt
	// <<
	std::optional<std::string> GetAssetExtension(fs::path path);

};

#include "AssetsReader.hpp"
