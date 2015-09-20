#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

class Camera
{
public:
	Camera(float aspectRatio, XMFLOAT3 position = { 0,0,-5 }, XMFLOAT2 rotation = { 0,0 }, bool debug = false);
	~Camera();

	XMFLOAT4X4 ViewMat();
	XMFLOAT4X4 ProjectionMat();

	void Rotation(float x, float y);
	void Rotation(XMFLOAT2 rot);

	void SetFOV(float angle);
	void SetAspectRatio(float aspect);
	void SetNearClipPlane(float nearDist);
	void SetFarClipPlane(float farDist);

	void Update(float deltaTime);

private:
	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;

	XMFLOAT3 position;
	XMFLOAT3 forward;
	XMFLOAT3 right;

	XMFLOAT2 rotation;

	float FOV;
	float aspectRatio;
	float nearClip;
	float farClip;

	bool debug;
	bool dirty;

	void CalculateProj();
	void CalculateView();
};

