#include "pch.h"
#include "InputManager.h"
#include <SDL/SDL.h>

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return  _currentState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (_prevState[keyCode] == 0)
	{
		if (_currentState[keyCode] == 0)
			return ButtonState::None;
		else
			return ButtonState::Pressed;
	}
	else 
	{
		if (_currentState[keyCode] == 0)
			return ButtonState::Released;
		else
			return ButtonState::Held;
	}
}

bool MouseState::GetButtonValue(int32 button) const
{
	return (SDL_BUTTON(button) & _currentButtons);
}

ButtonState MouseState::GetButtonState(int32 button) const
{
	int32 mask = SDL_BUTTON(button);
	if ((mask & _prevButtons) == 0)
	{
		if ((mask & _currentButtons) == 0)
			return ButtonState::None;
		else
			return ButtonState::Pressed;
	}
	else
	{
		if ((mask & _currentButtons) == 0)
			return ButtonState::Released;
		else
			return ButtonState::Held;
	}
}

bool InputManager::Initialize()
{
	// Keyboard
	_state.keyboard._currentState = ::SDL_GetKeyboardState(NULL);
	::memset(_state.keyboard._prevState, 0, SDL_NUM_SCANCODES);

	// Mouse
	_state.mouse._currentButtons = 0;
	_state.mouse._prevButtons = 0;

	return true;
}

void InputManager::Clear()
{

}

void InputManager::PrepareForUpdate()
{
	// Keyboard
	::memcpy(_state.keyboard._prevState,_state.keyboard._currentState,SDL_NUM_SCANCODES);

	// Mouse
	_state.mouse._prevButtons = _state.mouse._currentButtons;
	_state.mouse._isRelative = false;
	_state.mouse._scrollWheel = Vector2::Zero;
}

void InputManager::Update()
{
	// Mouse
	int x = 0, y = 0;

	if (_state.mouse._isRelative)
		_state.mouse._currentButtons = ::SDL_GetRelativeMouseState(&x, &y);
	else
		_state.mouse._currentButtons = ::SDL_GetMouseState(&x, &y);

	_state.mouse._mousePosition.x = static_cast<float>(x);
	_state.mouse._mousePosition.y = static_cast<float>(y);
}

void InputManager::ProcessEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEWHEEL:
		_state.mouse._scrollWheel = Vector2(static_cast<float>(event.wheel.x), static_cast<float>(event.wheel.y));
		break;
	default:
		break;
	}
}

void InputManager::SetRelativeMouseMode(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	::SDL_SetRelativeMouseMode(set);

	_state.mouse._isRelative = value;
}
