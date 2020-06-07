#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

/* This class is used for XInput controller functionality 
** An XBox 360 style controller must be connected to use this
*/
class XInputController
{
public:
	XInputController(int id);
	~XInputController();

	XINPUT_STATE GetControllerState();
	XINPUT_GAMEPAD GetGamepadState();
	bool IsConnected();

private:
	int _id;
	XINPUT_STATE _state;
};

