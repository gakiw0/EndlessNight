#include "AutoScroller.hpp"
#include "Engine/GameEngine.hpp"
#include <allegro5/allegro_image.h>
#include <iostream>

AutoScroller::AutoScroller(const char *imagePath, float speed)
    : speed(speed), zoom(1.0f)
{

   std::string fullImagePath = "Resource/images/";
   fullImagePath += imagePath;

   image = al_load_bitmap(fullImagePath.c_str());
   if (!image)
   {
      std::cerr << "Error loading image: " << fullImagePath << std::endl;
   }
   else
   {
      width = al_get_bitmap_width(image);
      height = al_get_bitmap_height(image);
   }

   offsetX = 0;
}

AutoScroller::~AutoScroller()
{
   if (image)
   {
      al_destroy_bitmap(image);
   }
}

void AutoScroller::Update(float deltaTime)
{
   offsetX -= speed * deltaTime;

   if (offsetX <= -width)
   {
      offsetX += width;
   }
}

void AutoScroller::SetZoom(float zoomFactor)
{
   zoom = zoomFactor;
}

void AutoScroller::Draw()
{
   if (image)
   {
      int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
      int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
      float scaledWidth = width * zoom;
      float scaledHeight = height * zoom;
      float sh = h;
      float sw = h * width / height;

      // al_draw_scaled_bitmap(image,
      //                       0, 0, width, height,
      //                       offsetX, 0, scaledWidth, scaledHeight,
      //                       0);

      // al_draw_scaled_bitmap(image,
      //                       0, 0, width, height,
      //                       offsetX + scaledWidth, 0, scaledWidth, scaledHeight,
      //                       0);

      al_draw_scaled_bitmap(image,
                            0, 0, width, height,
                            offsetX, 0, sw, sh,
                            0);

      al_draw_scaled_bitmap(image,
                            0, 0, width, height,
                            offsetX + sw, 0, sw, sh,
                            0);
   }
}