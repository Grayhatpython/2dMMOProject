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

    // ������ ��� (�÷��̾ ȭ�� �߾��� �Ѿ ��� ����)
    _cameraOffset.x = (targetPosition.x > screenCenter.x) ? (targetPosition.x - screenCenter.x) : 0.0f;
    _cameraOffset.y = (targetPosition.y > screenCenter.y) ? (targetPosition.y - screenCenter.y) : 0.0f;

    // �� ������ ����� �ʵ��� ������ ����
    _cameraOffset.x = Math::Clamp(_cameraOffset.x, 0.0f, mapSize.x - Manager::GetRenderManager()->GetScreenWidth());
    _cameraOffset.y = Math::Clamp(_cameraOffset.y, 0.0f, mapSize.y - Manager::GetRenderManager()->GetScreenHeight());

}
