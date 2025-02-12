#include "pch.h"
#include "Tile.h"
#include "SpriteComponent.h"
#include "Manager.h"

Tile::Tile()
	: Actor(L"Tile")
{

}

void Tile::SetTileState(TileState state)
{
	_tileState = state;
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	_selected = !_selected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string filename;
	switch (_tileState)
	{
	case TileState::Start:
		filename = "../Common/Assets/TileTan.png";
		break;
	case TileState::Base:
		filename = "../Common/Assets/TileGreen.png";
		break;
	case TileState::Path:
		if (_selected)
			filename = "../Common/Assets/TileGreySelected.png";
		else
			filename = "../Common/Assets/TileGrey.png";
		break;
	case TileState::Default:
	default:
		if (_selected)
			filename = "../Common/Assets/TileBrownSelected.png";
		else
			filename = "../Common/Assets/TileBrown.png";
		break;
	}

	auto spriteComponent = GetSpriteComponent();
	ASSERT_CRASH(spriteComponent);

	spriteComponent->SetTexture(filename);
}

