#ifndef DAMAGEFLASK_HPP
#define DAMAGEFLASK_HPP

#include "Item.hpp"
#include <vector>

class DamageFlask : public Item{
private:
    int frame;
    float sinceLastCicle;
    const float frameDuration = 0.1f;
    std::vector<std::string> imagePath; 
public:
    DamageFlask(float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // DAMAGEFLASK_HPP