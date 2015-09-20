#include "Camera.h"

#include "InputManager.h"

#define PI 3.1415926535f

Camera::Camera(float aspectRatio, XMFLOAT3 position, XMFLOAT2 rotation, bool debug)
{
	if (aspectRatio == 0)
	{
		this->aspectRatio = (float)8 / 6;
	}
	else
	{
		this->aspectRatio = aspectRatio;
	}
	this->debug = debug;
	this->position = position;
	this->rotation = rotation;
	FOV = 0.25f * PI;
	nearClip = 0.1f;
	farClip = 100.0f;

	CalculateProj();
	CalculateView();
}

Camera::~Camera()
{
}

XMFLOAT4X4 Camera::ViewMat()
{
	return view;
}

XMFLOAT4X4 Camera::ProjectionMat()
{
	return proj;
}

void Camera::Rotation(float x, float y)
{
	Rotation({ x,y });
}

void Camera::Rotation(XMFLOAT2 rot)
{
	rotation = rot;
	dirty = true;
}

void Camera::SetFOV(float angle)
{
	if (angle > PI * .45f) // 80ish degrees
	{
		FOV = PI * .45f;
	}
	else if (angle < PI * .1f) // 18ish degrees
	{
		FOV = PI * .1f;
	}
	else
	{
		FOV = angle;
	}

	dirty = true;
}

void Camera::SetAspectRatio(float aspect)
{
	aspectRatio = aspect;
	dirty = true;
}

void Camera::SetNearClipPlane(float nearDist)
{
	if (nearDist < .1f)
	{
		nearClip = .1f;
	}
	else if (nearDist >= farClip)
	{
		return;
	}
	else
	{
		nearClip = nearDist;
	}

	dirty = true;
}

void Camera::SetFarClipPlane(float farDist)
{
	if (farDist <= nearClip)
	{
		return;
	}

	farClip = farDist;

	dirty = true;
}

void Camera::Update(float deltaTime)
{
	XMVECTOR pos = XMLoadFloat3(&position);
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, 0);
	XMVECTOR dir = XMVector3Transform({ 0,0,1 }, rot);
	XMStoreFloat3(&forward, dir);

	XMVECTOR r = XMVector3Cross({ 0,1,0 }, dir);
	XMStoreFloat3(&right, r);

	if (debug)
	{
		if (InputManager::GetKey(InputManager::keyCodes.W))
		{
			pos = pos + (XMLoadFloat3(&forward) * deltaTime);
			dirty = true;
		}

		if (InputManager::GetKey(InputManager::keyCodes.S))
		{
			pos = pos - (XMLoadFloat3(&forward) * deltaTime);
			dirty = true;
		}

		if (InputManager::GetKey(InputManager::keyCodes.A))
		{
			pos = pos - (r * deltaTime);
			dirty = true;
		}

		if (InputManager::GetKey(InputManager::keyCodes.D))
		{
			pos = pos + (r * deltaTime);
			dirty = true;
		}

		if (InputManager::GetKey(InputManager::keyCodes.Q))
		{
			pos = pos + XMVECTOR{ 0,deltaTime,0 };
			dirty = true;
		}

		if (InputManager::GetKey(InputManager::keyCodes.E))
		{
			pos = pos - XMVECTOR{ 0,deltaTime,0 };
			dirty = true;
		}

		if (InputManager::GetMouseButton(0))
		{
			if (InputManager::DeltaMouse().x != 0)
			{
				rotation.y += InputManager::DeltaMouse().x * deltaTime;
				dirty = true;
			}

			if (InputManager::DeltaMouse().y != 0)
			{
				rotation.x += InputManager::DeltaMouse().y * deltaTime;
				dirty = true;
			}
		}

		XMStoreFloat3(&position, pos);
	}

	if (dirty)
	{
		CalculateView();
		CalculateProj();
		dirty = false;
	}
}

void Camera::CalculateProj()
{
	XMMATRIX p = XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearClip, farClip);
	XMStoreFloat4x4(&proj, XMMatrixTranspose(p));
}

void Camera::CalculateView()
{
	XMVECTOR pos = XMLoadFloat3(&position);
	XMVECTOR dir = XMLoadFloat3(&forward);

	XMMATRIX viewMat = XMMatrixLookToLH(pos, dir, { 0,1,0 });
	XMStoreFloat4x4(&view, XMMatrixTranspose(viewMat));
}


