#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Group.hpp"
#include "RangeBoost.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int RangeBoost::Price = 0;
RangeBoost::RangeBoost(float x, float y) :
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
	Turret("play/blankpage.png", "play/rangeboost.png", x, y, 0, Price, 0.5) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}

void RangeBoost::CreateBullet() 
{
}

int RangeBoost::GetID()
{
	return 6;
}


