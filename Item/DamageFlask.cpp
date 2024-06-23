#include "Item/DamageFlask.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

#include <iostream>

DamageFlask::DamageFlask(float x, float y)
    : Item("PixelArt/DamageFlask/flasks_4_1.png", x, y), sinceLastCicle(0.0f)
{
    scaleX = 2.0f;
    scaleY = 2.0f;

    imagePath = {
        "PixelArt/DamageFlask/flasks_4_1.png",
        "PixelArt/DamageFlask/flasks_4_2.png",
        "PixelArt/DamageFlask/flasks_4_3.png",
        "PixelArt/DamageFlask/flasks_4_4.png",
        "PixelArt/DamageFlask/flasks_4_1.png"};
    frame = static_cast<int>(imagePath.size());
    for (auto imgPath : imagePath)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
}

void DamageFlask::Update(float deltaTime)
{
    sinceLastCicle += deltaTime;
    if (sinceLastCicle >= frameDuration)
    {
        frame = (frame + 1) % 5;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        sinceLastCicle = 0; // Reset elapsed time
    }
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
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius && scene->RegenState() == false))
        {
            player->AddBulletDmg(10.0f);
            scene->ItemGroup->RemoveObject(objectIterator);
            return;
        }
    }
}
