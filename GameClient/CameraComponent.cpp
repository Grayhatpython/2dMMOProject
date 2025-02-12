#include "pch.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent()
	: Component(ComponentType::Camera)
{

}

CameraComponent::CameraComponent(ComponentType type)
	: Component(type)
{
}
