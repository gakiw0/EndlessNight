#ifndef SPEEDFLASK_HPP
#define SPEEDFLASK_HPP

#include "Item.hpp"
#include <vector>

class SpeedFlask : public Item{
private:
public:
    SpeedFlask(float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // SpeedFLASK_HPP