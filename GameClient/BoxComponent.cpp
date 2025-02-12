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

        auto width = texture->GetTextureWidth();   // �ؽ�ó ���� ũ��
        auto height = texture->GetTextureHeight(); // �ؽ�ó ���� ũ��
        auto scale = owner->GetScale();             // ������Ʈ ������
        auto position = owner->GetPosition();       // ������Ʈ ��ġ (�߽� ��ǥ)

        // AABB ���
        Vector2 halfSize = Vector2(width * scale * 0.5f, height * scale * 0.5f);
        _objectBox.min = position - halfSize;
        _objectBox.max = position + halfSize;
    }
}
