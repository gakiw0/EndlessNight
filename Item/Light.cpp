#include "Light.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Resources.hpp"
#include <cmath>

Light::Light(float x, float y)
    : Item("PixelArt/Torch/torch.png", x, y)
{
    Rotation = atan2(sin(ALLEGRO_PI / 4), cos(ALLEGRO_PI / 4));
    scaleX = 1.f;
    scaleY = 1.0f;
}

void Light::Update(float deltaTime)
{
    hoverEffect(deltaTime);
    Sprite::Update(deltaTime);
    HandleOverlapWithPlayer(deltaTime);
}

void Light::HandleOverlapWithPlayer(float deltaTime)
{
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius))
        {
            scene->ExpandLight(2.0f);
            scene->ItemGroup->RemoveObject(objectIterator);
            return;
        }
    }
}
