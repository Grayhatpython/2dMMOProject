#include "pch.h"
#include "BoxComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Texture.h"

BoxComponent::BoxComponent()
	: Component(ComponentType::Box)
{

}

void BoxComponent::Update()
{
    auto owner = GetOwner();
    ASSERT_CRASH(owner);

    if (owner)
    {
        auto sprite = owner->GetSpriteComponent();
        ASSERT_CRASH(sprite);

        auto texture = sprite->GetTexture();

        auto width = texture->GetTextureWidth();   // 텍스처 가로 크기
        auto height = texture->GetTextureHeight(); // 텍스처 세로 크기
        auto scale = owner->GetScale();             // 오브젝트 스케일
        auto position = owner->GetPosition();       // 오브젝트 위치 (중심 좌표)

        // AABB 계산
        Vector2 halfSize = Vector2(width * scale * 0.5f, height * scale * 0.5f);
        _objectBox.min = position - halfSize;
        _objectBox.max = position + halfSize;
    }
}
