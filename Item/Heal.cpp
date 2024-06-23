#include "Heal.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

Heal::Heal(float x, float y)
    : Item("PixelArt/Heart/heart0.png", x, y), sinceLastCicle(0.0f)
{
    scaleX = 2.0f;
    scaleY = 2.0f;

    imagePath = {
        "PixelArt/Heart/heart0.png",
        "PixelArt/Heart/heart1.png",
        "PixelArt/Heart/heart2.png",
        "PixelArt/Heart/heart3.png",
        "PixelArt/Heart/heart4.png",
        "PixelArt/Heart/heart5.png",
        "PixelArt/Heart/heart6.png",
        "PixelArt/Heart/heart7.png"};
    frame = static_cast<int>(imagePath.size());
    for (auto imgPath : imagePath)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
}

void Heal::Update(float deltaTime)
{
    sinceLastCicle += deltaTime;
    if (sinceLastCicle >= frameDuration)
    {
        frame = (frame + 1) % 8;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        sinceLastCicle = 0; // Reset elapsed time
    }
    hoverEffect(deltaTime);
    Sprite::Update(deltaTime);
    HandleOverlapWithPlayer(deltaTime);
}

void Heal::HandleOverlapWithPlayer(float deltaTime)
{
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius))
        {
            if (scene->RegenState() == false)
            {
            scene->HealAnim();
            player->Heal(10.0f);
            scene->ItemGroup->RemoveObject(objectIterator);
            return;
            }
        }
    }
}
