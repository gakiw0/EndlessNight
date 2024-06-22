#include "Coin.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"

Coin::Coin(float x, float y)
    : Item("PixelArt/Coin/coin0.png", x, y), sinceLastCicle(0.0f)
{
    scaleX = 2.0f;
    scaleY = 2.0f;

    imagePath = {
        "PixelArt/Coin/coin0.png",
        "PixelArt/Coin/coin1.png",
        "PixelArt/Coin/coin2.png",
        "PixelArt/Coin/coin3.png",
        "PixelArt/Coin/coin4.png",
        "PixelArt/Coin/coin5.png",
        "PixelArt/Coin/coin6.png",
        "PixelArt/Coin/coin7.png"};
    frame = static_cast<int>(imagePath.size());
    for (auto imgPath : imagePath)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
}

void Coin::Update(float deltaTime)
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
            scene->updateScore();
            return;
        }
    }
    
}
