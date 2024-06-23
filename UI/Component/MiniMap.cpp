#include "MiniMap.hpp"
#include "Engine/GameEngine.hpp"
#include "Player/Player.hpp"
#include "Scene/PlayScene.hpp"
#include <cmath>

#include <iostream>

PlayScene *MiniMap::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

MiniMap::MiniMap()
{
    range = 1000;
    radius = 128;
    Size.x = Size.y = radius * 2;
    Position.x = Engine::GameEngine::GetInstance().GetScreenSize().x - Size.x / 2 - 20;
    Position.y = Size.y / 2 + 20;
    getPlayScene()->AddNewObject(EnemyLocGroup = new Engine::Group());
    getPlayScene()->AddNewObject(ItemLocGroup = new Engine::Group());
    getPlayScene()->AddNewObject(Border = new Engine::Image("play/minimap_border.png", Position.x, Position.y, Size.x + 5, Size.y + 5, 0.5f, 0.5f));
    getPlayScene()->AddNewObject(BackGround = new Engine::Image("play/minimap.png", Position.x, Position.y, Size.x, Size.y, 0.5f, 0.5f));
    getPlayScene()->AddNewObject(PlayerLoc = new Engine::Image("play/player_loc.png", Position.x, Position.y, 0, 0, 0.5f, 0.5f));
   // getPlayScene()->AddNewObject(BackGround = new Engine::Image("play/minimap_border.png", Position.x, Position.y, Size.x + 5, Size.y + 5, 0.5f, 0.5f));
}

void MiniMap::Update(float deltaTime)
{
    EnemyLocGroup->Clear();
    ItemLocGroup->Clear();
    auto player = getPlayScene()->PlayerGroup->GetObjects().front();
    for (auto enemy : getPlayScene()->EnemyGroup->GetObjects())
    {
        Engine::Point dist = enemy->Position - player->Position;
        if (abs(dist.x) < range && abs(dist.y) < range)
        {
            EnemyLocGroup->AddNewObject(new Engine::Image("play/enemy_loc.png", Position.x + (+dist.x) * radius / range, Position.y + (+dist.y) * radius / range, 0.0f, 0.0f, 0.5f, 0.5f));
        }
    }
    for (auto item : getPlayScene()->ItemGroup->GetObjects())
    {
        Engine::Point dist = item->Position - player->Position;
        if (abs(dist.x) < range && abs(dist.y) < range)
        {
            ItemLocGroup->AddNewObject(new Engine::Image("play/drop_loc.png", Position.x + (+dist.x) * radius / range, Position.y + (+dist.y) * radius / range, 0.0f, 0.0f, 0.5f, 0.5f));
        }
    }
}

void MiniMap::Draw() const
{
    Border->Draw();
    BackGround->Draw();
    EnemyLocGroup->Draw();
    ItemLocGroup->Draw();
    PlayerLoc->Draw();
}