// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/StartScene.h"
#include "Scene/PlayScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/StoryScene.hpp"
#include "Scene/ScoreBoardScene.hpp"
#include "Scene/LoginOrRegisterScene.hpp"
#include "Scene/LoginScene.hpp"
#include "Scene/RegisterScene.hpp"
#include "Engine/AudioHelper.hpp"
#include <allegro5/allegro_audio.h>


#include <iostream>

ALLEGRO_SAMPLE* startBGM = nullptr;
ALLEGRO_SAMPLE* playBGM = nullptr;

int main(int argc, char **argv)
{
	Engine::LOG::SetConfig(true);
	Engine::GameEngine &game = Engine::GameEngine::GetInstance();
	
	game.AddNewScene("story", new StoryScene());
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("scoreboard", new ScoreBoardScene());
	game.AddNewScene("loginOrRegister", new LoginOrRegisterScene());
	game.AddNewScene("login", new LoginScene());
	game.AddNewScene("register", new RegisterScene());

	game.Start("loginOrRegister", 60, 1600, 832);

	return 0;
}
