#ifndef COIN_HPP
#define COIN_HPP

#include "Item.hpp"

class Coin : public Item{
private:
    
public:
    Coin (float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // COIN_HPP