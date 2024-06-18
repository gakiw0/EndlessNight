#include "OctoTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Point.hpp"

const int OctoTurret::Price = 100;

OctoTurret::OctoTurret(float x, float y) : 
    Turret("play/tower-base.png", "play/turret-octa.png", x, y, 0 , Price, 0.3 /* Adjust cooldown */),
    currentDirectionIndex(0)
{
   this->enableTargeting = false;
   Anchor.y += 8.0f / GetBitmapHeight(); 
}

void OctoTurret::CreateBullet()
{
   // Define the 8 directions (adjust angles as needed)
   const std::vector<Engine::Point> directions = {
       Engine::Point(0, -1), // Up
       Engine::Point(1, -1), // Up-Right
       Engine::Point(1, 0),  // Right
       Engine::Point(1, 1),  // Down-Right
       Engine::Point(0, 1),  // Down
       Engine::Point(-1, 1), // Down-Left
       Engine::Point(-1, 0), // Left
       Engine::Point(-1, -1) // Up-Left
   };

   // Get the current direction
   Engine::Point direction = directions[currentDirectionIndex];

   // Calculate bullet position and rotation
   Engine::Point normalized = direction.Normalize();
   getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 36, direction, atan2(direction.y, direction.x), this));
   AudioHelper::PlayAudio("gun.wav"); // Play your sound effect

   // Update direction index for the next shot
   currentDirectionIndex = (currentDirectionIndex + 1) % 8; // Cycle through 0-7

   Rotation = atan2(direction.y, direction.x) + ALLEGRO_PI / 2; 
}

int OctoTurret::GetID()
{
   return 5; // Your OctoTurret ID
}