#pragma once

/* ��Ÿ������ �аų� �����մϴ�. */
class AssetsReader
{
public:
	AssetsReader();
	virtual ~AssetsReader();

private:
	auto ReadAssets(fs::path path);

};