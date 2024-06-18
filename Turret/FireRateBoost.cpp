#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "FireRateBoost.hpp" 

const int FireRateBoost::Price = 0;

FireRateBoost::FireRateBoost(float x, float y)
    : Turret("play/blankpage.png", "play/firerateboost.png", x, y, 0, Price, 0) { 
}

void FireRateBoost::CreateBullet() {
}

int FireRateBoost::GetID() {
    return 7; 
}