#include "Animation.hpp"
#include <allegro5/allegro_image.h>
#include <iostream>

Animation::Animation(const std::vector<std::string>& framePaths, float frameDuration,
                     float x, float y, float anchorX, float anchorY,
                     float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), timeElapsed(0.0f),
      x(x), y(y), anchorX(anchorX), anchorY(anchorY), scaleX(scaleX), scaleY(scaleY),
      finished(false)
{
   for (const auto &path : framePaths) {
      // Create the shared_ptr<ALLEGRO_BITMAP> directly
      std::shared_ptr<ALLEGRO_BITMAP> bitmap(al_load_bitmap(path.c_str()), al_destroy_bitmap);

      if (!bitmap) {
         std::cerr << "Error loading image: " << path << std::endl;
      } else {
         frames.push_back(bitmap);
      }
   }
}

void Animation::Update(float deltaTime)
{
   if (finished)
      return;

   timeElapsed += deltaTime;
   if (timeElapsed >= frameDuration)
   {
      currentFrame = (currentFrame + 1) % frames.size();
      timeElapsed = 0.0f;

      if (currentFrame == 0)
      { // Animation looped back to the start
         finished = true;
      }
   }
}

void Animation::Draw() const
{
   if (currentFrame < frames.size() && frames[currentFrame])
   {
      int frameWidth = al_get_bitmap_width(frames[currentFrame].get());
      int frameHeight = al_get_bitmap_height(frames[currentFrame].get());

      al_draw_scaled_bitmap(frames[currentFrame].get(),
                            0, 0, frameWidth, frameHeight,
                            x - anchorX * frameWidth * scaleX,
                            y - anchorY * frameHeight * scaleY,
                            frameWidth * scaleX, frameHeight * scaleY,
                            0);
   }
}