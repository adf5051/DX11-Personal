#include "GameEntity.h"

GameEntity::GameEntity(Mesh *mesh, Material* mat)
{
	this->mesh = mesh;
	this->material = mat;

	position = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };

	XMMATRIX w = XMMatrixIdentity();
	XMStoreFloat4x4(&world, w);
}


GameEntity::~GameEntity()
{
}

XMFLOAT4X4 GameEntity::WorldMat()
{
	return world;
}

#pragma region Position Accessors/Modifiers

XMFLOAT3 GameEntity::Position()
{
	return position;
}

void GameEntity::SetPosition(XMFLOAT3 pos)
{
	position = pos;
	dirty = true;
}

void GameEntity::SetPosX(float x)
{
	position.x = x;
	dirty = true;
}

void GameEntity::SetPosY(float y)
{
	position.y = y;
	dirty = true;
}

void GameEntity::SetPosZ(float z)
{
	position.z = z;
	dirty = true;
}

#pragma endregion

#pragma region Rotation Accessors/Modifiers

XMFLOAT3 GameEntity::Rotation()
{
	return rotation;
}

void GameEntity::SetRotation(XMFLOAT3 rot)
{
	rotation = rot;
	dirty = true;
}

void GameEntity::SetRotX(float x)
{
	rotation.x = x;
	dirty = true;
}

void GameEntity::SetRotY(float y)
{
	rotation.y = y;
	dirty = true;
}

void GameEntity::SetRotZ(float z)
{
	rotation.z = z;
	dirty = true;
}

#pragma endregion

#pragma region Scale Acessors/Modifiers

XMFLOAT3 GameEntity::Scale()
{
	return scale;
}

void GameEntity::SetScale(XMFLOAT3 scale)
{
	this->scale = scale;
	dirty = true;
}

void GameEntity::SetScaleX(float x)
{
	scale.x = x;
	dirty = true;
}

void GameEntity::SetScaleY(float y)
{
	scale.y = y;
	dirty = true;
}

void GameEntity::SetScaleZ(float z)
{
	scale.z = z;
	dirty = true;
}

#pragma endregion

void GameEntity::Move(XMFLOAT3 vel)
{
	Move(XMLoadFloat3(&vel));
}

void GameEntity::Move(XMVECTOR vel)
{
	XMVECTOR pos = XMLoadFloat3(&position);
	pos += vel;
	XMStoreFloat3(&position, pos);
	dirty = true;
}

void GameEntity::Draw(ID3D11DeviceContext *deviceContext, XMFLOAT4X4 view, XMFLOAT4X4 proj)
{
	PrepareMaterial(view, proj);

	if (dirty)
	{
		XMMATRIX w = XMLoadFloat4x4(&world);
		XMMATRIX trans = XMMatrixTranslation(position.x, position.y, position.z);
		XMMATRIX rot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));
		XMMATRIX scal = XMMatrixScaling(scale.x, scale.y, scale.z);
		w = scal * rot * trans;
		XMStoreFloat4x4(&world, XMMatrixTranspose(w));
	}

	mesh->Draw(deviceContext);

	dirty = false;
}

void GameEntity::SetDirectionalLight(DirectionalLight *light)
{
	dirLight = light;
}

void GameEntity::SetSunLight(DirectionalLight *light)
{
	sun = light;
}

void GameEntity::PrepareMaterial(XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	material->GetPixelShader()->SetData(
		"light",
		sun,
		sizeof(DirectionalLight)
	);

	material->GetPixelShader()->SetData(
		"exLight",
		dirLight,
		sizeof(DirectionalLight)
		);

	material->GetPixelShader()->SetFloat4("surfaceColor", { .5f,.5f,.8f,1 });

	material->GetVertexShader()->SetMatrix4x4("world", world);
	material->GetVertexShader()->SetMatrix4x4("view", view);
	material->GetVertexShader()->SetMatrix4x4("projection", projection);

	material->GetVertexShader()->SetShader(true);
	material->GetPixelShader()->SetShader(true);
}
