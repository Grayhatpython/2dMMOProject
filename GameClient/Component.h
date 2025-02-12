#pragma once

class Actor;
class Component : public std::enable_shared_from_this<Component>
{
	friend class Actor;

public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Update();
	virtual void ProcessInput();

public:
	ComponentType						GetType() { return _type; }
	std::shared_ptr<Actor>				GetOwner()	{ return _owner.lock(); }
	const std::shared_ptr<Actor>		GetOwner()	const { return _owner.lock(); }
	void								SetOwner(std::shared_ptr<Actor> owner) { _owner = owner; }

protected:
	ComponentType			_type;
	std::weak_ptr<Actor>	_owner;
};

