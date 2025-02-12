#pragma once
#include <SDL/SDL_mouse.h>
#include <SDL/SDL_scancode.h>

class KeyboardState
{
public:
	friend class InputManager;

public:
	bool			GetKeyValue(SDL_Scancode keyCode) const;
	ButtonState		GetKeyState(SDL_Scancode keyCode) const;

private:
	const uint8*	_currentState = nullptr;
	uint8			_prevState[SDL_NUM_SCANCODES];
};

class MouseState
{
public:
	friend class InputManager;

public:
	const Vector2&	GetPosition() const { return _mousePosition; }
	const Vector2&	GetScrollWheel() const { return _scrollWheel; }
	bool			IsRelative() const { return _isRelative; }

	bool			GetButtonValue(int32 button) const;
	ButtonState		GetButtonState(int32 button) const;

private:
	Vector2 _mousePosition;
	Vector2 _scrollWheel;

	uint32 _currentButtons{ 0 };
	uint32 _prevButtons{ 0 };

	bool _isRelative = false;
};

struct InputState
{
	KeyboardState	keyboard;
	MouseState		mouse;
};

class InputManager
{
public:
	bool Initialize();
	void Clear();

	void PrepareForUpdate();
	void Update();

	void ProcessEvent(union SDL_Event& event);

public:
	const InputState& GetState() const { return _state; }

	void SetRelativeMouseMode(bool value);

private:
	InputState	_state;
};


