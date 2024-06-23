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

    background = new AutoScroller("stage-select/moon.png", 60.0f);
    // AddNewObject(background);
    background->SetZoom(1.0f);

    title1 = new Engine::Image("stage-select/title.png", halfW - 300, 60, 600, 300);
    AddNewObject(title1);

    // AddNewObject(new Engine::Label("Endless Nights", "onesize.ttf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 200, halfH / 2 + 200, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginOrRegisterScene::LoginOnClick, this, 1));
    AddNewControlObject(btn);
    login = new Engine::Label("LOGIN", "onesize.ttf", 48, halfW, halfH / 2 + 250, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(login);

    btn1 = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn1->SetOnClickCallback(std::bind(&LoginOrRegisterScene::RegisterOnClick, this, 2));
    AddNewControlObject(btn1);
    register1 = new Engine::Label("REGISTER", "onesize.ttf", 48, halfW, halfH * 3 / 2, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(register1);
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

void LoginOrRegisterScene::Draw() const
{
    IScene::Draw();
    background->Draw();
    title1->Draw();
    btn1->Draw();
    btn->Draw();
    login->Draw();
    register1->Draw();
}

void LoginOrRegisterScene::Update(float deltaTime)
{
    background->Update(deltaTime);
}