#include "Item.hpp"
#include "Engine/GameEngine.hpp"
#include "Scene/PlayScene.hpp"
#include <iostream>
#include <cmath>

Item::Item(std::string imgPath, float x, float y)
    : Engine::Sprite(imgPath, x, y), amplitude(5.0f), frequency(3.0f), elapsedTime(0.0f)
{
    CollisionRadius = 20;
}

PlayScene *Item::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Item::Update(float deltaTime)
{
}

void Item::hoverEffect(float deltaTime)
{
    elapsedTime += deltaTime;
    if(frequency * elapsedTime > 2 * ALLEGRO_PI)
        elapsedTime = (frequency * elapsedTime - 2 * ALLEGRO_PI) / frequency;
    Velocity.y = frequency * amplitude * std::cos(frequency * elapsedTime);
}


