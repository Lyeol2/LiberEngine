#pragma once


/* Fbx모델을 로더할때 사용합니다. 
	메타파일을 생성하거나 ...*/
class FbxModelLoader
{
public:
	FbxModelLoader();
	virtual ~FbxModelLoader();

	void Initialize();

	void Destroy();

private:
	/* -THINKING-
		원래는 스마트포인터로 작성하려했는데
		FbxManager로 스마트포인터를 생성하니까 C2248 오류를 띄웠다.
		오버라이드된 fbx객체의 delete때문인거 같은데.. 
		당장은 해결못하니 일반 포인터로 작성하도록 하자.
		(람다식써서 어찌저찌 두번째 템플릿 인수에 뭐적으면 될지도.)
	*/
	FbxManager* m_fbxManager;
	FbxImporter* m_fbxImporter;


	
};