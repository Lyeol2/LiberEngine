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
	*  ������ �н��ϴ� .lasset ������ ������ ���ٸ� �����մϴ�.
	*  | Template :
	*  - LAsset : ����� AssetType �ڿ��� �����Դϴ�. (Enum)ResourceType �� ������ �ֽ��ϴ�.
	* 
	*  | Parameter :
	*  - fs::path path : ���� ���� ��� (fs << std::filesystem) Condition: ~~.lasset
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
