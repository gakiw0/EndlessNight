#include "Item/DamageFlask.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

#include <iostream>

DamageFlask::DamageFlask(float x, float y)
    : Item("PixelArt/DamageFlask/flasks_4_1.png", x, y)
{
    scaleX = 2.0f;
    scaleY = 2.0f;
}

void DamageFlask::Update(float deltaTime)
{
    hoverEffect(deltaTime);
    Sprite::Update(deltaTime);
    HandleOverlapWithPlayer(deltaTime);
}

void DamageFlask::HandleOverlapWithPlayer(float deltaTime)
{
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius))
        {
            player->AddBulletDmg(10.0f);
            scene->ItemGroup->RemoveObject(objectIterator);
            return;
        }
    }
}
