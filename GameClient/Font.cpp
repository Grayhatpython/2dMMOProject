#include "pch.h"
#include "Font.h"
#include "Texture.h"
#include "Manager.h"

Font::Font()
{
}

Font::~Font()
{
	Clear();
}

bool Font::Load(const std::string& fileName)
{
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = ::TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		_fonts.insert(std::make_pair(size, font));
	}

	return true;
}

void Font::Clear()
{
	for (auto& font : _fonts)
		::TTF_CloseFont(font.second);
}

std::shared_ptr<Texture> Font::RenderText(const std::string& textKey, const Vector3& color, int32 fontSize)
{
	std::shared_ptr<Texture> texture = nullptr;

	SDL_Color sdlColor;
	sdlColor.r = static_cast<uint8>(color.x * 255);
	sdlColor.g = static_cast<uint8>(color.y * 255);
	sdlColor.b = static_cast<uint8>(color.z * 255);
	sdlColor.a = 255;

	auto iter = _fonts.find(fontSize);
	if (iter != _fonts.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = Manager::GetAssetManager()->GetText(textKey);

		SDL_Surface* surf = ::TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			texture = std::make_shared<Texture>();
			texture->CreateTextureFromSurface(surf);
			::SDL_FreeSurface(surf);
		}
	}
	else
		SDL_Log("Point size %d is unsupported", fontSize);

	return texture;
}
