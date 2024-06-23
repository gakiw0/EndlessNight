#ifndef ScoreBoardScene_HPP
#define ScoreBoardScene_HPP

#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"

struct ScoreData
{
	std::string userName;
	int score;
	std::chrono::system_clock::time_point date;
};

class ScoreBoardScene final : public Engine::IScene
{
private:
	int displayStart;
	int numMap;
	int currMap;

public:
	Engine::Label *UITitle;
	std::vector<std::vector<ScoreData>> scoreboards;
	std::vector<Engine::Label *> scoreboardLabels;

	explicit ScoreBoardScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int stage);
	void ReadScoreBoards();
	void PrevPageOnClick();
	void NextPageOnClick();
	void PrevMapOnClick();
	void NextMapOnClick();
	void UpdateScoreBoardDisplay();
};

#endif // ScoreBoardScene_HPP