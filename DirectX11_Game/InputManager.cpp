#include "InputManager.h"

const KeyCode InputManager::keyCodes = KeyCode();
bool InputManager::mouseDown = false;
XMINT2 InputManager::mousePos = { 0,0 };
XMINT2 InputManager::prevMousePos = { 0,0 };
XMINT2 InputManager::deltaMouse = { 0,0 };

// This returns whether or not the specified key is set.
// Use Inputmanager::keyCodes for list of available codes
bool InputManager::GetKey(Key key)
{
	return ((GetAsyncKeyState(key.lower) & 0x8000) || (GetAsyncKeyState(key.uppper) & 0x8000));
}

// TODO: Write logic to determine between key held, down, and up
bool InputManager::GetKeyDown(Key key)
{
	return false;
}

// TODO: Write logic to determine between key held, down, and up
bool InputManager::GetKeyUp(Key key)
{
	return false;
}

// TODO: Take mouse tracking out of MyDemoGame
bool InputManager::GetMouseButton(UINT button)
{
	return mouseDown;
}

// TODO: Take mouse tracking out of MyDemoGame
bool InputManager::GetMouseButtonDown(UINT button)
{
	return false;
}

// TODO: Take mouse tracking out of MyDemoGame
bool InputManager::GetMouseButtonUp(UINT button)
{
	return false;
}

// TODO: Take mouse tracking out of MyDemoGame
XMINT2 InputManager::MousePosition()
{
	return mousePos;
}

XMINT2 InputManager::DeltaMouse()
{
	return deltaMouse;
}

void InputManager::SetMousePos(XMINT2 pos)
{
	prevMousePos = mousePos;
	mousePos = pos;
	deltaMouse = { mousePos.x - prevMousePos.x, mousePos.y - prevMousePos.y };
}

void InputManager::SetMouseDown(bool down)
{
	mouseDown = down;
}
