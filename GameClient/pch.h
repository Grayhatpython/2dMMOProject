#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

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
#include "Protocol.pb.h"

#include "Enums.h"
#include "Math.h"

using namespace Enums;

using ServerSessionRef = std::shared_ptr<class ServerSession>;
using ServerInstanceRef = std::shared_ptr<class ServerInstance>;
using PacketMessageRef = std::shared_ptr<struct PacketMessage>;
using PacketQueueRef = std::shared_ptr<class PacketQueue>;
