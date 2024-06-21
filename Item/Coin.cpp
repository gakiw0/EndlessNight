#include "Coin.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"

Coin::Coin(float x, float y)
    : Item("Transparent/coin4_16x16.png", x, y)
{
    scaleX = 2.0f;
    scaleY = 2.0f;
}

void Coin::Update(float deltaTime)
{
    HandleOverlapWithPlayer(deltaTime);
    hoverEffect(deltaTime);
    Sprite::Update(deltaTime);
}

void Coin::HandleOverlapWithPlayer(float deltaTime)
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
