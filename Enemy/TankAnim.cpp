#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "TankAnim.hpp"
#include "Engine/GameEngine.hpp"

TankAnim::TankAnim(int x, int y) : Enemy("play/enemy-3.png", x, y, 250, 350, 100, 50),
                                   head("play/enemy-3-head.png", x, y), targetRotation(0)
{
}
void TankAnim ::Draw() const
{
   Enemy::Draw();
   head.Draw();
}
void TankAnim::Update(float deltaTime)
{
   if (targetPosition.x != 0.0f || targetPosition.y != 0.0f)
   {

      if (targetPosition != Position)
      {
         Engine::Point direction = (targetPosition - Position).Normalize();
         float angle = atan2(direction.y, direction.x);
         Rotation = angle;

         Position.x += direction.x * speed * deltaTime;
         Position.y += direction.y * speed * deltaTime;

         if (Position.Distance(targetPosition) < 5.0f)
         {
            Position = targetPosition;
         }
      }

      head.Position = Position;
      head.Rotation = Rotation + sin(deltaTime * 4.0f) * ALLEGRO_PI / 8;
   }
}
