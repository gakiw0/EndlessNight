#include "StartScene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"

#define move 25

void StartScene::Initialize()
{
   int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
   int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
   int halfW = w / 2;
   int halfH = h / 2;

   std::vector<std::string> imagePaths = {
       "StartZombie/pixil-frame-0.png",
       "StartZombie/pixil-frame-1.png",
       "StartZombie/pixil-frame-2.png",
       "StartZombie/pixil-frame-3.png"};

   for (const auto &path : imagePaths)
   {
      auto img = std::make_shared<Engine::Image>(path, halfW, halfH / 2 + 48, 0, 0, 0.5f, 0.5f, 2.5f, 2.5f);
      zombieFrames.push_back(img);
   }

   btn1 = new Engine::ImageButton("stage-select/mainbutton.png", "stage-select/mainbutton2.png", halfW - 281, halfH / 2 + 110, 562, 220);
   btn1->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
   AddNewControlObject(btn1);

   play = new Engine::Label("Play", "pirulen.ttf", 96, halfW, halfH / 2 + 196, 0, 0, 0, 255, 0.5, 0.5);
   AddNewObject(play);

   //border = new Engine::Image("stage-select/border.png", w - 96, 32);
   //AddNewObject(border);

   btn = new Engine::ImageButton("stage-select/settings3.png", "stage-select/settings4.png", w - 96, 32, 64, 64);
   btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
   AddNewControlObject(btn);

   // settings = new Engine::Label("Settings", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 25 - move, 0, 0, 0, 255, 0.5, 0.5);
   // AddNewObject(settings);
}

void StartScene::Update(float deltaTime)
{

   animationTime += deltaTime;
   if (animationTime >= 0.2f)
   { // Change frame every frameDuration seconds
      currentFrame = (currentFrame + 1) % zombieFrames.size();
      animationTime = 0.0f;
   }
}

void StartScene::Draw() const
{
   IScene::Draw();
   if (!zombieFrames.empty())
   {
      zombieFrames[currentFrame]->Draw();
   }

   btn1->Draw();
   play->Draw();
   //border->Draw();
   btn->Draw();
}

void StartScene::Terminate()
{
   IScene::Terminate();
   // ZombieAnimation's destructor will handle frame cleanup
}

void StartScene::PlayOnClick(int stage)
{
   Engine::GameEngine::GetInstance().ChangeScene("play");
}

void StartScene::SettingsOnClick(int stage)
{
   Engine::GameEngine::GetInstance().ChangeScene("settings");
}

void StartScene::OnMouseDown(int button, int mx, int my)
{
   IScene::OnMouseDown(button, mx, my);
}

