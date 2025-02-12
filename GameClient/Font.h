#pragma once
#include <SDL/SDL_ttf.h>

class Texture;
class Font
{
public:
	Font();
	~Font();

public:
	bool Load(const std::string& fileName);
	void Clear();

	std::shared_ptr<Texture> RenderText(const std::string& textKey, const Vector3& color = Color::White, int32 fontSize = 30);

private:
	std::unordered_map<int32, TTF_Font*>	_fonts;
};
