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
#include "Engine/AutoScroller.hpp"

#define move 25

void StartScene::Initialize()
{
   int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
   int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
   int halfW = w / 2;
   int halfH = h / 2;

   background = new AutoScroller("stage-select/moon.png", 60.0f);
   // AddNewObject(background);
   background->SetZoom(1.0f);

   std::vector<std::string> imagePaths = {
       "StartZombie/pixil-frame-0.png",
       "StartZombie/pixil-frame-1.png",
       "StartZombie/pixil-frame-2.png",
       "StartZombie/pixil-frame-3.png"};

   for (const auto &path : imagePaths)
   {
      auto img = std::make_shared<Engine::Image>(path, halfW, halfH + 275, 0, 0, 0.5f, 0.5f, 2.0f, 2.0f);
      zombieFrames.push_back(img);
   }

   title1 = new Engine::Image("stage-select/title.png", halfW - 300, 20, 600, 300);
   AddNewObject(title1);

   btn1 = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW, halfH + 50, 450, 150, 0.5, 0.5);
   btn1->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
   AddNewControlObject(btn1);

   play = new Engine::Label("Play", "pirulen.ttf", 48, halfW, halfH + 50, 255, 255, 255, 255, 0.5, 0.5);
   AddNewObject(play);

   // border = new Engine::Image("stage-select/border.png", w - 96, 32);
   // AddNewObject(border);

   btn = new Engine::ImageButton("stage-select/settings3.png", "stage-select/settings4.png", w - 10, 10, 64, 64, 1, 0);
   btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
   AddNewControlObject(btn);

   btn2 = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", w - 10, h - 80, 192, 64, 1, 0);
   btn2->SetOnClickCallback(std::bind(&StartScene::LogoutOnClick, this, 3));
   AddNewControlObject(btn2);

   btn3 = new Engine::ImageButton("settings/score1.png", "settings/score2.png", w - 84, 10, 64, 64, 1, 0);
   btn3->SetOnClickCallback(std::bind(&StartScene::ScoreBoardOnClick, this, 4));
   AddNewControlObject(btn3);

   logout = new Engine::Label("Logout", "pirulen.ttf", 24, w - 105, h - 50, 255, 255, 255, 255, 0.5, 0.5);
   AddNewObject(logout);
}

void StartScene::Update(float deltaTime)
{

   animationTime += deltaTime;
   if (animationTime >= 0.2f)
   { // Change frame every frameDuration seconds
      currentFrame = (currentFrame + 1) % zombieFrames.size();
      animationTime = 0.0f;
   }
   background->Update(deltaTime);
   // float zoomFactor = 1.0f + 0.2f * sin(al_get_time());
   // background->SetZoom(zoomFactor);
}

void StartScene::Draw() const
{
   IScene::Draw();
   background->Draw();
   title1->Draw();
   if (!zombieFrames.empty())
   {
      zombieFrames[currentFrame]->Draw();
   }

   btn1->Draw();
   play->Draw();
   btn->Draw();
   btn2->Draw();
   btn3->Draw();
   logout->Draw();
}

void StartScene::Terminate()
{
   delete background;
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

void StartScene::ScoreBoardOnClick(int stage)
{
   Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}

void StartScene::OnMouseDown(int button, int mx, int my)
{
   IScene::OnMouseDown(button, mx, my);
}

void StartScene::LogoutOnClick(int stage)
{
   User::getInstance().setName("");
   User::getInstance().setPassword("");
   Engine::GameEngine::GetInstance().ChangeScene("loginOrRegister");
}
