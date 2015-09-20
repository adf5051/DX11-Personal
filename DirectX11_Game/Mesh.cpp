#include "Mesh.h"


Mesh::Mesh(Vertex *vertices, int numVertices, int *indices, int numIndices, ID3D11Device *device)
{
	this->numIndices = numIndices;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * numVertices;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;

	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuff);

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * numIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	device->CreateBuffer(&ibd, &initialIndexData, &indexBuff);

}


Mesh::~Mesh()
{
	vertexBuff->Release();
	indexBuff->Release();
}

ID3D11Buffer* Mesh::GetVertexBuffer()
{
	return vertexBuff;
}

ID3D11Buffer* Mesh::GetIndexBuffer()
{
	return indexBuff;
}

int Mesh::GetIndexCount()
{
	return numIndices;
}

void Mesh::Draw(ID3D11DeviceContext *deviceContext)
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->DrawIndexed(numIndices, 0, 0);
}
