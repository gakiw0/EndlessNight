#ifndef ITEM_HPP
#define ITEM_HPP

#include "Engine/Sprite.hpp"

class PlayScene;

class Item : public Engine::Sprite
{
    protected:
        std::string imgPath;
        float amplitude;
        float frequency;
        float elapsedTime;
    public:
        Item(std::string imgPath, float x, float y);
        void Update(float deltaTime) override;
        PlayScene *getPlayScene();
        
        void hoverEffect(float deltaTime);
};

#endif //ITEM_HPP