#ifndef SPEEDFLASK_HPP
#define SPEEDFLASK_HPP

#include "Item.hpp"
#include <vector>

class SpeedFlask : public Item{
private:
    int frame;
    float sinceLastCicle;
    const float frameDuration = 0.1f;
    std::vector<std::string> imagePath; 
public:
    SpeedFlask(float x, float y);
    void Update(float deltaTime) override;
    void HandleOverlapWithPlayer(float deltaTime);
};

#endif // SpeedFLASK_HPP