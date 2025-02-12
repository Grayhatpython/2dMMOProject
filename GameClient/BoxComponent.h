#pragma once
#include "Component.h"

struct CollisionInfo
{
	CollisionLayer	layer;
	int32			collisionMask = 0;
};

struct AABB
{
	AABB(const Vector2& min, const Vector2& max)
		: min(min), max(max) {}

	Vector2 min;
	Vector2 max;
};

class BoxComponent : public Component
{
public:
	BoxComponent();

public:
	virtual void Update() override;

public:
	//	TODO
	AABB			GetObjectBox() { return _objectBox; }

	void			SetCollisionLayer(CollisionLayer layer) { _collisionInfo.layer = layer; }
	void			SetCollisionMask(int mask) { _collisionInfo.collisionMask = mask; }

	CollisionLayer	GetCollisionLayer() const { return _collisionInfo.layer; }
	int				GetCollisionMask() const { return _collisionInfo.collisionMask; }

private:
	AABB			_objectBox{ Vector2::Zero, Vector2::Zero };
	CollisionInfo	_collisionInfo;
};

