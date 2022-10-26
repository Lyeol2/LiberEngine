#include "pch.h"
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

void FbxModelLoader::Destroy()
{
	m_fbxManager->Destroy();
	m_fbxImporter->Destroy();
}
