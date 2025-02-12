#pragma once

class Scene;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	void ProcessInput();
	void Update();
	void Clear();

public:
	const std::shared_ptr<Scene>&		GetCurrentScene() { return _currentScene; }
	


	void								SetCurrentScene(std::shared_ptr<Scene> gameScene);

private:
	std::shared_ptr<Scene>				_currentScene = nullptr;
};