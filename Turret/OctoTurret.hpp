#ifndef OCTOTURRET_HPP
#define OCTOTURRET_HPP
#include "Turret.hpp"

class OctoTurret : public Turret
{
public:
   static const int Price;
   // static const int ID;
   OctoTurret(float x, float y);
   void CreateBullet() override;
   int GetID() override;

private:
   int currentDirectionIndex;
};
#endif // MACHINEGUNTURRET_HPP
