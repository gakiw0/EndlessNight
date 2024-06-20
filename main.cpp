// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/LoseScene.hpp"

#include <iostream>

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();


	game.AddNewScene("play", new PlayScene());	
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("lose", new LoseScene());
	//game.AddNewScene("Lose", new PlayScene());

	game.Start("play", 60, 1600, 832);
	
	return 0;
}
