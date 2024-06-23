#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include "Engine/IScene.hpp"
#include "Player/Player.hpp"
#include "UI/Component/Label.hpp"
#include "Bullet/Bullet.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/ImageButton.hpp"
#include "Engine/Animation.hpp"
#include "UI/Component/MiniMap.hpp"
#include "ScoreBoardScene.hpp"
#include <vector>
#include <string>
#include <map>

class PlayScene : public Engine::IScene
{
private:
    int sw, sh;
    Engine::Point cameraTopLeft, cameraDownRight;
    Engine::Point cameraD;
    Engine::Point camera;
    Player *player1;
    Engine::Label *healthLabel;
    int score;
    Engine::Label *scoreLabel;
    Engine::Image *shade;
    std::vector<std::shared_ptr<Engine::Image>> coinFrames;
    std::vector<std::shared_ptr<Engine::Image>> healFrames;
    std::vector<ScoreData> scoreboard;
    int currentFrame;    // Current frame of animation
    float animationTime; // Time accumulator for animation
    bool isHealing;      // Add the isHealing flag
    float healAnimationTimer;
    float sinceLightExpandStart;
    float lightExpandDuration;
    float initialLightScale;
    int healFrame;
    MiniMap *miniMap;

    enum ItemType
    {
        NONE,
        COIN,
        HEAL,
        DAMAGEFLASK,
        SPEEDFLASK,
        LIGHT,
    };
    enum TileType
    {
        TILE_DIRT1,
        TILE_DIRT2,
        TILE_DIRT3,
        TILE_DIRT4,
        TILE_GRASS1,
        TILE_GRASS2,
        TILE_GRASS3,
        TILE_BUSH,
        TILE_TOMBSTONE,
        TILE_POLETILE,
        TILE_STONE,
        TILE_BOX,
        TILE_CAR,
        TILE_DEBRIS,
        TILE_LOG,
        TILE_PATH0,
        TILE_PATH1,
        TILE_PATH2,
        TILE_PATH3,
        TILE_PATH4,
        TILE_PATH5,
        TILE_PATH6,
        TILE_PATH7,
        TILE_PATH8,
        TILE_PATH9,
        TILE_PATH10,
        TILE_PATH11,
    };
    std::vector<double> ItemProbabilities;
    std::vector<Engine::ImageButton *> heartImages;
    std::vector<Animation *> healAnimations;

public:
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    int MapId;
    Group *TileMapGroup;
    Group *ObstacleGroup;
    Group *NonObstacleGroup;
    Group *BulletGroup;
    Group *EnemyGroup;
    Group *PlayerGroup;
    Group *LabelGroup;
    Group *ItemGroup;
    Group *UILife;
    std::vector<std::vector<TileType>> mapState;
    explicit PlayScene();
    static Engine::Point GetClientSize();
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void ReadMap();
    void OnKeyDown(int keyCode) override;
    void OnKeyUp(int keyCode) override;
    int generateRandomItemValue();
    void generateItem(int index, float x, float y);
    void IncreaseKill();
    void updateScore();
    void ConstructHeart();
    void DestroyHeart();
    void HealAnim();
    bool RegenState();
    void ReadScoreBoard();
    void WriteScoreBoard();
    void ExpandLight(float boost);
    int getScore();
};

#endif // PLAYSCENE_HPP
