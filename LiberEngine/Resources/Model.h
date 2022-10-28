#pragma once
#include "LAsset.h"

/* 모델에셋은 정점, 인덱스, 노말 등.. 의 데이터를 가집니다.*/
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