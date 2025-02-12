#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#pragma comment(lib, "SDL\\x64\\SDL2.lib")
#pragma comment(lib, "SDL\\x64\\SDL2main.lib")
#pragma comment(lib, "SDL\\x64\\SDL2_ttf.lib")
#pragma comment(lib, "SDL\\x64\\SDL2_mixer.lib")
#pragma comment(lib, "SDL\\x64\\SDL2_image.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "CorePch.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

#include "Enums.h"
#include "Math.h"

using namespace Enums;