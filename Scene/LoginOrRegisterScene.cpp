#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "LoginOrRegisterScene.hpp"
#include "UI/Component/TextInput.hpp"

void LoginOrRegisterScene::Initialize()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    AddNewObject(new Engine::Label("Endless Nights", "pirulen.ttf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 200, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginOrRegisterScene::LoginOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("LOGIN", "pirulen.ttf", 48, halfW, halfH / 2 + 250, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginOrRegisterScene::RegisterOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("REGISTER", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
}
void LoginOrRegisterScene::Terminate()
{
    IScene::Terminate();
}
void LoginOrRegisterScene::LoginOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("login");
}
void LoginOrRegisterScene::RegisterOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("register");
}