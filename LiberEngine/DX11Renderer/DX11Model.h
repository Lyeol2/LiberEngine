#pragma once

/* -THINKING-
	���� ���۵��, ���������� ModelŬ�������� �ٷ�⺸��
	�̸��� ������ RendererŬ�������� �ٷ�°� �Ǵٰ� �Ǵ��ߴ�.
	�׷��� �𵨵�� Ŭ������ DX11Renderer�� ����.
*/

/* DX11������ ���� �ٷ�ϴ�.*/
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