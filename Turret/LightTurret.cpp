#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/LightBullet.hpp"
#include "Engine/Group.hpp"
#include "LightTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int LightTurret::Price = 300;
LightTurret::LightTurret(float x, float y) :
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
	Turret("play/tower-base.png", "play/turret-7.png", x, y, 350, Price, 2) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void LightTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
   Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new LightBullet(Position + normalized * 36 - normal * 8, diff, rotation, this));
   getPlayScene()->BulletGroup->AddNewObject(new LightBullet(Position + normalized * 36 + normal * 8, diff, rotation, this));
	AudioHelper::PlayAudio("laser.wav");
}

int LightTurret::GetID()
{
	return 3;
}
