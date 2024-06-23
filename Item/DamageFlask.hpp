#ifndef DAMAGEFLASK_HPP
#define DAMAGEFLASK_HPP

#include "Item.hpp"
#include <vector>

class DamageFlask : public Item{
private:
public:
    DamageFlask(float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // DAMAGEFLASK_HPP