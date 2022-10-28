#pragma once
#include "LAsset.h"

/* �𵨿����� ����, �ε���, �븻 ��.. �� �����͸� �����ϴ�.*/
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
	// ���� ����
	std::vector<VertexInfo> vertices;
	// �ε��� ����
	std::vector<UINT> indices;
	
};