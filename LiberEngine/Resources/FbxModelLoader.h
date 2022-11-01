#pragma once


/* Fbx���� �δ��Ҷ� ����մϴ�. 
	��Ÿ������ �����ϰų� ...*/
class FbxModelLoader
{
public:
	FbxModelLoader();
	virtual ~FbxModelLoader();

	void Initialize();

	// >>
	//	 Fbx ������ �������� �н��ϴ�.
	//  # Parameter : 
	//        - std::string filePath : fbx���� ���ϰ���Դϴ�.
	//  # Return :
	//        - std::shared_ptr<Model> : 
	//          �о�帰 �������� ����Ʈ �������Դϴ�. ���н� nullptr ��ȯ�մϴ�.
	// <<
	std::shared_ptr<Model> ReadFbxFile(std::string filePath);

	void Destroy();

private:
	/* -THINKING-
		������ ����Ʈ�����ͷ� �ۼ��Ϸ��ߴµ�
		FbxManager�� ����Ʈ�����͸� �����ϴϱ� C2248 ������ �����.
		�������̵�� fbx��ü�� delete�����ΰ� ������.. 
		������ �ذ���ϴ� �Ϲ� �����ͷ� �ۼ��ϵ��� ����.
		(���ٽĽἭ �������� �ι�° ���ø� �μ��� �������� ������.)
	*/
	FbxManager* m_fbxManager;
	FbxImporter* m_fbxImporter;


	
};