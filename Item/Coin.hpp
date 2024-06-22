#ifndef COIN_HPP
#define COIN_HPP

#include "Item.hpp"
#include <vector>

class Coin : public Item{
private:
    int frame;
    float sinceLastCicle;
    const float frameDuration = 0.1f;
    std::vector<std::string> imagePath; 
public:
    Coin (float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // COIN_HPP