#include "pch.h"
#include "Model.h"
#include "FbxModelLoader.h"

FbxModelLoader::FbxModelLoader()
{
}

FbxModelLoader::~FbxModelLoader()
{
}

void FbxModelLoader::Initialize()
{
	m_fbxManager = FbxManager::Create();
	m_fbxImporter = FbxImporter::Create(m_fbxManager, "");
}

std::shared_ptr<Model> FbxModelLoader::ReadFbxFile(std::string filePath)
{
	// input ouput �� �����մϴ�.
	FbxIOSettings* ios = FbxIOSettings::Create(m_fbxManager, IOSROOT);
	m_fbxManager->SetIOSettings(ios);


	// fbx������ �����ͷ� �ʱ�ȭ�մϴ�.
	bool result = m_fbxImporter->Initialize(
		filePath.c_str(), -1, m_fbxManager->GetIOSettings());

	if (!result)
	{
		LB_LOG(Error, "FbxImporter::Initialize() failed.", __LINE__, __FUNCTION__, __FILE__);
		return nullptr;
	}

	// ����ü ����
	FbxScene* fbxScene = FbxScene::Create(m_fbxManager, "Scene");


	// �����͸� Ȱ���ؼ� �� �ʱ�ȭ
	result = m_fbxImporter->Import(fbxScene);

	if (!result)
	{
		LB_LOG(Error, "FbxImporter::Import() failed.", __LINE__, __FUNCTION__, __FILE__);
		return nullptr;
	}

	// ���� ��Ʈ ��带 �޾ƿɴϴ�.
	FbxNode* rootNode = fbxScene->GetRootNode();

	// ��ǥ���� �����´�.
	FbxAxisSystem sceneAxisSystem = fbxScene->GetGlobalSettings().GetAxisSystem();

	// -TODO- ����� DX���� ���߿��� ���� �׷��Ƚ����̺귯���� �ٲܼ� �ֵ��� ����
	FbxAxisSystem::DirectX.ConvertScene(fbxScene);

	// �� ������ �ﰢ��ȭ �� �� �ִ� ��� ��带 �ﰢ��ȭ ��Ų��.
	FbxGeometryConverter geometryConverter(m_fbxManager);
	// -TODO- �������� �����ɸ��� �۾� ����ȭ �ʿ�.
	geometryConverter.Triangulate(fbxScene, true);

	auto searchNodeFunc = [](FbxNode* node) 
	{
		const int childCount = node->GetChildCount();

	};


	rootNode->Destroy();
	fbxScene->Destroy();
	fbxScene = nullptr;

	return nullptr;
}

void FbxModelLoader::Destroy()
{
	m_fbxImporter->Destroy();
	m_fbxManager->Destroy();
}
