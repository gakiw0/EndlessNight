#include "Enemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Collider.hpp"
#include <cmath>

Enemy::Enemy(float x, float y)
    : Engine::Sprite("play/enemy-1.png", x, y), hp(100), speed(50), damage(5), timeSinceLastAttack(0), attackCooldown(2.0f)
{
    CollisionRadius = 10;
}

PlayScene *Enemy::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Enemy::Update(float deltaTime)
{
    auto target = getPlayScene()->PlayerGroup->GetObjects().front();
    Rotation = atan2((target->Position.y - Position.y), (target->Position.x - Position.x));
    Velocity.x = cos(Rotation) * speed;
    Velocity.y = sin(Rotation) * speed;

    if (timeSinceLastAttack <= attackCooldown)
        timeSinceLastAttack += deltaTime;
    IsOverlapWithPlayer(deltaTime);

    IsOverlapWithObstacle(deltaTime);

    Sprite::Update(deltaTime);
}

void Enemy::Hit(float damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
    }
}

void Enemy::IsOverlapWithPlayer(float deltaTime)
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
                player->TakeDamage(damage);
                timeSinceLastAttack = 0;
            }
            Velocity.x = -Velocity.x;
            Velocity.y = -Velocity.y;
            return;
        }
    }
}

void Enemy::IsOverlapWithObstacle(float deltaTime)
{
    Engine::Point nextPosition;
    nextPosition.x = Position.x + Velocity.x * deltaTime;
    nextPosition.y = Position.y + Velocity.y * deltaTime;
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->ObstacleGroup->GetObjects())
    {
        Image *obstacle = dynamic_cast<Image *>(it);
        if (Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
        {
            return;
        }
        else if (Engine::Collider::IsRectOverlap(nextPosition - Size / 2, nextPosition + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
        {
            Velocity.x = 0;
            Velocity.y = 0;
            return;
        }
    }
}