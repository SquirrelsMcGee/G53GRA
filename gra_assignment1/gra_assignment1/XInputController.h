#pragma once

#pragma comment(lib, "XInput.lib") 

#include <Windows.h>
#include <Xinput.h>

#define MAX_XINPUT_DEVICES 4

class XInputController
{
public:
	XInputController(int playerNumber);
	~XInputController();

	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);

private:
	XINPUT_STATE _controllerState;
	int _controllerNum;

};

