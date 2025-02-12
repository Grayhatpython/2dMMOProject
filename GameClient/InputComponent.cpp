#include "pch.h"
#include "InputComponent.h"
#include "Manager.h"

InputComponent::InputComponent()
	: MoveComponent(ComponentType::Input)
{
}

void InputComponent::ProcessInput()
{
	const auto& state = Manager::GetInputManager()->GetState();

	float forwardSpeed = 0.0f;
	if (state.keyboard.GetKeyValue(SDL_Scancode(_forwardKey)))
		forwardSpeed += _maxForwardSpeed;
	if (state.keyboard.GetKeyValue(SDL_Scancode(_backKey)))
		forwardSpeed -= _maxForwardSpeed;
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (state.keyboard.GetKeyValue(SDL_Scancode(_clockwiseKey)))
		angularSpeed += _maxAngularSpeed;
	if (state.keyboard.GetKeyValue(SDL_Scancode(_counterClockwiseKey)))
		angularSpeed -= _maxAngularSpeed;
	SetAngularSpeed(angularSpeed);
}
