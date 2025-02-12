#include "pch.h"
#include "AssetManager.h"
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

#include "Font.h"
#include "Manager.h"
#include "Texture.h"

AssetManager::~AssetManager()
{
	_textures.clear();
}

std::shared_ptr<Texture> AssetManager::GetTexture(const std::string& fileName)
{
	std::shared_ptr<Texture> texture = nullptr;
	// Is the texture already in the map?
	auto iter = _textures.find(fileName);
	if (iter != _textures.end())
		texture = iter->second;
	else
	{
		texture = std::make_shared<Texture>();
		if (texture->Load(fileName) == false)
			return nullptr;

		_textures.insert(std::make_pair(fileName.c_str(), texture));
	}

	return texture;
}

std::shared_ptr<Font> AssetManager::GetFont(const std::string& fileName)
{
	auto iter = _fonts.find(fileName);
	if (iter != _fonts.end())
		return iter->second;
	else
	{
		std::shared_ptr<Font> font = std::make_shared<Font>();
		if (font->Load(fileName))
			_fonts.insert(std::make_pair(fileName, font));
		else
		{
			font->Clear();
			font = nullptr;
		}

		return font;
	}
}

void AssetManager::LoadText(const std::string& fileName)
{
	_texts.clear();

	std::ifstream file(fileName);
	if (file.is_open() == false)
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();

	std::string contents = fileStream.str();

	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	if (doc.IsObject() == false)
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}

	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin(); itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
			_texts.insert(std::make_pair(itr->name.GetString(),itr->value.GetString()));
	}
}

const std::string& AssetManager::GetText(const std::string& key)
{
	static std::string errorMsg("Not Found Key Text");

	auto iter = _texts.find(key);
	if (iter != _texts.end())
		return iter->second;
	else
		return errorMsg;
}
