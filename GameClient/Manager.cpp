#include "pch.h"
#include "Manager.h"
#include "Random.h"

std::unique_ptr<Manager>	Manager::S_Instance = nullptr;
std::once_flag				Manager::S_InitFlag;

void Manager::Initialize()
{
    Random::Initialize();

    _time = std::make_unique<TimeManager>();
    _scene = std::make_unique<SceneManager>();
    _render = std::make_unique<RenderManager>();
    _asset = std::make_unique<AssetManager>();
    _input = std::make_unique<InputManager>();
    _physics = std::make_unique<PhysicsManager>();

    _time->Initialize();
    _input->Initialize();
}

void Manager::Clear()
{
    if (S_Instance)
    {
        S_Instance->_time.reset();      //  TimeManager ����
        S_Instance->_scene->Clear();    //  TODO
        S_Instance->_scene.reset();     //  SceneManager ����
        S_Instance->_asset.reset();     //  AssetManager ����
        S_Instance->_render.reset();    //  RenderManager ����
        S_Instance->_input.reset();     //  InputManager ����
        S_Instance->_physics.reset();     //  PhysicsManager ����
        S_Instance.reset();             //  Manager ����
    }
}
