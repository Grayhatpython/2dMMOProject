#include "pch.h"
#include "PhysicsManager.h"
#include "CircleComponent.h"
#include "BoxComponent.h"
#include "Manager.h"
#include "Scene.h"
#include "Actor.h"
#include "BoxComponent.h"

void PhysicsManager::Update()
{
    const auto& actors = Manager::GetSceneManager()->GetCurrentScene()->GetActors();

    // 좀 느리다...
    // BoxComponent가 있는 Actor들을 저장
    std::vector<std::shared_ptr<BoxComponent>> boxComponents;

    for (const auto& actor : actors)
    {
        auto box = actor->GetBoxComponent();
        if (box) // BoxComponent가 있는 Actor만 저장
            boxComponents.push_back(box);
    }

    // 충돌 검사 (N^2 루프지만 중복 검사 방지)
    int32 size = static_cast<int32>(boxComponents.size());
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++) 
        {
            auto& a = boxComponents[i];
            auto& b = boxComponents[j];

            // 충돌 가능 여부 확인
            if (CanCollision(a, b) == false)
                continue;

            if (Intersect(a, b))
            {
                // 충돌 이벤트 발생
                a->GetOwner()->OnCollision(b->GetOwner());
                b->GetOwner()->OnCollision(a->GetOwner());
            }
        }
    }
}

bool PhysicsManager::Intersect(const std::shared_ptr<CircleComponent>& a, const std::shared_ptr<CircleComponent>& b)
{
	Vector2 diffSquared = a->GetCenter() - b->GetCenter();
	float distSq = diffSquared.LengthSq();

	float radiusSquared = a->GetRadius() + b->GetRadius();
	radiusSquared *= radiusSquared;

	return distSq <= radiusSquared;
}

bool PhysicsManager::Intersect(const std::shared_ptr<BoxComponent>& a, const std::shared_ptr<BoxComponent>& b)
{
	auto aObjectBox = a->GetObjectBox();
	auto bObjectBox = b->GetObjectBox();

	// AABB 충돌 검사
	bool overlapX = (aObjectBox.min.x <= bObjectBox.max.x) && (aObjectBox.max.x >= bObjectBox.min.x);
	bool overlapY = (aObjectBox.min.y <= bObjectBox.max.y) && (aObjectBox.max.y >= bObjectBox.min.y);

	return overlapX && overlapY; // X, Y축 모두 겹치면 충돌 발생
}

bool PhysicsManager::CanCollision(const std::shared_ptr<BoxComponent>& a, const std::shared_ptr<BoxComponent>& b)
{
    int32 layerA = static_cast<int32>(a->GetCollisionLayer());
    int32 layerB = static_cast<int32>(b->GetCollisionLayer());

    int32 maskA = a->GetCollisionMask();
    int32 maskB = b->GetCollisionMask();

    return (maskA & layerB) != 0 || (maskB & layerA) != 0;
}

