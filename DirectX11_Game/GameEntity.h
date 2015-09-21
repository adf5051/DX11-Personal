#pragma once

#include <DirectXMath.h>
#include "Mesh.h"
#include "SimpleShader.h"
#include "Material.h"
#include "Light.h"

using namespace DirectX;

class GameEntity
{
public:
	GameEntity(Mesh *mesh, Material* mat);
	~GameEntity();

	XMFLOAT4X4 WorldMat();

	XMFLOAT3 Position();
	void SetPosition(XMFLOAT3 pos);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);

	XMFLOAT3 Rotation();
	void SetRotation(XMFLOAT3 rot);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	XMFLOAT3 Scale();
	void SetScale(XMFLOAT3 scale);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	void Move(XMFLOAT3 vel);

	void Move(XMVECTOR vel);

	void Draw(ID3D11DeviceContext *deviceContext, XMFLOAT4X4 view, XMFLOAT4X4 proj);

	void SetDirectionalLight(DirectionalLight *light);

	void SetSunLight(DirectionalLight *light);
	
private:

	void PrepareMaterial(XMFLOAT4X4 view, XMFLOAT4X4 projection);

	XMFLOAT4X4 world;

	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	Mesh* mesh;

	Material* material;

	DirectionalLight *sun;
	DirectionalLight *dirLight;


	bool dirty;
};

