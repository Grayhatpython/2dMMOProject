#pragma once

class Actor;
class PlayScene;
class UIScreen;
class FollowActor;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene(SceneType type);
	virtual ~Scene();

public:
	virtual void Initialize();
	virtual void ProcessInput();
	virtual void HandleKeyPress();
	virtual void Update();
	virtual void Clear();

public:
	void AddActor(std::shared_ptr<Actor> actor);
	void RemoveActor(std::shared_ptr<Actor> actor);

	//	TEMP
	void PushUI(std::shared_ptr<UIScreen> ui);

protected:
	virtual void OnAddActor(std::shared_ptr<Actor> actor);

public:

	SceneType		GetSceneType() { return _type; }

	GameState						GetState() { return _state; }
	void							SetState(GameState state) { _state = state; }

	const std::shared_ptr<FollowActor>&				GetCamera() { return _camera; }
	const std::vector<std::shared_ptr<Actor>>&		GetActors() { return _actors; }
	const std::vector<std::shared_ptr<UIScreen>>&	GetUis() { return _uis; }

	std::shared_ptr<PlayScene>						GetPlayScene();

protected:
	GameState									_state = GameState::Play;
	SceneType									_type = SceneType::None;

	std::shared_ptr<FollowActor>				_camera;

	std::vector<std::shared_ptr<Actor>>			_actors;
	std::vector<std::shared_ptr<Actor>>			_pendingActors;
	bool										_updatingActors = false;

	std::vector<std::shared_ptr<UIScreen>>		_uis;
};