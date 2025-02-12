#pragma once

//	TODO
class BoxComponent;
class CircleComponent;
class PhysicsManager
{
public:
	void Update();

private:
	bool Intersect(const std::shared_ptr<CircleComponent>& a, const std::shared_ptr<CircleComponent>& b);
	bool Intersect(const std::shared_ptr<BoxComponent>& a, const std::shared_ptr<BoxComponent>& b);

	bool CanCollision(const std::shared_ptr<BoxComponent>& a, const std::shared_ptr<BoxComponent>& b);
};

