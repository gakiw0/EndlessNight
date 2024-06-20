#include "Bullet.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Collider.hpp"
#include "Scene/PlayScene.hpp"
#include "Enemy/Enemy.hpp"
#include <cmath>

#include <iostream>

Bullet::Bullet(float x, float y, float rotation, float speed)
    : Sprite("play/bullet-1.png", x, y, 0, 0, 0.5, 0.5, 0, 255, 255, 255, 255), speed(speed), damage(50) {
    this->Velocity.x = std::cos(rotation) * speed;
    this->Velocity.y = std::sin(rotation) * speed;
    this->Rotation = rotation - ALLEGRO_PI / 2; 
    CollisionRadius = 10;
}

PlayScene* Bullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Bullet::Update(float deltaTime) {
    Sprite::Update(deltaTime);

    PlayScene *scene = getPlayScene();

    for(auto& it: scene->EnemyGroup->GetObjects())
    {
        Enemy* enemy = dynamic_cast<Enemy*>(it);
        if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			enemy->Hit(damage);
			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
    }
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
    
}
