#pragma once

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







};