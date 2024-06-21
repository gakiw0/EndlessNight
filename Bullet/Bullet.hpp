#ifndef BULLET_HP
#define BULLET_HP

#include "Engine/Sprite.hpp"

class PlayScene;

class Bullet : public Engine::Sprite {
public:
    float speed;
    float damage;
    Bullet(float x, float y, float rotation, float speed, float dmg);
    PlayScene *getPlayScene();
    void Update(float deltaTime) override;
};

#endif // BULLET_HP
