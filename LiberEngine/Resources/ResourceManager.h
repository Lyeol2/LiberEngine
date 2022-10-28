#pragma once

/* -THINKING- 
	유니티는 meta파일을 생성
	언리얼은 모든에셋을 uasset로 변환
	*/ 

// 리소스 타입
enum class ResourceType
{
	Unknown,
	Script,
	Texture,
	Model,
};
/*	
	게임 리소스를 관리합니다.
	게임에 필요한 데이터를 캐쉬시켜 놓습니다.
*/
class RESOURCES_API ResourceManager
{
	
public:
	ResourceManager();
	virtual ~ResourceManager();

	/*	리소스 정보를 초기화 합니다.
		모든 캐쉬데이터를 지우고 Assets 폴더의 
		리소스정보를 가져옵니다.
	*/
	void Initialize();

	/*	리소스를 다시 로드합니다. */
	void Reload();

private:
	std::unique_ptr<class AssetsReader> assetsReader;








};