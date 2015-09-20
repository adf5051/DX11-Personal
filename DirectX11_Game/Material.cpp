#include "Material.h"



Material::Material(SimplePixelShader* pixelShader, SimpleVertexShader* vertexShader)
{
	this->pixelShader = pixelShader;
	this->vertexShader = vertexShader;
}


Material::~Material()
{
	delete pixelShader;
	delete vertexShader;
}

SimpleVertexShader* Material::GetVertexShader()
{
	return vertexShader;
}

SimplePixelShader* Material::GetPixelShader()
{
	return pixelShader;
}
