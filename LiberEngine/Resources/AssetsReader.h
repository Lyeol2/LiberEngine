#pragma once
#include "ResourceManager.h"
#include "Model.h"

/* ��Ÿ������ �аų� �����մϴ�. */
class AssetsReader
{
public:
	AssetsReader();
	virtual ~AssetsReader();
private:
	/*
	*  .lasset ������ �����մϴ�
	*  | Template :
	*  - LAsset : ����� LAsset �ڿ��� �����Դϴ�. (Enum)ResourceType �� ������ �ֽ��ϴ�.
	* 
	*  | Parameter :
	*  - fs::path path : ���� ���� ��� (fs << std::filesystem)
	* 
	*  | Return :
	*  - LAsset ��ȯ�� lasset�� ������
	*/
	template<typename AssetType = LAsset>
	AssetType CreateLAsset(fs::path path);
	/* template specialization*/
	template<>
	Model CreateLAsset(fs::path path);
	/*
	*  .lasset ������ �о� LAsset ��ü�� �����մϴ�.
	*  | Template :
	*  - LAsset : ����� AssetType �ڿ��� �����Դϴ�. (Enum)ResourceType �� ������ �ֽ��ϴ�.
	* 
	*  | Parameter :
	*  - fs::path path : ���� ���� ��� (fs << std::filesystem) Condition: ~~.lasset
	*/
	template<typename AssetType>
	AssetType ReadLAssets(fs::path path);
public:
	/*
	*  ������ �н��ϴ� .lasset ������ ������ ���ٸ� �����մϴ�.
	*  | Parameter :
	*  - fs::path path : ���� ���� ��� (fs << std::filesystem)
	*  | Return : 
	*  - std::pair<ResourceType, LAsset> : ���ҽ�Ÿ�԰� LAsset ��ü�� ��ȯ�մϴ�
	*/
	std::pair<FileType, LAsset> ReadAssets(fs::path path);

};

#include "AssetsReader.hpp"
