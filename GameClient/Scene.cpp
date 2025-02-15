#include "pch.h"
#include "Scene.h"
#include "Game.h"
#include "Actor.h"
#include "Manager.h"
#include "PlayScene.h"
#include "UIScreen.h"
#include "FollowActor.h"
#include "FollowCameraComponent.h"

Scene::Scene(SceneType type)
	: _type(type)
{

}

Scene::~Scene()
{

}

void Scene::Initialize()
{
	_camera = std::make_shared<FollowActor>();
	std::shared_ptr<FollowCameraComponent> fcc = std::make_shared<FollowCameraComponent>();
	_camera->AddComponent(fcc);
}

void Scene::ProcessInput()
{
	Manager::GetInputManager()->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_state = GameState::Quit;
			break;
		case SDL_MOUSEWHEEL:
			Manager::GetInputManager()->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	Manager::GetInputManager()->Update();

	//	Global Key 
	if (_state == GameState::Play)
		HandleKeyPress();
	else if (_uis.empty() == false)
		_uis.back()->HandleKeyPress();

	if (_state == GameState::Play)
	{
		_updatingActors = true;
		for (auto& actor : _actors)
		{
			if (actor->GetState() == ActorState::Active)
				actor->ProcessInput();
		}
		_updatingActors = false;
	}
	else if (_uis.empty() == false)
		_uis.back()->ProcessInput();
}

void Scene::HandleKeyPress()
{

}

void Scene::Update()
{
	_updatingActors = true;
	for (auto& actor : _actors)
		actor->Update();
	_updatingActors = false;

	if(_camera)
		_camera->Update();

	for (auto& pending : _pendingActors)
	{
		_actors.push_back(pending);
		OnAddActor(pending);
	}
	_pendingActors.clear();

	_actors.erase(std::remove_if(_actors.begin(), _actors.end(),
		[](const std::shared_ptr<Actor>& actor) {
			return actor->GetState() == ActorState::Dead;
		}),
		_actors.end());

	for (auto ui : _uis)
	{
		if (ui->GetState() == UIState::Active)
			ui->Update();
	}

	auto iter = _uis.begin();
	while (iter != _uis.end())
	{
		if ((*iter)->GetState() == UIState::Close)
			iter = _uis.erase(iter);
		else
			++iter;
	}
}

void Scene::Clear()
{
	_camera = nullptr;
	_actors.clear();
	_pendingActors.clear();
	_uis.clear();
}

void Scene::AddActor(std::shared_ptr<Actor> actor)
{
	// If we're updating actors, need to add to pending
	if (_updatingActors)
		_pendingActors.push_back(actor);
	else
	{
		_actors.push_back(actor);
		OnAddActor(actor);
	}
}

void Scene::RemoveActor(std::shared_ptr<Actor> actor)
{
	auto iter = std::find(_pendingActors.begin(), _pendingActors.end(), actor);
	if (iter != _pendingActors.end())
	{
		std::iter_swap(iter, _pendingActors.end() - 1);
		_pendingActors.pop_back();
	}

	iter = std::find(_actors.begin(), _actors.end(), actor);
	if (iter != _actors.end())
	{
		std::iter_swap(iter, _actors.end() - 1);
		_actors.pop_back();
	}
}

void Scene::PushUI(std::shared_ptr<UIScreen> ui)
{
	_uis.push_back(ui);
}

void Scene::OnAddActor(std::shared_ptr<Actor> actor)
{

}


std::shared_ptr<PlayScene> Scene::GetPlayScene()
{
	return std::static_pointer_cast<PlayScene>(shared_from_this()); 
}
