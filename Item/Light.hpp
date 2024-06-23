#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Item.hpp"
#include <vector>

class Light : public Item{
private:
public:
    Light(float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // LIGHT_HPP