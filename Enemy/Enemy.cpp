#include "Enemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Collider.hpp"
#include <cmath>

Enemy::Enemy(float x, float y)
    : Engine::Sprite("play/enemy-1.png", x, y), hp(100), speed(50), damage(5),timeSinceLastAttack(0), attackCooldown(2.0f)
{
    scaleX = 2.0f;
    scaleY = 2.0f;
    CollisionRadius = 40;
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

    if(timeSinceLastAttack <= attackCooldown)
    timeSinceLastAttack += deltaTime;
    if (IsOverlapWithPlayer())
    {
        Velocity.x *= -1;
        Velocity.y *= -1;
    }

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

bool Enemy::IsOverlapWithPlayer()
{
    PlayScene *scene = getPlayScene();

    for (auto &it : scene->PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, player->Position, player->CollisionRadius))
        {
            if(timeSinceLastAttack >= attackCooldown)
            {
                Velocity.x *= -10;
                Velocity.y *= -10;
                player->TakeDamage(damage);
                timeSinceLastAttack = 0;
            }
            return true;
        }
    }
    return false;
}