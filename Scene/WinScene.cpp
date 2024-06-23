#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <functional>
#include <string>
#include <fstream>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Text.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "Engine/Resources.hpp"
#include "Engine/User.hpp"


void WinScene::Initialize()
{
	finalScore = User::getInstance().getScore();
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	tempscore = 0;

	// AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	//AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
	// AddNewObject(new Engine::Label("Enter Your Name", "pirulen.ttf", 30, halfW, halfH / 4 + 66 + 300, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label("Score", "pirulen.ttf", 30, halfW, halfH / 4 + 135, 255, 255, 255, 255, 0.5, 0.5));

	scoreLabel = new Engine::Label("", "pirulen.ttf", 72, halfW, halfH / 4 + 200, 255, 255, 255, 255, 0.5, 0.5);
	AddNewObject(scoreLabel);
	scoreLabel->Text = std::to_string(tempscore);
	

	Engine::ImageButton *btn;
	btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 187.5, halfH * 6 / 4 - 75, 375, 151.875);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 6 / 4, 255, 255, 255, 255, 0.5, 0.5));

	bgmId = AudioHelper::PlayAudio("win.wav");

	playerNameLabel = new Engine::Label("", "pirulen.ttf", 36, halfW, halfH + 150, 255, 255, 255, 255, 0.5, 0.5);
	AddNewObject(playerNameLabel);
}

void WinScene::Terminate()
{
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}

void WinScene::Update(float deltaTime)
{
	ticks += deltaTime;
	// if (ticks > 4 && ticks < 100 &&
	// 	 dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2)
	// {
	// 	ticks = 100;
	// 	bgmId = AudioHelper::PlayBGM("happy.ogg");
	// }
	// printf("l");
	if (tempscore < finalScore)
	{
		// printf("k");
		tempscore += 10;
		scoreLabel->Text = std::to_string(tempscore);
	}
	else
		scoreLabel->Text = std::to_string(finalScore);

}
void WinScene::BackOnClick(int stage)
{
	Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}

// void WinScene::TextClick()
// {

// }

void WinScene::Draw() const
{
	IScene::Draw();
}

// std::string WinScene::GetCurrentDateTime()
// {
// 	// 1. Get current time point
// 	auto now = std::chrono::system_clock::now();

// 	// 2. Get time_t for the date and time
// 	std::time_t t = std::chrono::system_clock::to_time_t(now);
// 	std::tm *nowTM = std::localtime(&t);

// 	// 3. Create a stringstream to format the output
// 	std::stringstream ss;

// 	// Format the date and time up to minutes
// 	ss << std::put_time(nowTM, "%Y-%m-%d/%H:%M");

// 	return ss.str();
// }

// void WinScene::SaveScoreToFile(const std::string &name, int score)
// {
// 	std::string date = GetCurrentDateTime();
// 	std::ofstream file("Resource/scoreboard.txt", std::ios::app);
// 	if (file.is_open())
// 	{
// 		file << name << " " << finalScore << " " << date << "\n";
// 		file.close();
// 	}

// 	std::ofstream file1("../Resource/scoreboard.txt", std::ios::app);
// 	if (file1.is_open())
// 	{
// 		file1 << name << " " << finalScore << " " << date << "\n";
// 		file1.close();
// 	}
// }

void WinScene::OnMouseDown(int button, int mx, int my)
{
	IScene::OnMouseDown(button, mx, my);
}

void WinScene::OnMouseMove(int mx, int my)
{
	IScene::OnMouseMove(mx, my);
}

void WinScene::OnMouseUp(int button, int mx, int my)
{
	IScene::OnMouseUp(button, mx, my);
}
// void WinScene::OnKeyDown(int keyCode)
// {
// 	IScene::OnKeyDown(keyCode);
// 	if (!input->clicked)
// 		return;
// 	switch (keyCode)
// 	{
// 	case ALLEGRO_KEY_SPACE:
// 		break;
// 	case ALLEGRO_KEY_ENTER:
// 		drawTextInputBox = false;
// 		SaveScoreToFile(playerName, finalScore);
// 		Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
// 		break;
// 	case ALLEGRO_KEY_BACKSPACE:
// 		if (!playerName.empty())
// 		{
// 			playerName.pop_back();
// 		}
// 		playerNameLabel->Text = playerName;
// 		break;
// 	default:
// 		if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z)
// 		{
// 			// std::cout << "lol" << std::endl;
// 			const char *keyName = al_keycode_to_name(keyCode);
// 			// std::cout << keyName << std::endl;
// 			if (playerName.size() < 8)
// 			{
// 				playerName += keyName;
// 				// std::cout << playerName << std::endl;
// 			}
// 			playerNameLabel->Text = playerName;
// 			break;
// 		}
// 	}
// }
