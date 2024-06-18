#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

struct ScoreEntry {
    std::string name;
    int score;
	 std::string date;
};

const int SCORES_PER_PAGE = 10; // Adjust as needed

class ScoreBoardScene final : public Engine::IScene
{
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
	std::vector<ScoreEntry> scores;
	int currentPage;
	int totalPages;
	std::vector<Engine::Label*> scoreLabels; // Track score labels for clearing
public:
	explicit ScoreBoardScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int stage);
	std::vector<ScoreEntry> ReadScores(const std::string& filename);
   void ShowPage(int page);
   void NextPageOnClick();
   void PrevPageOnClick();
	void ClearScoreLabels();
};

#endif // SCOREBOARDSCENE_HPP