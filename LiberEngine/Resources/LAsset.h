#pragma once

/* Ȯ���� .LAsset ������ ������ ���̽� Ŭ���� �Դϴ�. 
	���ӿ� �ʿ��� ���ҽ��� �����͸� ����ϴ�.*/
class LAsset
{
public:
	LAsset();
	LAsset(fs::path path);
	virtual ~LAsset() noexcept;

private:
	GUID guid;

	std::string filename;
	fs::path filePath;


};