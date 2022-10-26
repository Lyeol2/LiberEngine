#pragma once

/* -THINKING-
	모델의 버퍼등록, 렌더과정을 Model클래스에서 다루기보다
	이름이 적절한 Renderer클래스에서 다루는게 옳다고 판단했다.
	그래서 모델등록 클래스는 DX11Renderer로 간다.
*/

/* DX11형식의 모델을 다룹니다.*/
class DX11Model
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	DX11Model();
	virtual ~DX11Model();

	void Initialize();





};