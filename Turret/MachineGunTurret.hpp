#ifndef MACHINEGUNTURRET_HPP
#define MACHINEGUNTURRET_HPP
#include "Turret.hpp"

class MachineGunTurret: public Turret {
public:
	static const int Price;
	//static const int ID;
    MachineGunTurret(float x, float y);
	void CreateBullet() override;
	int GetID() override;
};
#endif // MACHINEGUNTURRET_HPP
