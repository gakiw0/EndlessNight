#include "Enemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Resources.hpp"
#include "Engine/Collider.hpp"
#include <cmath>

Enemy::Enemy(float x, float y)
    : Engine::Sprite("PixelArt/Zombie/RightLeftWalk/pixil-frame-0.png", x, y), hp(100), speed(50), damage(5), timeSinceLastAttack(0), attackCooldown(2.0f), frame(0), elapsedTime(0.0f)
{
    CollisionRadius = 10;

    rightLeftWalkImages = {
        "PixelArt/Zombie/RightLeftWalk/pixil-frame-0.png",
        "PixelArt/Zombie/RightLeftWalk/pixil-frame-1.png",
        "PixelArt/Zombie/RightLeftWalk/pixil-frame-2.png"};

    upWalkImages = {
        "PixelArt/Zombie/UpWalk/pixil-frame-0.png",
        "PixelArt/Zombie/UpWalk/pixil-frame-1.png",
        "PixelArt/Zombie/UpWalk/pixil-frame-2.png"};

    downWalkImages = {
        "PixelArt/Zombie/DownWalk/pixil-frame-0.png",
        "PixelArt/Zombie/DownWalk/pixil-frame-1.png",
        "PixelArt/Zombie/DownWalk/pixil-frame-2.png"};

    for (auto imgPath : rightLeftWalkImages)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
    for (auto imgPath : upWalkImages)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
    for (auto imgPath : downWalkImages)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);

    // Use right-left walk images as the default
    imagePath = rightLeftWalkImages;
}

PlayScene *Enemy::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Enemy::Update(float deltaTime)
{
    auto target = getPlayScene()->PlayerGroup->GetObjects().front();
    imgRotation = atan2((target->Position.y - Position.y), (target->Position.x - Position.x));
    Velocity.x = cos(imgRotation) * speed;
    Velocity.y = sin(imgRotation) * speed;

    if (Velocity.x > 20.0f)
    {
        imgRotation = 0; // Right (D)
        imagePath = rightLeftWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        scaleX = abs(scaleX);
    }
    else if (Velocity.x < -20.0f)
    {
        imgRotation = ALLEGRO_PI; // Left (A)
        imagePath = rightLeftWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        scaleX = -abs(scaleX);
    }
    else
    {
        if (Velocity.y > 0)
        {
            imgRotation = ALLEGRO_PI / 2; // Down (S)
            imagePath = downWalkImages;
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        }
        else if (Velocity.y < 0)
        {
            imgRotation = 3 * ALLEGRO_PI / 2; // Up (W)
            imagePath = upWalkImages;
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        }
    }

    elapsedTime += deltaTime;
    if (elapsedTime >= frameDuration)
    {
        // Toggle between specific frames for up-walk animation
        frame = (frame + 1) % 3;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        elapsedTime = 0; // Reset elapsed time
    }

    if (timeSinceLastAttack <= attackCooldown)
        timeSinceLastAttack += deltaTime;

    HandleOverlapWithPlayer(deltaTime);

    HandleOverlapWithObstacle(deltaTime);

    Sprite::Update(deltaTime);
}

void Enemy::Hit(float damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        int index = getPlayScene()->generateRandomItemValue();
        getPlayScene()->generateItem(index, Position.x, Position.y);
        getPlayScene()->IncreaseKill();
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
    }
}

void Enemy::HandleOverlapWithPlayer(float deltaTime)
{
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius))
        {
            if (timeSinceLastAttack >= attackCooldown)
            {
                Velocity.x *= 5;
                Velocity.y *= 5;
                if (scene->RegenState() == false)
                    player->TakeDamage(damage);
                timeSinceLastAttack = 0;
            }
            Velocity.x = -Velocity.x;
            Velocity.y = -Velocity.y;
            return;
        }
    }
}

void Enemy::HandleOverlapWithObstacle(float deltaTime)
{
    Engine::Point PositionPlusX = Engine::Point(Position.x + Velocity.x * deltaTime, Position.y);
    Engine::Point PositionPlusY = Engine::Point(Position.x, Position.y + Velocity.y * deltaTime);

    PlayScene *scene = getPlayScene();
    for (auto &it : scene->ObstacleGroup->GetObjects())
    {
        Image *obstacle = dynamic_cast<Image *>(it);
        if (Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
        {
            return;
        }
        else if (Engine::Collider::IsRectOverlap(PositionPlusX - Size / 2, PositionPlusX + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2) || Engine::Collider::IsRectOverlap(PositionPlusY - Size / 2, PositionPlusY + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
        {
            if (Engine::Collider::IsRectOverlap(PositionPlusX - Size / 2, PositionPlusX + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
                Velocity.x = 0;
            if (Engine::Collider::IsRectOverlap(PositionPlusY - Size / 2, PositionPlusY + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
                Velocity.y = 0;
            return;
        }
    }
}