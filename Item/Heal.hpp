#ifndef HEAL_HPP
#define HEAL_HPP

#include "Item.hpp"
#include <vector>

class Heal : public Item{
private:
    int frame;
    float sinceLastCicle;
    const float frameDuration = 0.1f;
    std::vector<std::string> imagePath; 
public:
    Heal (float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // HEAL_HPP