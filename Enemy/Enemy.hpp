#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Engine/Sprite.hpp"

class PlayScene;

class Enemy : public Engine::Sprite
{
protected:
    float speed;
    int frame;
    int hp;
    int damage;
    float imgRotation;
    float attackCooldown;
    float timeSinceLastAttack;
    float elapsedTime;
    const float frameDuration = 0.2f;
    std::vector<std::string> imagePath;           // List of current image paths for animation
    std::vector<std::string> rightLeftWalkImages; // Image paths for right-left walking
    std::vector<std::string> upWalkImages;        // Image paths for up-down walking
    std::vector<std::string> downWalkImages; 
public:
    Enemy(float x, float y);
    void Update(float deltaTime) override;
    PlayScene *getPlayScene();
    void Hit(float damage);
    void HandleOverlapWithPlayer(float deltaTime);
    void HandleOverlapWithObstacle(float deltaTime);
};

#endif // ENEMY_HPP
