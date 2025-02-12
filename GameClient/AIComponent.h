#pragma once
#include "Component.h"

class AIState;
class AIComponent : public Component
{
public:
	AIComponent();

public:
	void Update() override;
	void ChangeState(const std::wstring& name);

	void AddState(std::shared_ptr<AIState> state);

private:
	std::unordered_map<std::wstring, std::shared_ptr<AIState>>	_states;
	std::shared_ptr<AIState>									_currentState;
};
