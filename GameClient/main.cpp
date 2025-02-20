#include "pch.h"
#include <iostream>
#include "ThreadManager.h"
#include "Service.h"
#include "ServerSession.h"
#include "ServerPacketHandler.h"
#include "Game.h"
#include <XmlParser.h>

#undef main

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{

	//
	XmlNode root;
	XmlParser parser;
	if (parser.ParseFromFile(L"../Common/Data/Map/grid.tmx", OUT root) == false)
		return 0;

	{
		//	Grid Info
		int32 tileColumns = root.GetInt32Attr(L"width");
		int32 tileRows = root.GetInt32Attr(L"height");
		int32 tileSize = root.GetInt32Attr(L"tilewidth");
		int32 tileSpriteColumnCount = 0;

		Vector<XmlNode> tilesets = root.FindChildren(L"tileset");
		for (XmlNode& tileset : tilesets)
			tileSpriteColumnCount = tileset.GetInt32Attr(L"columns");

		std::vector<Vector2Int> collisionArray;

		Vector<XmlNode> layers = root.FindChildren(L"layer");
		for (XmlNode& layer : layers)
		{
			std::vector<std::vector<int>> array(tileRows, std::vector<int>(tileColumns, 0));

			wstring data = layer.FindChild(L"data").GetStringValue();
			wstring name = layer.GetStringAttr(L"name");

			// 숫자 추출 및 2D 배열에 저장
			size_t pos = 0, row = 0, col = 0;
			while (pos < data.length() && row < tileRows) {
				size_t next_pos = data.find(L",", pos);
				if (next_pos == std::wstring::npos) next_pos = data.length();

				int num = std::stoi(data.substr(pos, next_pos - pos));  // 문자열 → 정수 변환

				if (name == L"CollisionLayer" && num > 0)
					collisionArray.push_back(Vector2Int(row, col));
				else
					array[row][col] = num;

				col++;
				if (col >= tileColumns) {
					col = 0;
					row++;
				}

				pos = next_pos + 1;  // 다음 숫자로 이동
			}
		}

		int a = 3;
	}

	std::this_thread::sleep_for(1s);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(6610);
	std::cout.imbue(std::locale(""));
	std::wcout.imbue(std::locale(""));

	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.Run();
	}

	game.Shutdown();

	system("pause");
	return 0;
}