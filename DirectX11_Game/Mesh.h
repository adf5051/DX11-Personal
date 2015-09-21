#pragma once

#include <vector>
#include <fstream>
#include <DirectXMath.h>
#include <d3d11.h>
#include "Vertex.h"


class Mesh
{
public:
	Mesh(Vertex *vertices, int numVertices, int *indices, int numIndices, ID3D11Device *device);
	Mesh(char* fileName, ID3D11Device *device);

	~Mesh();

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

	int GetIndexCount();

	void Draw(ID3D11DeviceContext *deviceContext);

private:
	ID3D11Buffer *vertexBuff;
	ID3D11Buffer *indexBuff;

	int numIndices;
};

