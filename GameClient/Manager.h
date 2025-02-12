#pragma once

#include "TimeManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"

class Manager
{
private:
	Manager() {};

public:
	//	TODO
	static Manager* GetInstance()
	{
		std::call_once(S_InitFlag, []() {
			S_Instance = std::unique_ptr<Manager>(new Manager());
			});
		return S_Instance.get();
	}

	static TimeManager* GetTimeManager() { return GetInstance()->_time.get(); }
	static SceneManager* GetSceneManager() { return GetInstance()->_scene.get(); }
	static RenderManager* GetRenderManager() { return GetInstance()->_render.get(); }
	static AssetManager* GetAssetManager() { return GetInstance()->_asset.get(); }
	static InputManager* GetInputManager() { return GetInstance()->_input.get(); }
	static PhysicsManager* GetPhysicsManager() { return GetInstance()->_physics.get(); }

public:
	void Initialize();
	void Clear();

public:
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;

private:
	static std::unique_ptr<Manager> S_Instance;
	static std::once_flag			S_InitFlag;

	std::unique_ptr<TimeManager>		_time;
	std::unique_ptr<SceneManager>		_scene;
	std::unique_ptr<RenderManager>		_render;
	std::unique_ptr<AssetManager>		_asset;
	std::unique_ptr<InputManager>		_input;
	std::unique_ptr<PhysicsManager>		_physics;
};

