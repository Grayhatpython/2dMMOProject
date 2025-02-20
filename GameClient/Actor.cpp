#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "BoxComponent.h"
#include "FollowCameraComponent.h"
#include "AnimSingleSpriteComponent.h"
#include "GridComponent.h"

Actor::Actor()
{
}

Actor::Actor(const std::wstring& name)
	: _name(name)
{
}

Actor::~Actor()
{
	std::wcout << _name << std::endl;
}

void Actor::Initialize()
{

}

void Actor::Update()
{
	if (_state == ActorState::Active)
	{
		UpdateComponents();
		UpdateActor();
	}
}

void Actor::UpdateComponents()
{
	for (auto& component : _components)
	{
		if(component)
			component->Update();
	}
}

void Actor::UpdateActor()
{

}

void Actor::ProcessInput()
{
	if (_state == ActorState::Active)
	{
		// First process input for components
		for (auto& component : _components)
		{
			if (component)
				component->ProcessInput();
		}

		ActorInput();
	}
}

void Actor::ActorInput()
{

}

void Actor::OnCollision(std::shared_ptr<Actor> other)
{
}

std::shared_ptr<TransformComponent> Actor::GetTransformComponent()
{
	auto component = GetComponent(ComponentType::Transform);
	return std::static_pointer_cast<TransformComponent>(component);
}

std::shared_ptr<SpriteComponent> Actor::GetSpriteComponent()
{
	auto component = GetComponent(ComponentType::Sprite);

	if (component == nullptr)
		component = GetComponent(ComponentType::AnimSingleSprite);

	return std::static_pointer_cast<SpriteComponent>(component);
}

std::shared_ptr<CircleComponent> Actor::GetCircleComponent()
{
	auto component = GetComponent(ComponentType::Circle);
	return std::static_pointer_cast<CircleComponent>(component);
}

std::shared_ptr<BoxComponent> Actor::GetBoxComponent()
{
	auto component = GetComponent(ComponentType::Box);
	return std::static_pointer_cast<BoxComponent>(component);
}

std::shared_ptr<FollowCameraComponent> Actor::GetFollowCameraComponent()
{
	auto component = GetComponent(ComponentType::FollowCamera);
	return std::static_pointer_cast<FollowCameraComponent>(component);
}

std::shared_ptr<GridComponent> Actor::GetGridComponent()
{
	auto component = GetComponent(ComponentType::Grid);
	return std::static_pointer_cast<GridComponent>(component);
}

void Actor::AddComponent(std::shared_ptr<Component> component)
{
	component->SetOwner(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < COMPONENT_COUNT)
		_components[index] = component;
}

void Actor::RemoveComponent(std::shared_ptr<Component> component)
{
	auto type = component->GetType();
	uint8 index = static_cast<uint8>(type);
	ASSERT_CRASH(index < COMPONENT_COUNT);
	_components[index] = nullptr;
}

std::shared_ptr<Component> Actor::GetComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	ASSERT_CRASH(index < COMPONENT_COUNT);
	return _components[index];
}