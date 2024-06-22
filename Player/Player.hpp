#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Engine/Sprite.hpp"

#include <vector>
#include <string>

class PlayScene;

class Player : public Engine::Sprite
{
private:
    int hp;    // Player's HP
    int frame; // Animation frame index
    bool moving;
    bool movingU, movingD, movingL, movingR;
    float speed = 200.0f;
    float bulletDmg;
    float imgRotation;
    std::vector<std::string> imagePath;           // List of current image paths for animation
    std::vector<std::string> rightLeftWalkImages; // Image paths for right-left walking
    std::vector<std::string> upWalkImages;        // Image paths for up-down walking
    std::vector<std::string> downWalkImages;
    float elapsedTime;                // Time elapsed since last frame change
    const float frameDuration = 0.1f; // Duration of each frame in seconds
    float timeSinceLastShot;
    float shootCooldown;
    PlayScene *getPlayScene();

public:
    Player(float x, float y, int hp);
    void Update(float deltaTime) override;
    void TakeDamage(int damage);
    int GetHealth() const;
    float GetSpeed() const;
    void Shoot();
    void HandleOverlapWithObstacle(float deltaTime);
    void StartMove(int keyCode);
    void StopMove(int keyCode);
    void AddBulletDmg(float dmg);
};

#endif // PLAYER_HPP
