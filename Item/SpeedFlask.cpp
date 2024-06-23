#include "Item/SpeedFlask.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

#include <iostream>

SpeedFlask::SpeedFlask(float x, float y)
    : Item("PixelArt/SpeedFlask/flasks_3_1.png", x, y)
{
    scaleX = 3.0f;
    scaleY = 3.0f;
}

void SpeedFlask::Update(float deltaTime)
{
    hoverEffect(deltaTime);
    Sprite::Update(deltaTime);
    HandleOverlapWithPlayer(deltaTime);
}

void SpeedFlask::HandleOverlapWithPlayer(float deltaTime)
{
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius))
        {
            player->TemporarySpeedBoost(2.0f);
            scene->ItemGroup->RemoveObject(objectIterator);
            return;
        }
    }
}
