#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <allegro5/allegro.h>
#include <vector>
#include <memory>

class Animation
{
public:
   Animation(const std::vector<std::string> &framePaths, float frameDuration,
             float x, float y, float anchorX = 0.5f, float anchorY = 0.5f,
             float scaleX = 1.0f, float scaleY = 1.0f);
   void Update(float deltaTime);
   void Draw() const;
   bool IsFinished() const { return finished; }

private:
   std::vector<std::shared_ptr<ALLEGRO_BITMAP>> frames;
   float frameDuration;
   size_t currentFrame;
   float timeElapsed;
   float x, y;
   float anchorX, anchorY;
   float scaleX, scaleY;
   bool finished;
};

#endif // ANIMATION_HPP