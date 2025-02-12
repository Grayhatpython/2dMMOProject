#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	// Lower update order to update first
	InputComponent();

public:
	virtual void ProcessInput() override;

public:
	float	GetMaxForward() const { return _maxForwardSpeed; }
	float	GetMaxAngular() const { return _maxAngularSpeed; }
	int32	GetForwardKey() const { return _forwardKey; }
	int32	GetBackKey() const { return _backKey; }
	int32	GetClockwiseKey() const { return _clockwiseKey; }
	int32	GetCounterClockwiseKey() const { return _counterClockwiseKey; }

	void	SetMaxForwardSpeed(float speed) { _maxForwardSpeed = speed; }
	void	SetMaxAngularSpeed(float speed) { _maxAngularSpeed = speed; }
	void	SetForwardKey(int32 key) { _forwardKey = key; }
	void	SetBackKey(int32 key) { _backKey = key; }
	void	SetClockwiseKey(int32 key) { _clockwiseKey = key; }
	void	SetCounterClockwiseKey(int32 key) { _counterClockwiseKey = key; }

private:
	float _maxForwardSpeed{ 400.f };
	float _maxAngularSpeed{ 10.f };

	int32 _forwardKey{ 0 };
	int32 _backKey{ 0 };

	int32 _clockwiseKey{ 0 };
	int32 _counterClockwiseKey{ 0 };
};
