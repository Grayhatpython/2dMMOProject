#pragma once
#include <SDL/SDL.h>

class Texture;
class Font;
class AssetManager
{
public:
	~AssetManager();

public:
	std::shared_ptr<Texture>		GetTexture(const std::string& fileName);
	std::shared_ptr<Font>			GetFont(const std::string& fileName);

	void							LoadText(const std::string& fileName);
	const std::string&				GetText(const std::string& key);

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>>	_textures;
	std::unordered_map<std::string, std::shared_ptr<Font>>		_fonts;
	std::unordered_map<std::string, std::string>				_texts;
};

