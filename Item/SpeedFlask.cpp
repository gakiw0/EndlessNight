#include "Item/SpeedFlask.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

#include <iostream>

SpeedFlask::SpeedFlask(float x, float y)
    : Item("PixelArt/SpeedFlask/flasks_3_1.png", x, y), sinceLastCicle(0.0f)
{
    scaleX = 2.0f;
    scaleY = 2.0f;

    imagePath = {
        "PixelArt/SpeedFlask/flasks_3_1.png",
        "PixelArt/SpeedFlask/flasks_3_2.png",
        "PixelArt/SpeedFlask/flasks_3_3.png",
        "PixelArt/SpeedFlask/flasks_3_4.png",
        "PixelArt/SpeedFlask/flasks_3_1.png"};
    frame = static_cast<int>(imagePath.size());
    for (auto imgPath : imagePath)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
}

void SpeedFlask::Update(float deltaTime)
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
