#pragma once

#include "SimpleShader.h"

class Material
{
public:
	Material(SimplePixelShader* pixelShader, SimpleVertexShader* vertexShader);
	~Material();

	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();

private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};

