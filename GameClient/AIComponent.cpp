#include "pch.h"
#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"
#include <SDL/SDL_log.h>

AIComponent::AIComponent()
	: Component(ComponentType::AI)
{

}

void AIComponent::Update()
{
	if (_currentState)
		_currentState->Update();
}

void AIComponent::ChangeState(const std::wstring& name)
{
	// First exit the current state
	if (_currentState)
		_currentState->OnExit();

	// Try to find the new state from the map
	auto iter = _states.find(name);
	if (iter != _states.end())
	{
		_currentState = iter->second;
		// We're entering the new state
		_currentState->OnEnter();
	}
	else
	{
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		_currentState = nullptr;
	}
}

void AIComponent::AddState(std::shared_ptr<AIState> state)
{
	_states.insert(std::make_pair(state->GetName(), state));
}
