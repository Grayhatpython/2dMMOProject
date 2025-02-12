#pragma once

class AIComponent;
class AIState
{
public:
	AIState() = default;

public:
	virtual void Update() abstract;
	virtual void OnEnter() abstract;
	virtual void OnExit() abstract;

public:
	virtual const wchar_t* GetName() const abstract;

protected:
	std::weak_ptr<AIComponent> _owner;
};

class AIPatrol : public AIState
{
public:
	AIPatrol() = default;

public:
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const wchar_t* GetName() const override
	{
		return L"Patrol";
	}
};

class AIDeath : public AIState
{
public:
	AIDeath() = default;

public:
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const wchar_t* GetName() const override
	{
		return L"Death";
	}
};

class AIAttack : public AIState
{
public:
	AIAttack() = default;

public:
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const wchar_t* GetName() const override
	{
		return L"Attack";
	}
};
