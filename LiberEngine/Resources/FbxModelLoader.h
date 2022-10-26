#pragma once


/* Fbx���� �δ��Ҷ� ����մϴ�. 
	��Ÿ������ �����ϰų� ...*/
class FbxModelLoader
{
public:
	FbxModelLoader();
	virtual ~FbxModelLoader();

	void Initialize();

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