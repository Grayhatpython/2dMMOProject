#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

public:
	//	TEMP
	virtual void	Initialize() override;
	virtual void	ProcessInput() override;
	virtual void	HandleKeyPress() override;
	virtual void	Update() override;
	virtual void	Clear() override;

	//	TODO
public:
	void OnConnected();
	void OnConnectFailed();

public:
	TitleSceneState		GetTitleSceneState() { return _state; }
	void				SetTitleSceneState(TitleSceneState state) { _state = state; }

private:
	TitleSceneState		_state = TitleSceneState::None;
};
