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

#include <iostream>

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

	std::vector<std::string> storyText = {
        "HOW LONG WILL THE NIGHT BE?",
        "NOW....",
		  "WHO KNOWS?"
    };
   game.AddNewScene("story", new StoryScene(storyText));
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());	
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("scoreboard", new ScoreBoardScene());
	game.Start("start", 60, 1600, 832);
	
	return 0;
}
