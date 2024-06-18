#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include <map>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/ImageButton.hpp"
#include "Turret/Turret.hpp"

// int Score = 0;

class Turret;
namespace Engine
{
	class Group;
	class Image;
	class Label;
	class Sprite;
} // namespace Engine

class PlayScene final : public Engine::IScene
{
private:
	enum TileType
	{
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
	};
	ALLEGRO_SAMPLE_ID bgmId;
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
	std::vector<Engine::ImageButton *> heartImages;

protected:
	int lives;
	int money;
	int SpeedMult;
	int score;

public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const float DangerTime;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	float ticks;
	float deathCountDown;
	// Map tiles.
	Group *TileMapGroup;
	Group *GroundEffectGroup;
	Group *DebugIndicatorGroup;
	Group *BulletGroup;
	Group *TowerGroup;
	Group *EnemyGroup;
	Group *EffectGroup;
	Group *UIGroup;
	Group *UILife;
	Group *UIStar;
	Engine::Label *UIScore;
	Engine::Label *UIMoney;
	Engine::Label *UILives;
	Engine::Image *imgTarget;
	Engine::Sprite *dangerIndicator;
	Turret *preview;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<TileType>> oldmapState;
	std::vector<std::vector<Engine::ImageButton>> LifeUI;
	std::vector<std::vector<int>> mapDistance;
	std::list<std::pair<int, float>> enemyWaveData;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	void Hit();
	void Score(int scores);
	int GetMoney() const;
	void EarnMoney(int money);
	void ReadMap();
	void ReadEnemyWave();
	void ConstructUI();
	void UIBtnClicked(int id);
	bool CheckSpaceValid(int x, int y);
	std::vector<std::vector<int>> CalculateBFSDistance();
	std::map<Turret*, std::vector<Engine::Image*>> turretStars;
	// void ModifyReadMapTiles();
	void AddUpgradeStar(Turret* turret);
	void PauseGame();
	bool isPaused;
	Engine::ImageButton* pauseButton;
	int previousSpeedMult;
};
#endif // PLAYSCENE_HPP
