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
	// input ouput 을 세팅합니다.
	FbxIOSettings* ios = FbxIOSettings::Create(m_fbxManager, IOSROOT);
	m_fbxManager->SetIOSettings(ios);


	// fbx파일을 임포터로 초기화합니다.
	bool result = m_fbxImporter->Initialize(
		filePath.c_str(), -1, m_fbxManager->GetIOSettings());

	if (!result)
	{
		LB_LOG(Error, "FbxImporter::Initialize() failed.", __LINE__, __FUNCTION__, __FILE__);
		return nullptr;
	}

	// 씬객체 생성
	FbxScene* fbxScene = FbxScene::Create(m_fbxManager, "Scene");


	// 임포터를 활용해서 씬 초기화
	result = m_fbxImporter->Import(fbxScene);

	if (!result)
	{
		LB_LOG(Error, "FbxImporter::Import() failed.", __LINE__, __FUNCTION__, __FILE__);
		return nullptr;
	}

	// 씬의 루트 노드를 받아옵니다.
	FbxNode* rootNode = fbxScene->GetRootNode();

	// 좌표축을 가져온다.
	FbxAxisSystem sceneAxisSystem = fbxScene->GetGlobalSettings().GetAxisSystem();

	// -TODO- 현재는 DX지만 나중에는 여러 그래픽스라이브러리로 바꿀수 있도록 개발
	FbxAxisSystem::DirectX.ConvertScene(fbxScene);

	// 씬 내에서 삼각형화 할 수 있는 모든 노드를 삼각형화 시킨다.
	FbxGeometryConverter geometryConverter(m_fbxManager);
	// -TODO- 생각보다 오래걸리는 작업 최적화 필요.
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
