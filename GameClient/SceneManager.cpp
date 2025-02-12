#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::SetCurrentScene(std::shared_ptr<Scene> gameScene)
{
	Clear();

	_currentScene = gameScene;
	_currentScene->Initialize();
}

void SceneManager::ProcessInput()
{
	if(_currentScene)
		_currentScene->ProcessInput();
}

void SceneManager::Update()
{
	if(_currentScene)
		_currentScene->Update();

}

void SceneManager::Clear()
{
	if (_currentScene)
		_currentScene->Clear();
}

