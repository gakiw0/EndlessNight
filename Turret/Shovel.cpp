#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Group.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Shovel::Price = 30;
Shovel::Shovel(float x, float y) :
	
	Turret("play/blankpage.png", "play/shovel.png", x, y, 0, Price, 0.5) {
	
	Anchor.y += 8.0f / GetBitmapHeight();
}

void Shovel::CreateBullet() {
}

int Shovel::GetID()
{
	return 4;
}


