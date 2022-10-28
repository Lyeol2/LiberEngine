#pragma once
#include <typeinfo>
template<typename AssetType>
inline AssetType AssetsReader::CreateLAsset(fs::path path)
{
	// (C++17) if constexpr 템플릿 특수화
	if constexpr (!std::is_base_of<LAsset, AssetType>::value)
	{
		throw EngineException(std::format("[Generic Error] \'{0}\' wasn't derived from \'LAsset\'", typeid(AssetType).name()), __LINE__, __FUNCTION__, __FILE__);
	}
	return AssetType();


}
template<>
inline Model AssetsReader::CreateLAsset(fs::path path)
{
	return Model();
}
template<typename AssetType> 
inline AssetType AssetsReader::ReadLAssets(fs::path path)
{
	path += ".lasset";
	std::ifstream stream;

	// 파일을 엽니다.
	stream.open(path.string());

	if (!stream.is_open())
	{
		LB_LOG(Log, std::format("Didn't find lasset file so create lasset ## path:{0}", path.string()));
		CreateLAsset<AssetType>(path);
	}
	return AssetType();
}
