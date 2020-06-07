#include "XInputController.h"

XInputController::XInputController(int id) {
	this->_id = id;
}


XInputController::~XInputController()
{
}

XINPUT_STATE XInputController::GetControllerState() {
	/* Returns the controller state */
	memset(&_state, 0, sizeof(XINPUT_STATE));
	XInputGetState(_id, &_state);
	return _state;
}

XINPUT_GAMEPAD XInputController::GetGamepadState() {
	/* Returns the Gamepad state, i.e. what buttons are pressed */
	memset(&_state, 0, sizeof(XINPUT_STATE));
	XInputGetState(_id, &_state);
	return _state.Gamepad;
}

bool XInputController::IsConnected() {
	/* Checks if the controller is connected */
	memset(&_state, 0, sizeof(XINPUT_STATE));
	DWORD Result = XInputGetState(_id, &_state);
	return (Result == ERROR_SUCCESS);
}
