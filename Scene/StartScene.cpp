//
// Created by Hsuan on 2024/4/10.
//

#include "StartScene.h"
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
#include "Scene/StartScene.h"
#include "Enemy/TankAnim.hpp"

#define move 25

void StartScene::Initialize()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    tankAnim = new TankAnim(-24, h);
    AddNewObject(tankAnim);
    
     
    
    
    // Engine::ImageButton *btn1;
    btn1 = new Engine::ImageButton("play/play2.png", "play/play5.png", halfW - 250, halfH / 2 + 150, 500, 200.25);
    btn1->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn1);

    play = new Engine::Label("Play", "pirulen.ttf", 48, halfW, halfH / 2 + 250, 0, 0, 0, 255, 0.5, 0.5);
    AddNewObject(play);

    btn = new Engine::ImageButton("play/play2.png", "play/play5.png", halfW - 250, halfH * 3 / 2 - 75 - move, 500, 200.25);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);

    settings = new Engine::Label("Settings", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 25 - move, 0, 0, 0, 255, 0.5, 0.5);
    AddNewObject(settings);

    // TankAnim::TankAnim* tankAnim;
}

void StartScene::Update(float deltaTime)
{
    tankAnim->Update(deltaTime);
}

void StartScene::Draw() const
{
    IScene::Draw();
    tankAnim->Draw();
    btn1->Draw();
    play->Draw();
    btn->Draw();
    settings->Draw();
}

void StartScene::Terminate()
{
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
    //Engine::GameEngine::GetInstance().ChangeScene("win");
}
void StartScene::SettingsOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}

void StartScene::OnMouseDown(int button, int mx, int my)
{
    IScene::OnMouseDown(button, mx, my);
    tankAnim->targetPosition = Engine::Point(mx, my);
}