#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Engine/Sprite.hpp"

class PlayScene;

class Enemy : public Engine::Sprite {
protected:
    float speed;
    int hp;
    int damage;
    float attackCooldown;
    float timeSinceLastAttack;
public:
    Enemy(float x, float y);
    void Update(float deltaTime) override;
    PlayScene* getPlayScene();
    void Hit(float damage);
    bool IsOverlapWithPlayer();
};

#endif // ENEMY_HPP
