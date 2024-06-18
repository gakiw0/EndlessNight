#ifndef RANGEBOOST_HPP
#define RANGEBOOST_HPP
#include "Turret.hpp"

class RangeBoost: public Turret {
public:
	static const int Price;
   RangeBoost(float x, float y);
	void CreateBullet() override;
	int GetID() override;
};
#endif // RANGEBOOST_HPP
