#ifndef MINIMAP_HPP
#define MINIMAP_HPP

#include "Engine/IObject.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Image.hpp"

class PlayScene;

class MiniMap : public Engine::IObject
{
private:
    int range;
    int radius;
    Engine::Image *BackGround;
    Engine::Image *Border;
    Engine::Image *PlayerLoc;
    Engine::Group *EnemyLocGroup;
    Engine::Group *ItemLocGroup;
public:
    explicit MiniMap();
    void Update(float deltaTime) override;
    void Draw() const override;
    PlayScene *getPlayScene();
};

#endif // MINIMAP_HPP