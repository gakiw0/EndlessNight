#ifndef FIRERATEBOOST_HPP
#define FIRERATEBOOST_HPP

#include "Turret.hpp"

class FireRateBoost : public Turret {
public:
    static const int Price; 
    FireRateBoost(float x, float y);
    void CreateBullet() override; // Leave empty, power-up doesn't shoot
    int GetID() override;
};

#endif // FIRERATEBOOST_HPP