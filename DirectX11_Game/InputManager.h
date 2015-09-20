#pragma once
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Key { int lower; int uppper; };

struct KeyCode
{
	Key A = { 'a','A' };
	Key D = { 'd', 'D' };
	Key E = { 'e', 'E' };
	Key Q = { 'q', 'Q' };
	Key S = { 's', 'S' };
	Key W = { 'w','W' };
};

class InputManager
{
public:
	static bool GetKey(Key key);
	static bool GetKeyDown(Key key);
	static bool GetKeyUp(Key key);

	static bool GetMouseButton(UINT button);
	static bool GetMouseButtonDown(UINT button);
	static bool GetMouseButtonUp(UINT button);

	static XMINT2 MousePosition();
	static XMINT2 DeltaMouse();

	static const KeyCode keyCodes;

	// TODO: Remove this functionality and make InputManager Update mouse info
	static void SetMousePos(XMINT2 pos);
	static void SetMouseDown(bool down);
private:
	static XMINT2 mousePos;
	static XMINT2 prevMousePos;
	static XMINT2 deltaMouse;
	static bool mouseDown;

};



