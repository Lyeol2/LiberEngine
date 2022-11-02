#pragma once
#include "LAsset.h"

/* 모델에셋은 정점, 인덱스, 노말 등.. 의 데이터를 가집니다.*/
/* -TODO-
	나중에 하나의 모델에 매쉬가 2개거나 상속구조로 되어있을때 처리를 해줘야힘.
	당장은 DX11을 익혀야 하기때문에 하나의 매쉬만 불러오도록 한다.*/
class Model : LAsset
{
private:
	struct VertexInfo
	{
		// vertex
		float x, y, z;
		// tex
		float tu, tv;
		// nomarl
		float nx, ny, nz;
	};
public:
	Model();
	virtual ~Model() noexcept;

private:
	// 정점 정보
	std::vector<VertexInfo> vertices;
	// 인덱스 정보
	std::vector<UINT> indices;
	
};