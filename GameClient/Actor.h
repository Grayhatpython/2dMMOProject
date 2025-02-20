#pragma once

class Component;
class TransformComponent;
class SpriteComponent;
class CircleComponent;
class BoxComponent;
class FollowCameraComponent;
class GridComponent;
class Actor : public std::enable_shared_from_this<Actor>
{
public:
	Actor();
	Actor(const std::wstring& name);
	virtual ~Actor();

	virtual void Initialize();

	void			Update();
	void			UpdateComponents();
	virtual void	UpdateActor();

	void			ProcessInput();
	virtual void	ActorInput();

	virtual void	OnCollision(std::shared_ptr<Actor> other);

public:
	void			AddComponent(std::shared_ptr<Component> component);
	void			RemoveComponent(std::shared_ptr<Component> component);

public:
	const std::wstring& GetName() const { return _name; }
	void				SetName(const std::wstring& name) { _name = name; }
	const Vector2&		GetPosition() const { return _position; }
	void				SetPosition(const Vector2& position) { _position = position; }
	float				GetScale() const { return _scale; }
	void				SetScale(float scale) { _scale = scale; }
	float				GetRotation() const { return _rotation; }
	void				SetRotation(float rotation) { _rotation = rotation; }
	ActorState			GetState() const { return _state; }
	void				SetState(ActorState state) { _state = state; }

	Vector2				GetForward() const { return Vector2(Math::Cos(_rotation), -Math::Sin(_rotation)); }

	std::shared_ptr<TransformComponent>		GetTransformComponent();
	std::shared_ptr<SpriteComponent>		GetSpriteComponent();
	std::shared_ptr<CircleComponent>		GetCircleComponent();
	std::shared_ptr<BoxComponent>			GetBoxComponent();
	std::shared_ptr<FollowCameraComponent>	GetFollowCameraComponent();
	std::shared_ptr<GridComponent>			GetGridComponent();

private:
	std::shared_ptr<Component>				GetComponent(ComponentType type);

private:
	//	TEMP : Class Name
	std::wstring			_name;

	//	Enum
	Protocol::ActorType		_type = Protocol::ActorType::ACTOR_TYPE_MONSTER;
	//Protocol::ActorState	_state = Protocol::ActorState::ACTOR_STATE_NONE;
	Protocol::MoveDir		_dir = Protocol::MoveDir::MOVE_DIR_NONE;

	//	Grid Position
	Protocol::PositionInfo* _positionInfo = nullptr;

	int32			_actorId = 0;
	Vector2			_position;
	float			_scale{ 1.f };
	float			_rotation{ 0.f };
	ActorState		_state = ActorState::Active;

	std::array<std::shared_ptr<Component>, COMPONENT_COUNT> _components;
};
