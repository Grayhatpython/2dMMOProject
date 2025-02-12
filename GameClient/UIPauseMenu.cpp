#include "pch.h"
#include "UIPauseMenu.h"
#include "UIDialog.h"
#include "Game.h"
#include "Manager.h"
#include "Scene.h"

UIPauseMenu::UIPauseMenu()
{
	Manager::GetSceneManager()->GetCurrentScene()->SetState(GameState::Paused);
}

UIPauseMenu::~UIPauseMenu()
{
	//SetRelativeMouseMode(true);
	Manager::GetSceneManager()->GetCurrentScene()->SetState(GameState::Play);
}

void UIPauseMenu::HandleKeyPress()
{
	UIScreen::HandleKeyPress();

	const auto& state = Manager::GetInputManager()->GetState();

	if (state.keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		Close();
	}
}
