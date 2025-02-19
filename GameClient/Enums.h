#pragma once
#include <Types.h>
#include "Math.h"

namespace Enums
{
#pragma region Component

	enum class ComponentType : uint8
	{
		Transform,
		AI,
		Nav,
		Move,
		Input,
		Box,
		Circle,
		Sprite,
		AnimSingleSprite,
		AnimMultipleSprite,
		Camera,
		FollowCamera,
		Grid,
		End,
	};

	enum
	{
		COMPONENT_COUNT = static_cast<uint8>(ComponentType::End),
	};

#pragma endregion

#pragma region Actor

	enum class ActorState
	{
		Active,
		Paused,
		Dead
	};

	enum class TileState
	{
		Default,
		Path,
		Start,
		Base
	};

#pragma endregion

#pragma region Scene
	
	enum class SceneType
	{
		None,
		Title,
		Play,
	};

	enum class GameState
	{
		Play,
		Paused,
		Quit,
	};

	enum class TitleSceneState
	{
		None,
		AssetLoading,
		AssetLoaded,
		ConnectingToServer,
		ConnectedToServer,
		FailedToConnectToServer,
	};

#pragma endregion

#pragma region Input

	enum class ButtonState
	{
		None,
		Pressed,
		Released,
		Held
	};

#pragma endregion

#pragma region Physics

	enum class CollisionLayer
	{
		None = 0,
		Laser = 1 << 0,  // 0001
		Asteroid = 1 << 1, // 0010
	};

#pragma endregion

#pragma region Ui

	enum class UIState
	{
		Active,
		Close
	};

#pragma endregion

#pragma region Network

	enum class ServerType
	{
		GameServer = 0,
	};

#pragma endregion

}

namespace Color
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}
