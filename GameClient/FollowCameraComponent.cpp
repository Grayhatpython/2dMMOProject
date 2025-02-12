#include "pch.h"
#include "FollowCameraComponent.h"
#include "Actor.h"
#include "Manager.h"
#include "Scene.h"
#include "FollowActor.h"

FollowCameraComponent::FollowCameraComponent()
	: CameraComponent(ComponentType::FollowCamera)
{

}

void FollowCameraComponent::Update()
{
    auto owner = GetOwner();
    if (owner == nullptr) 
        return;

    auto& target = Manager::GetSceneManager()->GetCurrentScene()->GetCamera()->GetTarget();

    Vector2 targetPosition = Vector2::Zero;

    if(target)
        targetPosition = target->GetPosition();

    Vector2 screenCenter = Manager::GetRenderManager()->GetScreenCenter();
    const auto& mapSize= Manager::GetRenderManager()->GetMapSize();

    // 오프셋 계산 (플레이어가 화면 중앙을 넘어갈 경우 적용)
    _cameraOffset.x = (targetPosition.x > screenCenter.x) ? (targetPosition.x - screenCenter.x) : 0.0f;
    _cameraOffset.y = (targetPosition.y > screenCenter.y) ? (targetPosition.y - screenCenter.y) : 0.0f;

    // 맵 범위를 벗어나지 않도록 오프셋 제한
    _cameraOffset.x = Math::Clamp(_cameraOffset.x, 0.0f, mapSize.x - Manager::GetRenderManager()->GetScreenWidth());
    _cameraOffset.y = Math::Clamp(_cameraOffset.y, 0.0f, mapSize.y - Manager::GetRenderManager()->GetScreenHeight());

}
