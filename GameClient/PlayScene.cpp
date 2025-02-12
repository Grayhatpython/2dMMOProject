#include "pch.h"
#include "PlayScene.h"
#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Enemy.h"
#include "Manager.h"
#include "Grid.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "InputComponent.h"
#include "BoxComponent.h"
#include "UIPauseMenu.h"
#include "UIScreen.h"
#include "UIDialog.h"
#include "FollowActor.h"
#include "FollowCameraComponent.h"

PlayScene::PlayScene()
	: Scene(SceneType::Play)
{

}

PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	Scene::Initialize();

	_grid = std::make_shared<Grid>();
	_grid->Initialize();

	AddActor(_grid);
	
	Manager::GetAssetManager()->LoadText("../Common/Assets/English.gptext");

	{
		std::shared_ptr<Ship> ship = std::make_shared<Ship>();
		std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();
		ship->AddComponent(sc);
		ship->SetPosition(Vector2(704.f, 384.0f));

		sc->SetTexture("../Common/Assets/Ship.png");

		std::shared_ptr<InputComponent> ic = std::make_shared<InputComponent>();
		ship->AddComponent(ic);

		ic->SetForwardKey(SDL_SCANCODE_W);
		ic->SetBackKey(SDL_SCANCODE_S);
		ic->SetClockwiseKey(SDL_SCANCODE_A);
		ic->SetCounterClockwiseKey(SDL_SCANCODE_D);

		_camera->SetTarget(ship);

		AddActor(ship);
	}

	// Create asteroids
	for (int i = 0; i < 1; i++)
	{
		std::shared_ptr<Asteroid> as = std::make_shared<Asteroid>();
		Vector2 randPos = Random::GetRandomVector(Vector2(0.f,0.0f),Vector2(512.0f, 384.0f));
		as->SetPosition(randPos);
		as->SetRotation(Random::GetRandom(0.0f, Math::TwoPi));

		std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();
		as->AddComponent(sc);

		sc->SetTexture("../Common/Assets/Asteroid.png");
		std::shared_ptr<BoxComponent> bc = std::make_shared<BoxComponent>();
		as->AddComponent(bc);

		bc->SetCollisionLayer(CollisionLayer::Asteroid);
		bc->SetCollisionMask(static_cast<int32>(CollisionLayer::Laser));

		AddActor(as);
		_asteroids.push_back(as);
	}
}

void PlayScene::ProcessInput()
{
	//if (state[SDL_SCANCODE_B])
	//	_grid->BuildTower();

	//// Process mouse
	//int x, y;
	//Uint32 buttons = SDL_GetMouseState(&x, &y);
	//if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	//	_grid->ProcessClick(x, y);

	Scene::ProcessInput();
}

void PlayScene::HandleKeyPress()
{
	/*
	const auto& state = Manager::GetInputManager()->GetState();

	if (state.keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		std::shared_ptr<UIPauseMenu> pauseMenu = std::make_shared<UIPauseMenu>();
		PushUI(pauseMenu);

		pauseMenu->SetFont(Manager::GetAssetManager()->GetFont("../Common/Assets/Carlito-Regular.ttf"));
		pauseMenu->SetButtonOnTexture(Manager::GetAssetManager()->GetTexture("../Common/Assets/ButtonYellow.png"));
		pauseMenu->SetButtonOffTexture(Manager::GetAssetManager()->GetTexture("../Common/Assets/ButtonBlue.png"));

		//pauseMenu->SetRelativeMouseMode(false);
		pauseMenu->SetTitle("PauseTitle");

		std::weak_ptr<UIPauseMenu> pauseMenuPtr = pauseMenu;
		pauseMenu->AddButton("ResumeButton", [pauseMenuPtr]() {
			if (auto pauseMenu = pauseMenuPtr.lock()) { // weak_ptr이 살아있는지 확인 후 shared_ptr로 변환
				pauseMenu->Close();
			}
		});

		pauseMenu->AddButton("QuitButton", []() {
			std::shared_ptr<UIDialog> dialog = std::make_shared<UIDialog>();
			Manager::GetSceneManager()->GetCurrentScene()->PushUI(dialog);

			dialog->SetFont(Manager::GetAssetManager()->GetFont("../Common/Assets/Carlito-Regular.ttf"));
			dialog->SetButtonOnTexture(Manager::GetAssetManager()->GetTexture("../Common/Assets/ButtonYellow.png"));
			dialog->SetButtonOffTexture(Manager::GetAssetManager()->GetTexture("../Common/Assets/ButtonBlue.png"));

			dialog->SetBackGroundPosition(Vector2(0.0f, 0.0f));
			dialog->SetTitlePosition(Vector2(0.0f, 100.0f));
			dialog->SetNextButtonPosition(Vector2(0.0f, 0.0f));

			dialog->SetBackGroundTexture(Manager::GetAssetManager()->GetTexture("../Common/Assets/DialogBG.png"));
			dialog->SetTitle("QuitText", Vector3::Zero, 30);

			dialog->AddButton("OKButton", []() {
				Manager::GetSceneManager()->GetCurrentScene()->SetState(GameState::Quit);
			});

			std::weak_ptr<UIDialog> dialogPtr = dialog;
			dialog->AddButton("CancelButton", [dialogPtr]() {
				if (auto dialog = dialogPtr.lock()) { // weak_ptr이 살아있는지 확인 후 shared_ptr로 변환
					dialog->Close();
				}
				});
		});

		SetState(GameState::Paused);
	}
	*/
}

void PlayScene::Update()
{
	Scene::Update();

	//	TEMP :: _grid

	_asteroids.erase(std::remove_if(_asteroids.begin(), _asteroids.end(),
		[](const std::shared_ptr<Asteroid>& actor) {
			return actor->GetState() == ActorState::Dead;
		}),
		_asteroids.end());
}

void PlayScene::Clear()
{
	_grid.reset();
	_enemies.clear();

	Scene::Clear();
}

void PlayScene::OnAddActor(std::shared_ptr<Actor> actor)
{
	//if (actor->GetName() == L"Enemy")
	//	_enemies.push_back(std::static_pointer_cast<Enemy>(actor));
	if (actor->GetName() == L"_asteroids")
		_asteroids.push_back(std::static_pointer_cast<Asteroid>(actor));
}

std::shared_ptr<Enemy> PlayScene::GetNearestEnemy(const Vector2& position)
{
	std::shared_ptr<Enemy> best = nullptr;

	if (_enemies.size() > 0)
	{
		best = _enemies[0];
		// Save the distance squared of first enemy, and test if others are closer
		float bestDistSq = (position - _enemies[0]->GetPosition()).LengthSq();
		for (size_t i = 1; i < _enemies.size(); i++)
		{
			float newDistSq = (position - _enemies[i]->GetPosition()).LengthSq();
			if (newDistSq < bestDistSq)
			{
				bestDistSq = newDistSq;
				best = _enemies[i];
			}
		}
	}

	return best;
}
