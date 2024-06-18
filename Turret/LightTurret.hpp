#ifndef LIGHTTURRET_HPP
#define LIGHTTURRET_HPP
#include "Turret.hpp"

class LightTurret: public Turret {
public:
	static const int Price;
   LightTurret(float x, float y);
	void CreateBullet() override;
	int GetID() override;
};
#endif // LIGHTTURRET_HPP
