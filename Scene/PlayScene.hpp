#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include "Engine/IScene.hpp"
#include "Player/Player.hpp"
#include "UI/Component/Label.hpp"
#include "Bullet/Bullet.hpp"
#include "Engine/Point.hpp"
#include <vector>
#include <string>

class PlayScene : public Engine::IScene
{
private:
    int sw, sh;
    Engine::Point cameraTopLeft, cameraDownRight;
    Engine::Point cameraD;
    Engine::Point camera;
    Player *player1;
    Engine::Label *healthLabel;
    float remainingTime;
    Engine::Label *timerLabel;
    enum TileType {
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

public:
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    int MapId;
    Group* TileMapGroup;
    Group* ObstacleGroup;
    Group* NonObstacleGroup;
    Group *BulletGroup;
    Group *EnemyGroup;
    Group *PlayerGroup;
    Group *LabelGroup;
    std::vector<std::vector<TileType>> mapState;
    explicit PlayScene();
    static Engine::Point GetClientSize();
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void ReadMap();
    
};

#endif // PLAYSCENE_HPP
