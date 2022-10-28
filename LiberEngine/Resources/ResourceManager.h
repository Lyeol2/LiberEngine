#pragma once

/* -THINKING- 
	����Ƽ�� meta������ ����
	�𸮾��� ��翡���� uasset�� ��ȯ
	*/ 

// ���ҽ� Ÿ��
enum class ResourceType
{
	Unknown,
	Script,
	Texture,
	Model,
};
/*	
	���� ���ҽ��� �����մϴ�.
	���ӿ� �ʿ��� �����͸� ĳ������ �����ϴ�.
*/
class RESOURCES_API ResourceManager
{
	
public:
	ResourceManager();
	virtual ~ResourceManager();

	/*	���ҽ� ������ �ʱ�ȭ �մϴ�.
		��� ĳ�������͸� ����� Assets ������ 
		���ҽ������� �����ɴϴ�.
	*/
	void Initialize();

	/*	���ҽ��� �ٽ� �ε��մϴ�. */
	void Reload();

private:
	std::unique_ptr<class AssetsReader> assetsReader;








};